#include "wintest.h"

lpfnexpandKey expandKey;
lpfncrypt encrypt,decrypt;

TKeyData keyData;
TWorkMode workMode;

extern HWND hwndMainWindow;
extern HWND hwndHideKey, hwndKeyEdit;
extern HWND hwndEncSrcFile,hwndEncDstFile,hwndDecSrcFile,hwndDecDstFile;
extern HWND msgWin,hwndProgressControl;

int refreshKey(){
	char keyBuf[130];
	SendMessage(hwndKeyEdit,WM_GETTEXT,130,(LPARAM)keyBuf);
	if(strlen(keyBuf)>0)
		SendMessage(hwndMainWindow,WM_COMMAND,IDC_KEYENTER,0);
	return NORMAL_FINISH;
}

int enterKey(){
	char keyBuf[130];
	if(keyData.rawKey){
		delete[] keyData.rawKey;
		keyData.rawKey = (byte*)0;
	}
	if(keyData.expandedKey){
		delete[] keyData.expandedKey;
		keyData.expandedKey = (byte*)0;
	}
	SendMessage(hwndKeyEdit,WM_GETTEXT,130,(LPARAM)keyBuf);
	int n = strlen(keyBuf)*4;
	if(0 == n){
		keyData.keyStatus = KEY_STATUS_EMPTY;
		return KEY_INVALID_SIZE;
	}
	if(128!=n && 256!=n && 512!=n){
		keyData.keyStatus = KEY_STATUS_REJECTED;
		return KEY_INVALID_SIZE;
	}
	keyData.keySize = n;
	if(keyData.keySize < workMode.keySize){
		keyData.keyStatus = KEY_STATUS_REJECTED;
		return KEY_TOO_SMALL;
	}
	keyData.rawKey = str2pbyte(keyBuf);
	if(keyData.rawKey == 0){
		keyData.keyStatus = KEY_STATUS_REJECTED;
		return KEY_PARSE_ERROR;
	}
	
	keyData.expandedKey = expandKey(workMode.blockSize,workMode.keySize,keyData.rawKey,0);
	if(keyData.expandedKey == 0){
		keyData.keyStatus = KEY_STATUS_REJECTED;
		return KEY_EXPAND_ERROR;
	}
	keyData.keyStatus = KEY_STATUS_ACCEPTED;
	return NORMAL_FINISH;
}

int loadKey(HWND hwnd){
	OPENFILENAME f;
	DWORD fsize;
	char fname[512];
	fname[0] = '\0';
	fsize = sizeof(f);
	ZeroMemory(&f, fsize);

	f.lStructSize = fsize;
	f.hwndOwner = hwnd;
	f.lpstrFile = fname;
	f.nMaxFile = sizeof(fname);
	f.lpstrFilter = "Key files\0*.key\0Text files\0*.TXT\0All files\0*.*\0\0";
	f.nFilterIndex = 1;
	f.lpstrTitle = "Select file with a key";
	f.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (!GetOpenFileName(&f)) {
		return USER_CANCEL;
	}
	
	HANDLE h;
	h = CreateFile(
		f.lpstrFile, 
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE == h) {
		return FILE_OPEN_ERROR;
	}
		
	char fbuf[160];
	DWORD nRead;
	ReadFile(h, fbuf, 159, &nRead, NULL);
	fbuf[nRead]='\0';
	CloseHandle(h);
	SendMessage(hwndKeyEdit,WM_SETTEXT,0,(LPARAM)fbuf);
	return NORMAL_FINISH;	
}

int loadDll(){
	HINSTANCE hDLL= LoadLibrary("kalina.dll");//("..\\..\\DLL\\Release\\DLL.dll");
	if(hDLL == NULL){
		return DLL_LOAD_ERROR;
	}
	
	expandKey = (lpfnexpandKey)GetProcAddress(hDLL,"expandKey");
	if(expandKey == NULL){
		return DLL_EXPAND_LOCATE_ERROR;
	}
	encrypt = (lpfncrypt)GetProcAddress(hDLL,"encrypt");
	if(encrypt == NULL){
		return DLL_ENCRYPT_LOCATE_ERROR;
	}
	decrypt = (lpfncrypt)GetProcAddress(hDLL,"decrypt");
	if(decrypt == NULL){
		return DLL_DECRYPT_LOCATE_ERROR;
	}
	return NORMAL_FINISH;
}


