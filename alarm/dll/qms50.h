#ifndef __qms50_h__
#define __qms50_h__
#include "qmx.h"

#define QMX_QMS50_STROBE_EXT	0
#define QMX_QMS50_STROBE_INT	1

QMX_EXT QMX_API int __stdcall QMX_QMS50_SelectStrobe(HANDLE SD, BYTE Slot, WORD StrobeSrc);
QMX_EXT QMX_API int __stdcall QMX_QMS50_SetRate(HANDLE SD, BYTE Slot, double DRate, double *CRate);
QMX_EXT QMX_API int __stdcall QMX_QMS50_SetIODir(HANDLE SD, BYTE Slot, WORD Dir);
QMX_EXT QMX_API int __stdcall QMX_QMS50_SetIO(HANDLE SD, BYTE Slot, WORD State);
QMX_EXT QMX_API int __stdcall QMX_QMS50_GetIO(HANDLE SD, BYTE Slot, WORD *State);

#endif