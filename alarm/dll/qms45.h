#ifndef __qms45_h__
#define __qms45_h__
#include "qmx.h"

QMX_EXT QMX_API int __stdcall QMX_QMS45_SetDacRate(HANDLE SD, BYTE Slot, double DRate, double *CRate);
QMX_EXT QMX_API int __stdcall QMX_QMS45_SetMode(HANDLE SD, BYTE Slot, BYTE Mode);	
QMX_EXT QMX_API int __stdcall QMX_QMS45_SetDac(HANDLE SD, BYTE Slot, BYTE Channel, WORD Data);	// Async
QMX_EXT QMX_API int __stdcall QMX_QMS45_EnableDac(HANDLE SD, BYTE Slot, BYTE Enable);	// Async
QMX_EXT QMX_API int __stdcall QMX_QMS45_ReadCC(HANDLE SD, BYTE Slot, WORD Channel, QMX_CC_F *CC);
QMX_EXT QMX_API int __stdcall QMX_QMS45_WriteCC(HANDLE SD, BYTE Slot, WORD Channel, QMX_CC_F *CC);


#endif