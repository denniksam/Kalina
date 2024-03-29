#include "wintest.h"

HWND hwndMainWindow;
	
extern HWND hwndHideKey,hwndKeyGrp;
extern HWND hwndKeyEdit;
extern HWND hwndModeRadio[5];
extern HWND hwndPassed,hwndFailed;
extern TSample sample[5];
extern TKeyData keyData;
extern TWorkMode workMode;
extern HWND hwndEncryptGoBtn,hwndDecryptGoBtn;

bool tmpFlag;
char tmpStr[256];

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	switch(Message) {
		case WM_CREATE:
			if(loadDll() != NORMAL_FINISH){
				MessageBox(hwnd,"Error DLL loading","Program stopped",IDOK|MB_ICONSTOP);
				PostMessage(hwnd,WM_CLOSE,0,0);
				return EXIT_FAILURE;
			}
			createInterface(hwnd,hInst);
			if(!fillSample()){
				MessageBox(hwnd,"Error self-test preparing","Program stopped",IDOK|MB_ICONSTOP);
				PostMessage(hwnd,WM_CLOSE,0,0);
				return EXIT_FAILURE;
			}
			selfTest();
			SendMessage(hwndHideKey, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(hwndKeyEdit,EM_SETPASSWORDCHAR,'*',0);
			workMode.blockSize = 128;
			workMode.keySize = 128;
			workMode.direction = WORKMODE_UNKNOWN;
			SendMessage(hwndModeRadio[0],BM_SETCHECK,1,0);
			workMode.blockSize = 128;
			workMode.keySize = 128;
			keyData.rawKey = (byte*)0;
			keyData.expandedKey = (byte*)0;
			keyData.keyStatus = KEY_STATUS_EMPTY;
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDC_SELFTEST:
					selfTest();
					for(int i=0;i<5;i++)
						InvalidateRect(hwndModeRadio[i],NULL,TRUE);
					showTestResult(hwnd);
					break;
				case IDC_KEYSELECT:
					switch(loadKey(hwnd)){
					case FILE_OPEN_ERROR:
						MessageBox(hwnd, "File open error","Key load failure",MB_OK|MB_ICONEXCLAMATION);
						return 0;
					case USER_CANCEL:
						MessageBox(hwnd, "Key installation cancelled","Key load",MB_OK|MB_ICONINFORMATION);
						return 0;
					}
					//break; //no break - enter key after loading
				case IDC_KEYENTER:
					InvalidateRect(hwndKeyGrp,NULL,TRUE);
					switch(enterKey()){
					case KEY_INVALID_SIZE:
						SendMessage(hwndKeyEdit,WM_GETTEXT,130,(LPARAM)tmpStr);
						sprintf(tmpStr,"Invalid key size\n%d bit key length detected",4*strlen(tmpStr));
						MessageBox(hwnd, tmpStr,"Key install failure",MB_OK|MB_ICONEXCLAMATION);
						break;
					case KEY_TOO_SMALL:
						sprintf(tmpStr,"Entered key size %d bit\ntoo small for %d / %d work mode",keyData.keySize,workMode.blockSize,workMode.keySize);
						MessageBox(hwnd, tmpStr,"Key install failure",MB_OK|MB_ICONEXCLAMATION);
						break;
					case KEY_PARSE_ERROR:
						MessageBox(hwnd, "Invalid key format","Key install failure",MB_OK|MB_ICONEXCLAMATION);
						break;
					case KEY_EXPAND_ERROR:
						MessageBox(hwnd, "Key expand error","Key install failure",MB_OK|MB_ICONEXCLAMATION);
						break;
					case MEM_ALLOC_ERROR:
						MessageBox(hwnd, "Out of memory","Key install failure",MB_OK|MB_ICONSTOP);
						break;
					case NORMAL_FINISH:
						sprintf(tmpStr,"Key install successfully.\nWork mode - %d / %d\n(entered key size - %d)",workMode.blockSize,workMode.keySize,keyData.keySize);
						MessageBox(hwnd, tmpStr,"Key installation",MB_OK|MB_ICONINFORMATION);
						EnableWindow(hwndEncryptGoBtn,TRUE);
						EnableWindow(hwndDecryptGoBtn,TRUE);
						return 0;
					default:
						MessageBox(hwnd, "Key load failure","Key install failure",MB_OK|MB_ICONEXCLAMATION);
					}
					EnableWindow(hwndEncryptGoBtn,FALSE);
					EnableWindow(hwndDecryptGoBtn,FALSE);
					break;
				case IDC_HIDEKEY:
					if (BST_CHECKED==SendMessage(hwndHideKey, BM_GETCHECK, 0, 0)) {
						SendMessage(hwndHideKey, BM_SETCHECK, BST_UNCHECKED, 0);
						SendMessage(hwndKeyEdit,EM_SETPASSWORDCHAR,0,0);
						//if(keyData.rawKey)
						//	SendMessage(hwndKeyEdit,WM_SETTEXT,0,(LPARAM)pbyte2str(keyData.keySize,keyData.rawKey));
					}
					else {
						SendMessage(hwndHideKey, BM_SETCHECK, BST_CHECKED, 0);
						SendMessage(hwndKeyEdit,EM_SETPASSWORDCHAR,'*',0);
						//if(keyData.rawKey){
						//	sprintf(tmpStr,"%0128d",0);
						//	SendMessage(hwndKeyEdit,WM_SETTEXT,0,(LPARAM)tmpStr);
						//}
					}
					InvalidateRect(hwndKeyEdit,NULL,TRUE);
					break;
				case IDC_ABOUT:
					showAbout();
					break;
				case IDC_KEYGEN:
					keyGen();
					break;
				case STN_128128:
					for(int i=0;i<5;i++)SendMessage(hwndModeRadio[i],BM_SETCHECK,0,0);
					SendMessage(hwndModeRadio[0],BM_SETCHECK,1,0);
					workMode.blockSize = 128;
					workMode.keySize = 128;
					refreshKey();
					break;
				case STN_128256:
					for(int i=0;i<5;i++)SendMessage(hwndModeRadio[i],BM_SETCHECK,0,0);
					SendMessage(hwndModeRadio[1],BM_SETCHECK,1,0);
					workMode.blockSize = 128;
					workMode.keySize = 256;
					refreshKey();
					break;
				case STN_256256:
					for(int i=0;i<5;i++)SendMessage(hwndModeRadio[i],BM_SETCHECK,0,0);
					SendMessage(hwndModeRadio[2],BM_SETCHECK,1,0);
					workMode.blockSize = 256;
					workMode.keySize = 256;
					refreshKey();
					break;
				case STN_256512:
					for(int i=0;i<5;i++)SendMessage(hwndModeRadio[i],BM_SETCHECK,0,0);
					SendMessage(hwndModeRadio[3],BM_SETCHECK,1,0);
					workMode.blockSize = 256;
					workMode.keySize = 512;
					refreshKey();
					break;
				case STN_512512:
					for(int i=0;i<5;i++)SendMessage(hwndModeRadio[i],BM_SETCHECK,0,0);
					SendMessage(hwndModeRadio[4],BM_SETCHECK,1,0);
					workMode.blockSize = 512;
					workMode.keySize = 512;
					refreshKey();
					break;
				case STN_PASSED:
				case STN_FAILED:
					showTestResult(hwnd);
					break;
				case IDC_ESFILESEL:
				case IDC_EDFILESEL:
				case IDC_DSFILESEL:
				case IDC_DDFILESEL:
					fileSelect(hwnd,LOWORD(wParam));
					break;
				case IDC_ENCRYPTGO:
					workMode.direction = WORKMODE_ENCRYPTION;
					showProgress();
					break;
				case IDC_DECRYPTGO:
					workMode.direction = WORKMODE_DECRYPTION;
					showProgress();
					break;
				case IDCLOSE:
					PostMessage(hwnd,WM_CLOSE,0,0);
					break;
			}
			break;
		case WM_KEYUP:
			switch(wParam){
				case VK_ESCAPE:
					//PostMessage(hwnd,WM_CLOSE,0,0);
					break;
			}
			break;
		case WM_CTLCOLORSTATIC:	
			HDC hdc = (HDC)wParam;
			HWND ctl = (HWND)lParam;
			if(ctl == hwndKeyGrp){
				switch(keyData.keyStatus){
				case KEY_STATUS_REJECTED:
					SetTextColor(hdc,RGB(250,0,0));
					SetBkColor(hdc,GetSysColor(COLOR_BTNFACE));
					return (LRESULT)GetStockObject(NULL_BRUSH);
				case KEY_STATUS_ACCEPTED:
					SetTextColor(hdc,RGB(0,200,0));
					SetBkColor(hdc,GetSysColor(COLOR_BTNFACE));
					return (LRESULT)GetStockObject(NULL_BRUSH);
				}
			}
			if(ctl == hwndPassed){
				SetTextColor(hdc,RGB(0,200,0));
				SetBkMode(hdc,TRANSPARENT);
				return (LRESULT)GetStockObject(NULL_BRUSH);
			}
			if(ctl == hwndFailed){
				SetTextColor(hdc,RGB(250,0,0));
				SetBkMode(hdc,TRANSPARENT);
				return (LRESULT)GetStockObject(NULL_BRUSH);
			}
			for(int i=0;i<5;i++)
				if(ctl == hwndModeRadio[i]){
					//if(sample[i].
					SetTextColor(hdc,((sample[i].eStatus==1&&sample[i].dStatus==1)?RGB(0,200,0):RGB(250,0,0)));
					SetBkMode(hdc,TRANSPARENT);
					return (LRESULT)GetStockObject(NULL_BRUSH);
				}
			return DefWindowProc(hwnd,Message,wParam,lParam);
			break;
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; 
	MSG msg; 
	
	hInst = hInstance;
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; 
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(5);//COLOR_APPWORKSPACE
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); 

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Class Registration Failure","Program terminated",MB_ICONSTOP|MB_OK);
		return 0;
	}

	hwndMainWindow = CreateWindowEx(WS_EX_CLIENTEDGE,
		"WindowClass","Kalina crypto for win32",
		WS_VISIBLE|WS_OVERLAPPEDWINDOW&~(WS_THICKFRAME|WS_MAXIMIZEBOX),
		CW_USEDEFAULT,CW_USEDEFAULT,530,410, 
		NULL,NULL,hInstance,NULL);

	if(hwndMainWindow == NULL){
		MessageBox(NULL, "Window Creation Failed!","Program terminated",MB_ICONSTOP|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0){
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}
	return msg.wParam;
}

