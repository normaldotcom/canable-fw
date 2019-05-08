#ifndef _USB_H_
#define _USB_H_

#include <stdint.h>

void usb_queue_msg_tx_from_interrupt(const uint8_t* msg, uint32_t len);
void usb_flush();

#endif /* end of include guard: _USB_H_ */
