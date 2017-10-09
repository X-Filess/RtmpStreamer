/*
 * Linux com Library
 */

#ifndef __LIBCOM_H__
#define __LIBCOM_H__

#if defined(_WIN32)||defined(WIN32)||defined(__WIN32__)||defined(_MSC_VER)
#  ifdef DLL_EXPORTS
#    define COM_API __declspec(dllexport)
#  else
#    define COM_API __declspec(dllimport)
#  endif
#  define COM_WIN
#else
#  define COM_API
#  define COM_POSIX
#endif

/**********************/
/* Message formatting */
/**********************/

#define COM_COMMAND                    0x01
#define COM_TERMINATOR                 0xFF


#define COM_SUCCESS                    0x00
#define COM_FAILURE                    0xFF

#ifdef __cplusplus
extern "C" {
#endif

#ifdef COM_WIN

#include <windows.h>

/* timeout in us */
#define COM_SERIAL_WAIT              100000

/* size of the local packet buffer */
#define COM_INPUT_BUFFER_SIZE          1024

/* This is the interface for the Windows platform.
 */
typedef struct _COM_interface
{
  // RS232 data:
  HANDLE port_fd;
  int baud;

  // RS232 input buffer
  unsigned char ibuf[COM_INPUT_BUFFER_SIZE];
  int bytes;
  int type;
} COMInterface_t;

#ifdef _MSC_VER
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;

#  include <crtdbg.h>
#else
#  include <stdint.h>
#  ifndef _RPTF0
#    define _RPTF0(rptno,msg)
#  endif
#  ifndef _RPTF1
#    define _RPTF1(rptno,msg,arg1)
#  endif
#  ifndef _RPTF3
#    define _RPTF3(rptno,msg,arg1,arg2,arg3)
#  endif
#  ifndef _CRT_WARN
#    define _CRT_WARN
#  endif
#endif /* _MSC_VER */

#elif __AVR__

#include "v24.h"
#include <stdio.h>

/* timeout in us */
#define COM_SERIAL_WAIT              100000

/* size of the local packet buffer */
#define COM_INPUT_BUFFER_SIZE            32

/* This is the interface for the AVR platform.
 */
typedef struct _COM_interface
{
	// RS232 data:
	v24_port_t port_fd;

	// RS232 input buffer
	unsigned char ibuf[COM_INPUT_BUFFER_SIZE];
	int bytes;
	int type;
} COMInterface_t;

#else

#include <termios.h>
#include <stdint.h>

/* timeout in us */
#define COM_SERIAL_WAIT              100000

/* size of the local packet buffer */
#define COM_INPUT_BUFFER_SIZE          1024

/* This is the interface for the POSIX platform.
 */
typedef struct _COM_interface
{
  // RS232 data:
  int port_fd;
  struct termios options;
  uint32_t baud;

  // RS232 input buffer
  unsigned char ibuf[COM_INPUT_BUFFER_SIZE];
  uint32_t bytes;
  uint32_t type;

} COMInterface_t;

#endif

/* INTERFACE STRUCTURE -- this is only a forward declaration to the
 * structure. We declare a pointer to hide the platform specific code.
 */
typedef struct _COM_interface *pCOMInterface_t;


typedef struct _COM_packet
{
  unsigned char bytes[32];
  uint32_t length;
} COMPacket_t;

/* GENERAL FUNCTIONS */

COM_API uint32_t
_com_write_packet_data(COMInterface_t *iface, COMPacket_t *packet);

COM_API uint32_t
_com_send_packet(COMInterface_t *iface, COMPacket_t *packet);

COM_API uint32_t
_com_get_packet(COMInterface_t *iface);

COM_API uint32_t
com_open_serial(COMInterface_t *iface, const char *device_name);

COM_API uint32_t
com_unread_bytes(COMInterface_t *iface, unsigned char *buffer, uint32_t *buffer_size);

COM_API uint32_t
com_close_serial(COMInterface_t *iface);

extern void _com_append_byte(COMPacket_t *packet, unsigned char byte);
extern void _com_init_packet(COMPacket_t *packet);

/* Utility */
COM_API uint32_t
com_usleep(uint32_t useconds);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif /* __LIBCOM_H__ */
