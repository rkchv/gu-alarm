#ifndef __qms10_h__
#define __qms10_h__
#include "qmx.h"

#define QMX_QMS10_MODE_D	0	// X<->Y
#define QMX_QMS10_MODE_G	1	// GND
#define QMX_QMS10_MODE_X	2	// GND<->X
#define QMX_QMS10_MODE_Y	3	// GND<->Y

#define QMX_QMS10_GAIN_1	0
#define QMX_QMS10_GAIN_4	1
#define QMX_QMS10_GAIN_16	2
#define QMX_QMS10_GAIN_64	3

QMX_EXT QMX_API int __stdcall QMX_QMS10_SetAdcRate(HANDLE SD, BYTE Slot, double DRate, double *CRate);
QMX_EXT QMX_API int __stdcall QMX_QMS10_SetTable(HANDLE SD, BYTE Slot, WORD *Table, WORD TableLen);
QMX_EXT QMX_API int __stdcall QMX_QMS10_BuildTableItem(HANDLE SD, WORD Channel, WORD Mode, WORD Gain, WORD *Item);
QMX_EXT QMX_API int __stdcall QMX_QMS10_CheckDacPresence(HANDLE SD, BYTE Slot, BYTE *PFlag);
QMX_EXT QMX_API int __stdcall QMX_QMS10_SetDac(HANDLE SD, BYTE Slot, BYTE Channel, short Data);	// Async
QMX_EXT QMX_API int __stdcall QMX_QMS10_GetAdc(HANDLE SD, BYTE Slot, WORD Mode, WORD *Data);	// Async
QMX_EXT QMX_API int __stdcall QMX_QMS10_WriteCC(HANDLE SD, BYTE Slot, WORD Gain, QMX_CC_F *CC);
QMX_EXT QMX_API int __stdcall QMX_QMS10_ReadCC(HANDLE SD, BYTE Slot, WORD Gain, QMX_CC_F *CC);

#endif