char *pbyte2str(int matrixSize,const byte *matrix){
	const byte C = matrixSize / 8;
	char *str = new char[2*C + 1];
	for(int i=0;i<C;i++){
		sprintf(str+2*i,"%02X",matrix[i]);
	}
	str[2*C]='\0';
	return str;
}


byte* str2pbyte(char *str){
	int i,b=0,k;
	const int n = strlen(str);
	byte *pb = new byte[n/2];
	if(pb == 0)
		return 0;
	for(i=0;i<n;i++){
		k = -1;
		if(str[i]>='0' && str[i]<='9')
			k = str[i]-'0';
		if(str[i]>='A' && str[i]<='F')
			k = str[i]-'A'+10;
		if(str[i]>='a' && str[i]<='f')
			k = str[i]-'a'+10;
		if(-1 == k){
			return 0;
		}
		else{
			if(i&1){
				b += k;
				pb[i/2] = (byte)(b & 0xFF);
			}
			else{
				b = k<<4;
			}
		}
	}
	return pb;
}

int fileSelect(HWND mainWin,int editID){
	
	OPENFILENAME f;
	DWORD fsize;
	char fname[512];
	fname[0] = '\0';
	fsize = sizeof(f);
	ZeroMemory(&f, fsize);

	f.lStructSize = fsize;
	f.hwndOwner = mainWin;
	f.lpstrFile = fname;
	f.nMaxFile = sizeof(fname);
	f.nFilterIndex = 1;
	f.lpstrTitle = "Select file";
	
	HWND hEdit;
	switch(editID){
	case IDC_ESFILESEL:
		hEdit = hwndEncSrcFile;
		f.lpstrFilter = "All files\0*.*\0Text files\0*.TXT\0Encrypted files\0*.enc\0Decrypted files\0*.dec\0\0";
		break;
	case IDC_EDFILESEL:
		hEdit = hwndEncDstFile;
		f.lpstrFilter = "Encrypted files\0*.enc\0Text files\0*.TXT\0Decrypted files\0*.dec\0All files\0*.*\0\0";
		break;
	case IDC_DSFILESEL:
		hEdit = hwndDecSrcFile;
		f.lpstrFilter = "All files\0*.*\0Text files\0*.TXT\0Encrypted files\0*.enc\0Decrypted files\0*.dec\0\0";
		break;
	case IDC_DDFILESEL:
		hEdit = hwndDecDstFile;
		f.lpstrFilter = "Decrypted files\0*.dec\0Encrypted files\0*.enc\0Text files\0*.TXT\0All files\0*.*\0\0";
		break;
	default:
		return -1;
	}
	

	if (GetOpenFileName(&f)) {
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)f.lpstrFile);
		SendMessage(hEdit, EM_SETSEL, 0, -1);
		SendMessage(hEdit, EM_SETSEL, (WPARAM)-1, -1);
		SendMessage(hEdit, EM_SCROLLCARET, 0, 0);
	}
	return NORMAL_FINISH;
}

