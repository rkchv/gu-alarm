#ifndef __qmx_h__
#define __qmx_h__
#include <windows.h>

#if defined(QMX_BUILD_DLL)
 #define QMX_API __declspec(dllexport)
 #define QMX_EXT extern "C"
#elif defined(QMX_BUILD_APP)
 #define QMX_API
 #if defined(_CVI_)
  #define QMX_EXT extern
 #else
  #define QMX_EXT extern "C"
 #endif
#else
 #define QMX_API __declspec(dllimport)
 #if defined(_CVI_)
  #define QMX_EXT extern
 #else
  #define QMX_EXT extern "C"
 #endif
#endif

typedef struct QMX_CONFIG QMX_CONFIG;		// ������������ ������, ����������� QMX_Open() � QMX_Prepare()
typedef struct QMX_CC_F QMX_CC_F;		// ������������� ������������ float
typedef struct QMX_CC_D QMX_CC_D;		// ������������� ������������ double
typedef struct QMX_CIRC_BUF QMX_CIRC_BUF;	// ��������� �����
typedef struct QMX_CIRC_BUF_CONFIG QMX_CIRC_BUF_CONFIG;

QMX_EXT QMX_API int __stdcall QMX_GetDllVersion(void); // ToDo: !!!
QMX_EXT QMX_API int __stdcall QMX_GetLastError(HANDLE SD, char *str, DWORD len);
QMX_EXT QMX_API int __stdcall QMX_GetLastErrorForSlot(BYTE Slot, char *str, DWORD len);
QMX_EXT QMX_API HANDLE __stdcall QMX_Open(WORD VirtualSlot);
QMX_EXT QMX_API int __stdcall QMX_InitModules(HANDLE SD, WORD LogLevel, BYTE *FaulSlot);
QMX_EXT QMX_API int __stdcall QMX_GetConfiguration(HANDLE SD, QMX_CONFIG *Config);
QMX_EXT QMX_API int __stdcall QMX_Close(HANDLE SD);
QMX_EXT QMX_API int __stdcall QMX_Prepare(HANDLE SD, WORD ResponseTime, QMX_CONFIG *Config);
QMX_EXT QMX_API int __stdcall QMX_Start(HANDLE SD); // (crate (transfer) + modules)
QMX_EXT QMX_API int __stdcall QMX_Stop(HANDLE SD, WORD Mode); //(crate (transfer))
QMX_EXT QMX_API int __stdcall QMX_MOD_OutputPrestage(HANDLE SD, BYTE Slot);
QMX_EXT QMX_API int __stdcall QMX_MOD_SetActive(HANDLE SD, BYTE Slot, BYTE IsActive);
QMX_EXT QMX_API int __stdcall QMX_MOD_SetStartMode(HANDLE SD, BYTE Slot, BYTE Mode);

// ������ � ���������� �������� ============================================================
QMX_EXT QMX_API HANDLE __stdcall QMX_CircBufAttach(WORD VirtualSlot);
QMX_EXT QMX_API int __stdcall QMX_CircBufDetach(HANDLE SD);
QMX_EXT QMX_API int __stdcall QMX_CircBufSetChannels(HANDLE SD, BYTE Slot, BYTE Channels);
QMX_EXT QMX_API int __stdcall QMX_CircBufSetStorePath(HANDLE SD, char *Path);
QMX_EXT QMX_API int __stdcall QMX_CircBufOutputUpdate(HANDLE SD);

// �������������� ������� ==================================================================
//QMX_EXT QMX_API int __stdcall QMX_PutQMbus(QMX_SYSTEM *SD, WORD BusAddress, WORD N, WORD *Data);
//QMX_EXT QMX_API int __stdcall QMX_GetQMbus(QMX_SYSTEM *SD, WORD BusAddress, WORD N, WORD *Data);


#pragma pack(push)
#pragma pack(1)

struct QMX_CIRC_BUF_CONFIG {
 volatile WORD *buf_start;				// ��������� �� ������ ������
 volatile DWORD *buf_ptr;				// ��������� ������ � ����� [0..buf_size-1]
 volatile DWORD *buf_cntr;				// ������� ������ � ����� [0..2^32]
 volatile DWORD *buf_size;				// ������ ������ � ������ (WORD)
 volatile HANDLE event;
};


