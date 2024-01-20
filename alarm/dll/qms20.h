#ifndef __qms20_h__
#define __qms20_h__
#include "qmx.h"

#define QMX_QMS20_MODE_D	0	// X<->Y
#define QMX_QMS20_MODE_G	1	// GND


#define QMX_QMS20_GAIN_1	0
#define QMX_QMS20_GAIN_5	1

QMX_EXT QMX_API int __stdcall QMX_QMS20_SetAdcRate(HANDLE SD, BYTE Slot, double DRate, double *CRate);
QMX_EXT QMX_API int __stdcall QMX_QMS20_SetTable(HANDLE SD, BYTE Slot, WORD *Table, WORD TableLen);
QMX_EXT QMX_API int __stdcall QMX_QMS20_BuildTableItem(HANDLE SD, WORD Channel, WORD Mode, WORD Gain, WORD *Item);
QMX_EXT QMX_API int __stdcall QMX_QMS20_CheckDacPresence(HANDLE SD, BYTE Slot, BYTE *PFlag);
QMX_EXT QMX_API int __stdcall QMX_QMS20_SetDac(HANDLE SD, BYTE Slot, BYTE Channel, short Data);	// Async
QMX_EXT QMX_API int __stdcall QMX_QMS20_GetAdc(HANDLE SD, BYTE Slot, WORD Mode, WORD *Data);	// Async
QMX_EXT QMX_API int __stdcall QMX_QMS20_WriteCC(HANDLE SD, BYTE Slot, WORD Channel, WORD Gain, QMX_CC_F *CC);
QMX_EXT QMX_API int __stdcall QMX_QMS20_ReadCC(HANDLE SD, BYTE Slot, WORD Channel, WORD Gain, QMX_CC_F *CC);

#endif