#ifndef __qm14_h__
#define __qm14_h__
#include "qmx.h"

#define QM14_TEST_MODE_1234	0	// 0 .. 0xffff
#define QM14_TEST_MODE_00FF	1
#define QM14_TEST_MODE_AA55	2

QMX_EXT QMX_API int __stdcall QMX_QM14_SetTestMode(HANDLE SD, BYTE Slot, WORD Mode);
QMX_EXT QMX_API int __stdcall QMX_QM14_SetSpeed(HANDLE SD, BYTE Slot, DWORD DSpeed, DWORD *CSpeed);

#endif

