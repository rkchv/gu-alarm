#ifndef __qms15_h__
#define __qms15_h__
#include "qmx.h"

#define QMX_QMS15_MODE_D	0	// X<->Y
#define QMX_QMS15_MODE_G	1	// GND
#define QMX_QMS15_MODE_X	2	// GND<->X
#define QMX_QMS15_MODE_Y	3	// GND<->Y

#define QMX_QMS15_GAIN_1	1
#define QMX_QMS15_GAIN_2	0
#define QMX_QMS15_GAIN_6	2

QMX_EXT QMX_API int __stdcall QMX_QMS15_SetAdcRate(HANDLE SD, BYTE Slot, double DRate, double *CRate);
QMX_EXT QMX_API int __stdcall QMX_QMS15_SetTable(HANDLE SD, BYTE Slot, WORD *Table, WORD TableLen);
QMX_EXT QMX_API int __stdcall QMX_QMS15_BuildTableItem(HANDLE SD, WORD Channel, WORD Mode, WORD Gain, WORD *Item);
QMX_EXT QMX_API int __stdcall QMX_QMS15_GetAdc(HANDLE SD, BYTE Slot, WORD Mode, WORD *Data);	// Async
QMX_EXT QMX_API int __stdcall QMX_QMS15_WriteCC(HANDLE SD, BYTE Slot, WORD Channel, WORD Mode, WORD Gain, QMX_CC_F *CC);
QMX_EXT QMX_API int __stdcall QMX_QMS15_ReadCC(HANDLE SD, BYTE Slot, WORD Channel, WORD Mode, WORD Gain, QMX_CC_F *CC);

#endif