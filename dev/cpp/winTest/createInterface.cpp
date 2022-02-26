#include "wintest.h"
HWND hwndHideKey;
HWND hwndKeyEdit;
HWND hwndModeRadio[5];
HWND hwndPassed,hwndFailed;
HWND hwndEncSrcFile,hwndEncDstFile,hwndDecSrcFile,hwndDecDstFile;
HWND hwndEncryptGoBtn,hwndDecryptGoBtn;
WNDPROC stdEditProc;
HWND msgWin,msgCancelBtn;
HWND hwndProgressControl,hwndProgressStatic;
HANDLE hThread;
int msgBtnAct;

static HFONT s_hFont = NULL;

extern HWND hwndMainWindow;
extern HINSTANCE hInst;

int createInterface(HWND hwnd,HINSTANCE hInst){
	const char fontName[] = "Courier";
	const long nFontSize = 10;	
	
	HDC hdc = GetDC(hwnd);
	LOGFONT logFont = {0};
	logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	//logFont.lfWeight = FW_BOLD;
	strcpy(logFont.lfFaceName, fontName);
	s_hFont = CreateFontIndirect(&logFont);
	
	//create UI and change font by Sending Message WM_SETFONT
	
	//Key groupbox
	HWND tmp = 
		CreateWindow("Button","Key:",
			WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
			5,5,390,95,
			hwnd,(HMENU)0,hInst,0
		);
	
	//Hide key checkbox
	tmp =
		CreateWindow(
			"Button","Hide",
			WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
			50,15,55,23,
			hwnd,(HMENU)IDC_HIDEKEY,hInst,0
		);
	
	hwndHideKey = tmp;
	
	//Key edit control
	tmp =
		CreateWindow(
			"Edit","",
			WS_CHILD|WS_VISIBLE|/*ES_AUTOHSCROLL*/ES_LEFT | ES_MULTILINE,
			115,20,265,69,
			hwnd,(HMENU)0,hInst,0
		);
	SendMessage(
		tmp,
		WM_SETFONT, 
		(WPARAM)s_hFont, 
		(LPARAM)MAKELONG(TRUE, 0)
	);
	hwndKeyEdit = tmp;
	stdEditProc = (WNDPROC)SetWindowLongPtr(hwndKeyEdit, GWLP_WNDPROC, (LONG_PTR)keyEditProc);
	
	//Load key button
	tmp =
		CreateWindow(
			"Button","Load",
			WS_CHILD|WS_VISIBLE,
			25,38,75,23,
			hwnd,(HMENU)IDC_KEYSELECT,hInst,0
		);
		
	//Enter key button
	tmp =
		CreateWindow(
			"Button","Enter",
			WS_CHILD|WS_VISIBLE,
			25,65,75,23,
			hwnd,(HMENU)IDC_KEYENTER,hInst,0
		);
		
	
	
	
	// Encrypt groupbox
	tmp = 
		CreateWindow("Button","Encrypt:",
			WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
			5,112,390,95,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	
	//Source file static
	tmp = 
		CreateWindow("Static","Source",
			WS_CHILD|WS_VISIBLE,
			15,140,50,25,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	
	//Source filename edit
	tmp = 
		CreateWindow("Edit","",
			WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,
			75,137,190,25,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndEncSrcFile = tmp;
	
	//Source file load button
	tmp = 
		CreateWindow("Button","...",
			WS_CHILD|WS_VISIBLE,
			280,137,35,25,
			hwnd,(HMENU)IDC_ESFILESEL,hInst,0
		);
	if(!tmp) 
		return -1;
	
	
	//Destination file static
	tmp = 
		CreateWindow("Static","Result",
			WS_CHILD|WS_VISIBLE,
			15,170,50,25,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	
	//Destination filename edit
	tmp = 
		CreateWindow("Edit","",
			WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,
			75,167,190,25,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndEncDstFile = tmp;
	
	//Destination file load button
	tmp = 
		CreateWindow("Button","...",
			WS_CHILD|WS_VISIBLE,
			280,167,35,25,
			hwnd,(HMENU)IDC_EDFILESEL,hInst,0
		);
	if(!tmp) 
		return -1;
	
	//Encrypt GO button
	tmp = 
		CreateWindow("Button","GO",
			WS_CHILD|WS_VISIBLE,
			325,137,55,55,
			hwnd,(HMENU)IDC_ENCRYPTGO,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndEncryptGoBtn = tmp;
	EnableWindow(hwndEncryptGoBtn,FALSE);
	
	
	// Decrypt groupbox
	tmp = 
		CreateWindow("Button","Decrypt:",
			WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
			5,220,390,95,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	
	//Source file static
	tmp = 
		CreateWindow("Static","Source",
			WS_CHILD|WS_VISIBLE,
			15,248,50,25,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	
	//Source filename edit
	tmp = 
		CreateWindow("Edit","",
			WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,
			75,245,190,25,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndDecSrcFile = tmp;
	
	//Source file load button
	tmp = 
		CreateWindow("Button","...",
			WS_CHILD|WS_VISIBLE,
			280,245,35,25,
			hwnd,(HMENU)IDC_DSFILESEL,hInst,0
		);
	if(!tmp) 
		return -1;
	
	
	//Destination file static
	tmp = 
		CreateWindow("Static","Result",
			WS_CHILD|WS_VISIBLE,
			15,278,50,25,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	
	//Destination filename edit
	tmp = 
		CreateWindow("Edit","",
			WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,
			75,275,190,25,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndDecDstFile = tmp;
	
	//Destination file load button
	tmp = 
		CreateWindow("Button","...",
			WS_CHILD|WS_VISIBLE,
			280,275,35,25,
			hwnd,(HMENU)IDC_DDFILESEL,hInst,0
		);
	if(!tmp) 
		return -1;
	
	//Decrypt GO button
	tmp = 
		CreateWindow("Button","GO",
			WS_CHILD|WS_VISIBLE,
			325,245,55,55,
			hwnd,(HMENU)IDC_DECRYPTGO,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndDecryptGoBtn = tmp;
	EnableWindow(hwndDecryptGoBtn,FALSE);
	
	
	// Mode groupbox
	tmp = 
		CreateWindow("Button","Mode:",
			WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
			405,5,100,180,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	
	// 128/128 static
	tmp = 
		CreateWindow("Button","128 / 128",
			WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,
			412,30,80,25,
			hwnd,(HMENU)STN_128128,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndModeRadio[0] = tmp;
	
	// 128/256 static
	tmp = 
		CreateWindow("Button","128 / 256",
			WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,
			412,60,80,25,
			hwnd,(HMENU)STN_128256,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndModeRadio[1] = tmp;
	
	// 256/256 static
	tmp = 
		CreateWindow("Button","256 / 256",
			WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,
			412,90,80,25,
			hwnd,(HMENU)STN_256256,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndModeRadio[2] = tmp;
	
	// 256/512 static
	tmp = 
		CreateWindow("Button","256 / 512",
			WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,
			412,120,80,25,
			hwnd,(HMENU)STN_256512,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndModeRadio[3] = tmp;
	
	// 512/512 static
	tmp = 
		CreateWindow("Button","512 / 512",
			WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,
			412,150,80,25,
			hwnd,(HMENU)STN_512512,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndModeRadio[4] = tmp;
	
	// Self test groupbox
	tmp = 
		CreateWindow("Button","Mode test:",
			WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
			405,197,100,117,
			hwnd,(HMENU)0,hInst,0
		);
	if(!tmp) 
		return -1;
	
	//Green "Passed" static
	tmp = 
		CreateWindow("Static","# - Passed",
			WS_CHILD|WS_VISIBLE|SS_NOTIFY,
			418,222,80,25,
			hwnd,(HMENU)STN_PASSED,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndPassed = tmp;
	
	//Red "Failed" static
	tmp = 
		CreateWindow("Static","# - Failed",
			WS_CHILD|WS_VISIBLE|SS_NOTIFY,
			418,250,80,25,
			hwnd,(HMENU)STN_FAILED,hInst,0
		);
	if(!tmp) 
		return -1;
	hwndFailed = tmp;
	
	
	// Self test start button
	tmp = 
		CreateWindow("Button","Restart",
			WS_CHILD|WS_VISIBLE,
			415,278,75,23,
			hwnd,(HMENU)IDC_SELFTEST,hInst,0
		);
	if(!tmp) 
		return -1;
	
	
	// Generate key button
	tmp = 
		CreateWindow("Button","Generate key",
			WS_CHILD|WS_VISIBLE,
			60,330,95,23,
			hwnd,(HMENU)IDC_KEYGEN,hInst,0
		);
	if(!tmp) 
		return -1;
	
	
	
	// About button
	tmp = 
		CreateWindow("Button","About",
			WS_CHILD|WS_VISIBLE,
			205,330,75,23,
			hwnd,(HMENU)IDC_ABOUT,hInst,0
		);
	if(!tmp) 
		return -1;
	
	// Close button
	tmp = 
		CreateWindow("Button","Close",
			WS_CHILD|WS_VISIBLE,
			365,330,75,23,
			hwnd,(HMENU)IDCLOSE,hInst,0
		);
	if(!tmp) 
		return -1;
	
	msgWin = NULL;
	
	return 0;
}

LRESULT CALLBACK keyEditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
    case WM_CHAR:
		switch (wParam){
		case '0': case '5': 
		case '1': case '6': 
		case '2': case '7': 
		case '3': case '8': 
		case '4': case '9': 
		case 'a': case 'A':
		case 'b': case 'B':
		case 'c': case 'C':
		case 'd': case 'D':
		case 'e': case 'E':
		case 'f': case 'F':
		case VK_BACK:
			break;
		case VK_RETURN:
			SendMessage(hwndMainWindow,WM_COMMAND,IDC_KEYENTER,0);
			return 0;  
		default:
			Beep(1000,150);
			//MessageBeep(MB_ICONSTOP);
			return 0;
		}
    }
   return CallWindowProc(stdEditProc, hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK msgWinProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    switch(msg)
    {
	case WM_CREATE:
		hwndProgressControl = 
			CreateWindowEx(0,PROGRESS_CLASS,"",
				WS_CHILD|WS_VISIBLE|PBS_SMOOTH,
				10,10,270,20,
				hwnd,NULL,hInst,NULL);
		SendMessage(hwndProgressControl, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendMessage(hwndProgressControl, PBM_SETSTEP, (WPARAM) 1, 0); 
		
		hwndProgressStatic = 
			CreateWindow("Static","Processing the data",WS_CHILD|WS_VISIBLE,
				10,45,190,23,
				hwnd,(HMENU)IDCANCEL,hInst,NULL);
		
		msgCancelBtn = 
			CreateWindow("Button","Cancel",WS_CHILD|WS_VISIBLE,
				205,42,75,23,
				hwnd,(HMENU)IDCANCEL,hInst,NULL);
		msgBtnAct = MSGBTNACT_TERMINATE;
				
		hThread = NULL;
		PostMessage(hwnd,WM_PREPARED,0,0);
		break;
	case WM_PREPARED:
		if(NULL==hThread)
			hThread = CreateThread(NULL,0,decryptStart,NULL,0,NULL);
		
		break;
	case WM_CLOSE: 
		EnableWindow(hwndMainWindow, TRUE);
		ShowWindow(hwndMainWindow,SW_RESTORE);
		SetFocus(hwndMainWindow);
		//return 0;
        break;
	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case IDCANCEL:
			switch(msgBtnAct){
			case MSGBTNACT_TERMINATE:
				TerminateThread(hThread,ABORTED_BY_USER);
				SendMessage(msgCancelBtn,WM_SETTEXT,0,(LPARAM)"Exit");
				SendMessage(hwndProgressStatic,WM_SETTEXT,0,(LPARAM)"Process aborted by user");
				msgBtnAct = MSGBTNACT_CLOSEWIN;
				//SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,ABORTED_BY_USER);
				break;
			case MSGBTNACT_CLOSEWIN:
				SendMessage(msgWin,WM_CLOSE,0,0);
				break;
			}
			break;
		case IDC_THREADSTOP:
			switch(lParam){
			case MEM_ALLOC_ERROR:
				MessageBox(hwnd, "Out of memory. Restart program.","Decryption failed",MB_OK|MB_ICONSTOP);
				break;
			case KEY_NO_ENTERED:
				MessageBox(hwnd,"Enter or load key","Decryption fail",MB_OK|MB_ICONEXCLAMATION);
				break;
			case FILE_NO_SELECT:
				MessageBox(hwnd,"Select file to decrypt","Decryption fail",MB_OK|MB_ICONEXCLAMATION);
				break;
			case FILE_WRITE_DATA_ERROR:
				MessageBox(hwnd,"Error writing file","Decryption fail",MB_OK|MB_ICONEXCLAMATION);
				break;
			case ENCRYPT_INNER_ERROR:
				MessageBox(hwnd,"Error in decryption module","Decryption fail",MB_OK|MB_ICONEXCLAMATION);
				break;
			case FILE_READ_DATA_ERROR:
				MessageBox(hwnd,"Error reading file data","Decryption fail",MB_OK|MB_ICONEXCLAMATION);
				break;
			case FILE_WRONG_SIZE:
				MessageBox(hwnd,"Wrong file size","Decryption fail",MB_OK|MB_ICONEXCLAMATION);
				break;
			case DECRYPT_SIZE_RESTORE_ERROR:
				MessageBox(hwnd,"Error restoring file size. Possible incorrect password","Decryption fail",MB_OK|MB_ICONEXCLAMATION);
				break;
			case USER_CANCEL:
				MessageBox(hwnd,"Decryption cancelled","Decryption process",MB_OK|MB_ICONINFORMATION);
				break;
			case NORMAL_FINISH:
				SendMessage(hwndProgressStatic,WM_SETTEXT,0,(LPARAM)"Process finish successfully");
				SendMessage(msgCancelBtn,WM_SETTEXT,0,(LPARAM)"Exit");
				return 0;
			default:
				MessageBox(hwnd,"Decryption error (def)","Decryption process",MB_OK|MB_ICONEXCLAMATION);
			}
			SendMessage(msgWin,WM_CLOSE,0,0);
			//return 0;
			break;
		}
		break;
    }

    return DefWindowProc(hwnd,msg,wParam,lParam);
}

int showAbout(){
	showProgress();
	return NORMAL_FINISH;
}

int showProgress(){
	if(NULL==msgWin){
		WNDCLASSEX wc; 
		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpfnWndProc	 = msgWinProc; 
		wc.hInstance	 = hInst;
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(5);//COLOR_APPWORKSPACE
		wc.lpszClassName = "msgWindow";
		wc.hIcon		 = NULL;//LoadIcon(NULL, IDI_APPLICATION); 
		wc.hIconSm		 = NULL;//LoadIcon(NULL, IDI_APPLICATION); 
	
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "Window Class Registration Failure","Program terminated",MB_ICONSTOP|MB_OK);
			return 0;
		}
	}
	int W = 300;
	int H = 110;
	msgWin = CreateWindowEx(WS_EX_CLIENTEDGE,
		"msgWindow","Process monitor",
		WS_VISIBLE|WS_OVERLAPPEDWINDOW&~(WS_THICKFRAME|WS_MAXIMIZEBOX),
		(GetSystemMetrics(SM_CXSCREEN)-W)/2,(GetSystemMetrics(SM_CYSCREEN)-H)/2,W,H, 
		hwndMainWindow,NULL,hInst,NULL);
	
	if(msgWin == NULL){
		MessageBox(NULL, "Window Creation Failed!","Program terminated",MB_ICONSTOP|MB_OK);
		return 0;
	}
	EnableWindow(hwndMainWindow, FALSE);
	ShowWindow(msgWin,SW_SHOW);
	SetFocus(msgWin);
	return NORMAL_FINISH;
}