DWORD WINAPI decryptStart(void*){
	DWORD exitStatus;
	
	if(0==keyData.rawKey || 0== keyData.expandedKey){
		PostMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,KEY_NO_ENTERED);
		return KEY_NO_ENTERED;
	}
	
	HANDLE fD=0,fS=0;
	char *strS=0,*strD=0,*buf=0;
	int i,j;
	strS = new char[512];
	if(0==strS){
		exitStatus = MEM_ALLOC_ERROR;
		goto finalize;
	}
	SendMessage(hwndDecSrcFile,WM_GETTEXT,511,(LPARAM)strS);
	int nS = strlen(strS);
	if(nS<1){
		exitStatus = FILE_NO_SELECT;
		goto finalize;
	}
	strD = new char[512];
	if(0==strD){
		exitStatus = MEM_ALLOC_ERROR;
		goto finalize;
	}
	SendMessage(hwndDecDstFile,WM_GETTEXT,511,(LPARAM)strD);
	if(strlen(strD)<1){
		//if ext=.enc remove it
		if( '.'==strS[nS-4] &&
			'e'==strS[nS-3] &&
			'n'==strS[nS-2] &&
			'c'==strS[nS-1]){
			
			for(j=0;j<nS-4;j++)
				strD[j] = strS[j];				
			strD[nS-4]= '\0';
		}
		else{
			//find ext
			for(i=nS-1;i>=0;i--)
				if(strS[i]=='.')
					break;
			if(i<0){ //no ext
				i = nS;
			}
			for(j=0;j<i;j++)
				strD[j] = strS[j];
			strD[j++] = '.';
			strD[j++] = 'd';
			strD[j++] = 'e';
			strD[j++] = 'c';
			strD[j++] = '\0';
		}
		buf = new char[512];
		if(0==buf){
			exitStatus = MEM_ALLOC_ERROR;
			goto finalize;
		}
		sprintf(buf,"No name for result file. Use default?\n%s",strD);
		if(IDNO==MessageBox(msgWin,buf,"Decryption process",MB_YESNO|MB_ICONQUESTION)){
			exitStatus = USER_CANCEL;
			goto finalize;
		}
		SendMessage(hwndDecDstFile,WM_SETTEXT,0,(LPARAM)strD);
	}
	
	fS = CreateFile(
		strS, 
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE == fS) {
		exitStatus = FILE_OPEN_ERROR;
		goto finalize;
	}	
	
	fD = CreateFile(
		strD, 
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE != fD) {
		CloseHandle(fD);
		if(0==buf)
			buf = new char[512];
		if(0==buf){
			exitStatus = MEM_ALLOC_ERROR;
			goto finalize;
		}
		sprintf(buf,"File exists. Overwrite?\n%s",strD);
		if(IDNO==MessageBox(msgWin,buf,"Decryption process",MB_YESNO|MB_ICONQUESTION)){
			exitStatus = USER_CANCEL;
			goto finalize;
		}
	}	
	fD = CreateFile(
		strD, 
		GENERIC_WRITE,
		0,/*NO SHARE*/
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE == fD) {
		exitStatus = FILE_OPEN_ERROR;
		goto finalize;
	}	
	
	byte blockBytes = workMode.blockSize/8;
	
	byte *fbuf = new byte[blockBytes];
	if(0==fbuf){
		exitStatus = MEM_ALLOC_ERROR;
		goto finalize;
	}
	DWORD nRead,nWritten;
	LARGE_INTEGER fSize,fDSize;
	GetFileSizeEx(fS,&fDSize);
	LONGLONG fDSave = fDSize.QuadPart;

	ReadFile(fS,fbuf,blockBytes,&nRead,NULL);
	if(nRead<blockBytes){
		exitStatus = FILE_READ_DATA_ERROR;
		goto finalize;
	}
	if(0==decrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
		exitStatus = ENCRYPT_INNER_ERROR;
		goto finalize;
	}
	memcpy(&(fSize.QuadPart),fbuf,sizeof(fSize.QuadPart));
	if(0==buf)
		buf = new char[512];
	if(0==buf){
		exitStatus = MEM_ALLOC_ERROR;
		goto finalize;
	}
	fDSize.QuadPart -= nRead;
	//doneNew += nRead;
	

				
	while(fDSize.QuadPart > blockBytes){
		ReadFile(fS,fbuf,blockBytes,&nRead,NULL); 
		if(nRead != blockBytes){
			exitStatus = FILE_READ_DATA_ERROR;
			goto finalize;
		}
		if(0==decrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
			exitStatus = ENCRYPT_INNER_ERROR;
			goto finalize;
		}
		if(FALSE==WriteFile(fD,fbuf,blockBytes,&nWritten,NULL) || nWritten!=blockBytes){
			exitStatus = FILE_WRITE_DATA_ERROR;
			goto finalize;
		}
		fDSize.QuadPart -= nRead;
		fSize.QuadPart  -= nRead;
		
		SendMessage(hwndProgressControl, PBM_SETPOS, (int)(100-100*fDSize.QuadPart/fDSave), 0); 
		
	}

	//last block
	if(fDSize.QuadPart != blockBytes){
		exitStatus = FILE_WRONG_SIZE;
		goto finalize;
	}
	ReadFile(fS,fbuf,blockBytes,&nRead,NULL); 
	if(nRead != blockBytes){
		exitStatus = FILE_READ_DATA_ERROR;
		goto finalize;
	}
	if(0==decrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
		exitStatus = ENCRYPT_INNER_ERROR;
		goto finalize;
	}
	if(fSize.QuadPart<=0 || fSize.QuadPart > blockBytes){
		exitStatus =  DECRYPT_SIZE_RESTORE_ERROR;
		goto finalize;;
	}
	if(FALSE==WriteFile(fD,fbuf,fSize.QuadPart,&nWritten,NULL) || nWritten!=fSize.QuadPart){
		exitStatus = FILE_WRITE_DATA_ERROR;
		goto finalize;
	}
	SendMessage(hwndProgressControl, PBM_SETPOS, 100, 0); 
	exitStatus = NORMAL_FINISH;
	
