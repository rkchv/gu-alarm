#ifndef __qms70_h__
#define __qms70_h__
#include "qmx.h"

//QMX_API int __stdcall QMX_QMS70_SetRate(HANDLE SD, BYTE Slot, double DRate, double *CRate);
QMX_EXT QMX_API int __stdcall QMX_QMS70_GetAllChannels(HANDLE SD, BYTE Slot, WORD *Data);	// Async

#endif