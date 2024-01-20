#ifndef __qms3_h__
#define __qms3_h__
#include "qmx.h"

// Submodules types
#define QMX_QMS3_SUB_MOD_NONE	0x00	// no submod in subslot
#define QMX_QMS3_SUB_MOD_S10	0x10	// ���������		3 slots

#define QMX_QMS3_SUB_MOD_S20	0x20	// ���
#define QMX_QMS3_SUB_MOD_S21	0x21	// ��� -5..+5 mA
#define QMX_QMS3_SUB_MOD_S22	0x22	// ��� 0.. 5 mA
#define QMX_QMS3_SUB_MOD_S23	0x23	// ��� 0.. 20 mA

#define QMX_QMS3_SUB_MOD_S30	0x30	// ����������
#define QMX_QMS3_SUB_MOD_S40	0x40	// ���������
#define QMX_QMS3_SUB_MOD_S50	0x50	// �������������	2 slots
#define QMX_QMS3_SUB_MOD_S60	0x60	// �������
#define QMX_QMS3_SUB_MOD_S70	0x70	// ��� ����������
#define QMX_QMS3_SUB_MOD_S80	0x80	// ��� ���

typedef struct QMS3_CONFIG QMS3_CONFIG;

struct QMS3_CONFIG {
 BYTE SubModules[16];
};

QMX_EXT QMX_API int __stdcall QMX_QMS3_GetConfiguration(HANDLE SD, BYTE Slot, QMS3_CONFIG *Config);
QMX_EXT QMX_API int __stdcall QMX_QMS301_WriteCC(HANDLE SD, BYTE Slot, BYTE SubSlot, QMX_CC_F *CC);
QMX_EXT QMX_API int __stdcall QMX_QMS301_ReadCC(HANDLE SD, BYTE Slot, BYTE SubSlot, QMX_CC_F *CC);

#endif