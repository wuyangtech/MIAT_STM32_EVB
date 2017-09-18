#ifndef __USBMEM_H__
#define __USBMEM_H__

/* USB Hardware Functions */
void USB_Init       (void);
void USB_Connect    (BOOL  con);
void USB_SetBuffer(unsigned char *Buffer,unsigned int Size);
void USB_GetBuffer(void (*function)(unsigned char *));
void USB_SetInBuffer(unsigned char *Buffer,unsigned int Size);
void USB_SetOutBuffer(unsigned char *Buffer,unsigned int Size);

#endif  /* __USBMEM_H__ */
