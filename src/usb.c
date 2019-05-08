//
// usb: provides methods to queue data for USB safely
//

#include "usb.h"
#include "usbd_cdc_if.h"
#include "slcan.h"

#define BUFFER_SIZE 128

typedef struct {
  uint8_t data[BUFFER_SIZE];
  volatile size_t len;
  volatile int flushing;
} data_buffer;

static data_buffer buf;

void usb_queue_msg_tx_from_interrupt(const uint8_t* msg, uint32_t len)
{
  if (!buf.flushing && buf.len + len < sizeof(buf.data))
  {
    memcpy(buf.data + buf.len, msg, len);
    buf.len += len;
  }
}

void usb_flush()
{
  if (buf.len)
  {
    buf.flushing = 1;
    CDC_Transmit_FS(buf.data, buf.len);
    buf.len = 0;
    buf.flushing = 0;
  }
}
