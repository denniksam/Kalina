#if !defined(WINTEST_H)
#define WINTEST_H
#ifdef UNICODE
#undef UNICODE
#endif

#define WINVER 0x0501

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#define IDC_SELFTEST	1001
#define IDC_KEYSELECT	1002
#define IDC_HIDEKEY		1003
#define IDC_ABOUT		1004
#define IDC_HLP			1005
#define IDC_ESFILESEL	1006
#define IDC_EDFILESEL	1007
#define IDC_DSFILESEL	1008
#define IDC_DDFILESEL	1009
#define IDC_ENCRYPTGO	1010
#define IDC_DECRYPTGO	1011
#define IDC_KEYENTER	1012
#define IDC_THREADSTOP	1013

#define STN_128128		1021
#define STN_128256		1022
#define STN_256256		1023
#define STN_256512		1024
#define STN_512512		1025
#define STN_PASSED		1026
#define STN_FAILED		1027

#define DLL_DECRYPT_LOCATE_ERROR	10101
#define DLL_ENCRYPT_LOCATE_ERROR	10102
#define DLL_EXPAND_LOCATE_ERROR		10103
#define DLL_LOAD_ERROR				10104
#define DECRYPT_SIZE_RESTORE_ERROR	10105
#define ENCRYPT_INNER_ERROR			10106
#define FILE_NO_SELECT				10107
#define FILE_OPEN_ERROR				10108
#define FILE_READ_DATA_ERROR		10109
#define FILE_WRITE_DATA_ERROR		10110
#define FILE_WRONG_SIZE				10111
#define KEY_INVALID_FORMAT			10112
#define KEY_INVALID_SIZE			10113
#define KEY_PARSE_ERROR				10114
#define KEY_EXPAND_ERROR			10115
#define MEM_ALLOC_ERROR				10116
#define KEY_NO_ENTERED				10117
#define ABORTED_BY_USER				10118

#define NORMAL_FINISH	1
#define USER_CANCEL		0

#define WORKMODE_ENCRYPTION		2
#define WORKMODE_DECRYPTION		4
#define WORKMODE_UNKNOWN		0

typedef unsigned char byte;
typedef byte (*pmul)(byte,byte);
typedef byte* (*lpfnexpandKey)(int, int, const byte *, byte *);
typedef byte* (*lpfncrypt)(int, int, byte*, const byte*, bool);
typedef struct {
	int blockSize,keySize;
	byte *eBlock,*eKey,*eRes,*eAns;
	byte *dBlock,*dKey,*dRes,*dAns;
	int eStatus,dStatus;
} TSample;
typedef struct {
	byte *rawKey;
	byte *expandedKey;
	int keySize,blockSize;
}TKeyData;
typedef struct {
	int keySize,blockSize;
	int direction;
}TWorkMode;
	
char *pbyte2str(int,const byte *);
bool fillSample();
byte* str2pbyte(char*);
int createInterface(HWND,HINSTANCE);
int selfTest();
int loadDll();
int loadKey(HWND);
int enterKey();
int showTestResult(HWND);
int fileSelect(HWND,int);
DWORD WINAPI encryptGo();
DWORD WINAPI decryptGo();
DWORD WINAPI decryptStart(void*);
LRESULT CALLBACK keyEditProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
int showAbout();
int showProgress();

#endif