finalize:
	if(fS) CloseHandle(fS);
	if(fD) CloseHandle(fD);
	if(strS) delete[] strS;
	if(strD) delete[] strD;
	if(buf)  delete[] buf;	
	SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,exitStatus);
	return exitStatus;
}

int keyGen(){
	OPENFILENAME f;
	DWORD fsize;
	char fname[512];
	sprintf(fname,"rand%d.key",workMode.keySize);
	//fname[0] = '\0';
	fsize = sizeof(f);
	ZeroMemory(&f, fsize);

	f.lStructSize = fsize;
	f.hwndOwner = hwndMainWindow;
	f.lpstrFile = fname;
	f.nMaxFile = sizeof(fname);
	f.nFilterIndex = 1;
	f.lpstrTitle = "Select file";
	f.lpstrFilter = "All files\0*.*\0Text files\0*.TXT\0Key files\0*.key\0\0";

	if (!GetOpenFileName(&f)) {
		return USER_CANCEL;
	}
	HANDLE	fK = 
		CreateFile(
			f.lpstrFile, 
			GENERIC_WRITE,
			0,/*NO SHARE*/
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

	if (INVALID_HANDLE_VALUE == fK) {
		MessageBox(hwndMainWindow, "Key file create error","Key generation failed",MB_OK);
		return FILE_OPEN_ERROR;
	}	
	
	DWORD i, nWritten, keyStrLen = workMode.keySize / 4;
	char digit[] = "0123456789ABCDEF";
	char *keyStr = new char[keyStrLen+1];
	
	srand(time(NULL));
	for(i=0;i<keyStrLen;i++)
		keyStr[i] = digit[rand()%16];
	keyStr[i] = '\0';
	
	if(FALSE==WriteFile(fK,keyStr,keyStrLen,&nWritten,NULL) || nWritten!=keyStrLen){
		CloseHandle(fK);
		MessageBox(hwndMainWindow, "Key file write error","Key generation failed",MB_OK);
		delete[] keyStr;
		return FILE_WRITE_DATA_ERROR;
	}
	
	CloseHandle(fK);
	MessageBox(hwndMainWindow, "Key file written. \nTo change key size select other work mode.","Key generation",MB_OK);
	delete[] keyStr;
	return NORMAL_FINISH;
}


DWORD WINAPI encryptStart(void*){
	DWORD exitStatus;
	
	if(0==keyData.rawKey || 0== keyData.expandedKey){
		PostMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,KEY_NO_ENTERED);
		return KEY_NO_ENTERED;
	}
	HANDLE fD=0,fS=0;
	char *strS=0,*strD=0,*buf=0;
	int i,j;
	strS = new char[512];
	if(0==strS){
		exitStatus = MEM_ALLOC_ERROR;
		goto finalize;
	}
	
	SendMessage(hwndEncSrcFile,WM_GETTEXT,511,(LPARAM)strS);
	int nS = strlen(strS);
	if(nS<1){
		exitStatus = FILE_NO_SELECT;
		goto finalize;
	}
	strD = new char[512];
	if(0==strD){
		exitStatus = MEM_ALLOC_ERROR;
		goto finalize;
	}
	SendMessage(hwndEncDstFile,WM_GETTEXT,508,(LPARAM)strD);
	if(strlen(strD)<1){
		for(j=0;j<nS;j++)
			strD[j] = strS[j];
		strD[j++] = '.';
		strD[j++] = 'e';
		strD[j++] = 'n';
		strD[j++] = 'c';
		strD[j++] = '\0';
		buf = new char[512];
		if(0==buf){
			exitStatus = MEM_ALLOC_ERROR;
			goto finalize;
		}
		sprintf(buf,"No name for result file. Use default?\n%s",strD);
		if(IDNO==MessageBox(msgWin,buf,"Encryption process",MB_YESNO|MB_ICONQUESTION)){
			exitStatus = USER_CANCEL;
			goto finalize;
		}
		SendMessage(hwndEncDstFile,WM_SETTEXT,0,(LPARAM)strD);
	}

	fS = CreateFile(
		strS, 
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE == fS) {
		exitStatus = FILE_OPEN_ERROR;
		goto finalize; 
	}	
	
	LARGE_INTEGER fSize;
	LONGLONG fPos;
	GetFileSizeEx(fS,&fSize);
	
	fD = CreateFile(
		strD, 
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE != fD) {
		CloseHandle(fD);
		if(0==buf)
			buf = new char[512];
		if(0==buf){
			exitStatus = MEM_ALLOC_ERROR;
			goto finalize;
		}
		sprintf(buf,"File exists. Overwrite?\n%s",strD);
		if(IDNO==MessageBox(msgWin,buf,"Encryption process",MB_YESNO|MB_ICONQUESTION)){
			exitStatus = USER_CANCEL;
			goto finalize; 
		}
	}	
	fD = CreateFile(
		strD, 
		GENERIC_WRITE,
		0,/*NO SHARE*/
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE == fD) {
		exitStatus = FILE_OPEN_ERROR;
		goto finalize;
	}	
	
	byte blockBytes = workMode.blockSize/8;
	
	byte *fbuf = new byte[blockBytes];
	if(0==fbuf){
		exitStatus = MEM_ALLOC_ERROR;
		goto finalize;
	}
	
	DWORD nRead,nWritten;
	
	memcpy(fbuf,&(fSize.QuadPart),sizeof(fSize.QuadPart));
	if(0==encrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
		exitStatus = ENCRYPT_INNER_ERROR;
		goto finalize; 
	}
	if(FALSE==WriteFile(fD,fbuf,blockBytes,&nWritten,NULL) || nWritten!=blockBytes){
		exitStatus = FILE_WRITE_DATA_ERROR;
		goto finalize;;
	}
	fPos = 0;
	while(ReadFile(fS,fbuf,blockBytes,&nRead,NULL) && nRead>0){
		for(i=nRead;i<blockBytes;i++)
			fbuf[i]=0;
		if(0==encrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
			exitStatus = ENCRYPT_INNER_ERROR;
			goto finalize;
		}
		if(FALSE==WriteFile(fD,fbuf,blockBytes,&nWritten,NULL) || nWritten!=blockBytes){
			exitStatus = FILE_WRITE_DATA_ERROR;
			goto finalize;;
		}
		fPos += nRead;
		SendMessage(hwndProgressControl, PBM_SETPOS, (int)(100*fPos/fSize.QuadPart), 0); 
	}
	SendMessage(hwndProgressControl, PBM_SETPOS, 100, 0); 
	exitStatus = NORMAL_FINISH;
	
finalize:
	if(fS) CloseHandle(fS);
	if(fD) CloseHandle(fD);
	if(strS) delete[] strS;
	if(strD) delete[] strD;
	if(buf)  delete[] buf;	
	SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,exitStatus);
	return exitStatus;
}
