#ifndef __qms90_h__
#define __qms90_h__
#include "qmx.h"

#define QMX_QMS90_QMS92_OUTPUT_DISABLE	0
#define QMX_QMS90_QMS92_OUTPUT_ENABLE	1

QMX_EXT QMX_API int __stdcall QMX_QMS90_QMS92_OutputEnable(HANDLE SD, BYTE Slot, WORD OutputEn);
QMX_EXT QMX_API int __stdcall QMX_QMS90_QMS92_SetRate(HANDLE SD, BYTE Slot, double DRate, double *CRate);
QMX_EXT QMX_API int __stdcall QMX_QMS90_QMS92_SetOutputs(HANDLE SD, BYTE Slot, WORD State);
QMX_EXT QMX_API int __stdcall QMX_QMS90_QMS92_GetInputs(HANDLE SD, BYTE Slot, WORD *State);

#endif