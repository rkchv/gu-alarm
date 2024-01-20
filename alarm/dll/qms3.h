#ifndef __qms3_h__
#define __qms3_h__
#include "qmx.h"

// Submodules types
#define QMX_QMS3_SUB_MOD_NONE	0x00	// no submod in subslot
#define QMX_QMS3_SUB_MOD_S10	0x10	// Тензомост		3 slots

#define QMX_QMS3_SUB_MOD_S20	0x20	// Ток
#define QMX_QMS3_SUB_MOD_S21	0x21	// Ток -5..+5 mA
#define QMX_QMS3_SUB_MOD_S22	0x22	// Ток 0.. 5 mA
#define QMX_QMS3_SUB_MOD_S23	0x23	// Ток 0.. 20 mA

#define QMX_QMS3_SUB_MOD_S30	0x30	// Напряжение
#define QMX_QMS3_SUB_MOD_S40	0x40	// Термопара
#define QMX_QMS3_SUB_MOD_S50	0x50	// Сопротивление	2 slots
#define QMX_QMS3_SUB_MOD_S60	0x60	// Частота
#define QMX_QMS3_SUB_MOD_S70	0x70	// ЦАП напряжение
#define QMX_QMS3_SUB_MOD_S80	0x80	// ЦАП ток

typedef struct QMS3_CONFIG QMS3_CONFIG;

struct QMS3_CONFIG {
 BYTE SubModules[16];
};

QMX_EXT QMX_API int __stdcall QMX_QMS3_GetConfiguration(HANDLE SD, BYTE Slot, QMS3_CONFIG *Config);
QMX_EXT QMX_API int __stdcall QMX_QMS301_WriteCC(HANDLE SD, BYTE Slot, BYTE SubSlot, QMX_CC_F *CC);
QMX_EXT QMX_API int __stdcall QMX_QMS301_ReadCC(HANDLE SD, BYTE Slot, BYTE SubSlot, QMX_CC_F *CC);

#endif