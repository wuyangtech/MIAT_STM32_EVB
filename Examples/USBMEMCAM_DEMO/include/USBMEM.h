#ifndef __USBMEM_H__
#define __USBMEM_H__

/* USB Hardware Functions */
void USB_Init       (void);
void USB_Connect    (BOOL  con);
void UBS_SetBuffer(unsigned char *Buffer,unsigned int Size);
void UBS_GetBuffer(void (*function)(unsigned char *));

#endif  /* __USBMEM_H__ */