// ��������� ������������ ������
struct QMX_CONFIG {
// ���� ��������� ����� QMX_Open();
 BYTE 		  	UsbSpeed;	       		// ������� �������� USB
 CHAR		  	CtlName[11];         		// �������� �����������
 CHAR		  	CtlBIOSversion[6];   		// ������ ����� �����������
 CHAR		  	CtlSerialNumber[10]; 		// �������� ����� �����������
 BYTE 		  	ModQuantity;         		// ���������� ������� � �������
 CHAR		  	ModName[8][10];      		// ����� �������
 WORD		  	ModType[8];      		// ���� �������
 BYTE		  	ModRevision[8];   		// ������� ������
 CHAR		  	ModSerialNumber[8][10];		// �������� ����� ������
 HANDLE           	DevHandle;			// ����� ��������
// ���� ��������� ����� QMX_Prepare();
 WORD   	  	RespTime;	   		// ���������� ����� ������� � ��
 DWORD  	  	ReadFileSize;	   		// ������ �������� � ������
 DWORD  	  	WriteFileSize;   		// ������ ��������� � ������
 DWORD		  	ModLocalBufferSize[8];		// ������ �������� ���������� ������-1 (� ������)
 double		  	InputRate;			// �������� ����� ������ (����) � ���
 double		  	OutputRate;			// �������� ������ ������ (����) � ���
 QMX_CIRC_BUF_CONFIG    CBInput;			// ������������ ���������� ������ �����
 QMX_CIRC_BUF_CONFIG    CBOutput;			// ������������ ���������� ������ ������
};

// ������������� ������������
struct QMX_CC_F {
 float Offset;
 float Scale;
 char Units[6];
 BYTE UnitsCode;				// ���������������
};

struct QMX_CC_D {
 double Offset;
 double Scale;
 char Units[6];
 BYTE UnitsCode;				// ���������������
};

#pragma pack(pop)

//�������� �������� �������. ��� ������� QMX_Stop()
#define QMX_STOP_ALL		0
#define QMX_STOP_TRANSFER_IN	1
#define QMX_STOP_TRANSFER_OUT	2

//���� �������. QMX_CONFIG->ModType[]
#define QMX_MOD_NONE		0x0000		// ������ ������ ������������� �� ����� �����������
#define QMX_MOD_QM14		0x000E
#define QMX_MOD_QMS301		0x012D
#define QMX_MOD_QMS10		0x000A
#define QMX_MOD_QMS15		0x000F
#define QMX_MOD_QMS20		0x0014
#define QMX_MOD_QMS40		0x0028
#define QMX_MOD_QMS45		0x002D
#define QMX_MOD_QMS50		0x0032
#define QMX_MOD_QMS60		0x003C
#define QMX_MOD_QMS70		0x0046
#define QMX_MOD_QMS75		0x004B
#define QMX_MOD_QMS90		0x005A
#define QMX_MOD_QMS92		0x005C

//==============================================================================
#define QMX_OFF     		0
#define QMX_ON	                1

//������� ������� ������. ��� QMX_MOD_SetStartMode
#define QMX_START_MODE_MANUAL	0		// ������ ������ ��� ����������� �������� QMX_Start()
#define QMX_START_MODE_EXTERNAL	1		// ������ ������ ��� ����������� �� �������� ������� ����� QMX_Start()

// ��������� ������� ������ ���������� ���������� ��� ������� QMX_Open()
#define QMX_LOG_NONE		0		// �� �������� �����
#define QMX_LOG_TO_FILE		1		// �������� ����� � ����

// ���� ������ =================================================================
#define QMX_OK         		        	0L	//
#define QMX_ERR         	        	-1L	//
#define QMXE_INTERNAL_ERROR			0x80000000//
#define QMXE_INVALID_OS                		2L	//
#define QMXE_DEVICE_OPEN                	3L	//
#define QMXE_DEVICE_CLOSE               	4L	//
#define QMXE_FPGA_FIRMWARE_FILE_OPEN    	5L	//
#define QMXE_WRITE_PROHIBITED_REGION    	7L	// ToDo: !!!
#define QMXE_NO_ACTIVE_MODULES          	8L	//
#define QMXE_ACTIVE_OUTPUT_EXCEEDING    	9L	//
#define QMXE_MAX_SPEED_EXCEEDING        	10L	//
#define QMXE_ACTIVE_MODULE_ZERO_SPEED		11L	//
#define QMXE_BAD_PARAMETER                  	12L	//
#define QMXE_INVALID_DESCRIPTOR                 13L	//
#define QMXE_DATA_FLOW_CORRUPTED               	14L	//
#define QMXE_BUFFER_OVERFLOW		       	15L	//
#define QMXE_DISK_WRITE_ERROR		       	16L	//
#define QMXE_DATA_SERVER_ATTACH		       	17L	//
#define QMXE_ALREADY_STARTED			18L	//

// ������������������ ������� ==================================================
#include "qms3.h"
#include "qms10.h"
#include "qms15.h"
#include "qms20.h"
#include "qms45.h"
#include "qms50.h"
#include "qms70.h"
#include "qms75.h"
#include "qms90.h"
#include "qm14.h"

#endif
