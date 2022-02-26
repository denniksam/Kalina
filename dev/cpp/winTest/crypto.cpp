#include "wintest.h"

lpfnexpandKey expandKey;
lpfncrypt encrypt,decrypt;

TKeyData keyData;
TWorkMode workMode;

extern HWND hwndMainWindow;
extern HWND hwndHideKey, hwndKeyEdit;
extern HWND hwndEncSrcFile,hwndEncDstFile,hwndDecSrcFile,hwndDecDstFile;
extern HWND msgWin,hwndProgressControl;

int enterKey(){
	char *keyBuf;
	keyBuf = new char[130];
	if(0==keyBuf)
		return MEM_ALLOC_ERROR;
	SendMessage(hwndKeyEdit,WM_GETTEXT,130,(LPARAM)keyBuf);
	int n = strlen(keyBuf)*4;
	if(128!=n && 256!=n && 512!=n){
		//MessageBox(NULL,keyBuf,"",MB_OK);
		return KEY_INVALID_SIZE;
	}
	keyData.keySize = n;
	keyData.rawKey = str2pbyte(keyBuf);
	if(keyData.rawKey == 0)
		return KEY_PARSE_ERROR;
	
	keyData.expandedKey = expandKey(workMode.blockSize,workMode.keySize,keyData.rawKey,0);
	if(keyData.expandedKey == 0)
		return KEY_EXPAND_ERROR;
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
	f.lpstrFilter = "All files\0*.*\0Text files\0*.TXT\0Key files\0*.key\0\0";
	f.nFilterIndex = 1;
	f.lpstrTitle = "Select file with a key";
	f.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (!GetOpenFileName(&f)) {
		//MessageBox(hwnd, "Key not load","",IDOK);
		return USER_CANCEL;
	}
	//MessageBox(hwnd, f.lpstrFile,"",IDOK);
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
		//MessageBox(hwnd, "File open error","",IDOK);
		return FILE_OPEN_ERROR;
	}
		
	char fbuf[160];
	DWORD nRead;
	ReadFile(h, fbuf, 159, &nRead, NULL);
	fbuf[nRead]='\0';
	CloseHandle(h);
	SendMessage(hwndKeyEdit,WM_SETTEXT,0,(LPARAM)fbuf);
	//return enterKey();  
	return NORMAL_FINISH;	
}

int loadDll(){
	HINSTANCE hDLL= LoadLibrary("..\\..\\DLL\\Release\\DLL.dll");
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
	/* //Space separated version - need revision
	const byte C = matrixSize / 4;
	char *str = new char[(8+1)*2*C+1];
		for(byte i=0;i<8;i++)
			sprintf(str+2*i,"%02X",matrix[i]);
		sprintf(str+16," ");
		for(byte i=0;i<8;i++)
			sprintf(str+2*i+17,"%02X",matrix[8+i]);
		str[33]='\0';
		if(C>2){
			sprintf(str+33," ");
			for(byte i=0;i<8;i++)
				sprintf(str+2*i+34,"%02X",matrix[16+i]);
			sprintf(str+50," ");
			for(byte i=0;i<8;i++)
				sprintf(str+2*i+51,"%02X",matrix[24+i]);
			str[67]='\0';
		}
		if(C>4){
			sprintf(str+67," ");
			for(byte i=0;i<8;i++)
				sprintf(str+2*i+68,"%02X",matrix[32+i]);
			sprintf(str+85," ");
			for(byte i=0;i<8;i++)
				sprintf(str+2*i+85,"%02X",matrix[40+i]);
			
			sprintf(str+102," ");
			for(byte i=0;i<8;i++)
				sprintf(str+2*i+102,"%02X",matrix[48+i]);
			sprintf(str+119," ");
			for(byte i=0;i<8;i++)
				sprintf(str+2*i+119,"%02X",matrix[56+i]);
			str[135]='\0';
		}
	*/
	return str;
}


byte* str2pbyte(char *str){
	int i,b,k;
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
			//MessageBox(0,"sym error","",IDOK);
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
	//f.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
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
		SendMessage(hEdit,WM_SETTEXT,0,(LPARAM)f.lpstrFile);
	}
	return 0;
}

DWORD WINAPI encryptGo(){
	if(0==keyData.rawKey || 0== keyData.expandedKey){
		return KEY_NO_ENTERED;
	}
	
	char *strS,*strD,*buf=0;
	int i,j;
	strS = new char[512];
	if(0==strS)
		return MEM_ALLOC_ERROR;
	SendMessage(hwndEncSrcFile,WM_GETTEXT,511,(LPARAM)strS);
	int nS = strlen(strS);
	if(nS<1){
		return FILE_NO_SELECT;
	}
	strD = new char[512];
	if(0==strD){
		return MEM_ALLOC_ERROR;
	}
	SendMessage(hwndEncDstFile,WM_GETTEXT,508,(LPARAM)strD);
	if(strlen(strD)<1){
		/*
		//find ext
		for(i=nS-1;i>=0;i--)
			if(strS[i]=='.')
				break;
		if(i<0){ //no ext
			i = nS;
		}*/
		for(j=0;j<nS;j++)
			strD[j] = strS[j];
		strD[j++] = '.';
		strD[j++] = 'e';
		strD[j++] = 'n';
		strD[j++] = 'c';
		strD[j++] = '\0';
		buf = new char[512];
		if(0==buf)
			return MEM_ALLOC_ERROR;
		sprintf(buf,"No name for result file. Use default?\n%s",strD);
		if(IDNO==MessageBox(hwndEncSrcFile,buf,"Encryption process",MB_YESNO|MB_ICONQUESTION))
			return 0;
		SendMessage(hwndEncDstFile,WM_SETTEXT,0,(LPARAM)strD);
	}
	HANDLE fS;
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
		//MessageBox(hwndEncSrcFile, "Source file open error","Encryption failed",IDOK);
		return FILE_OPEN_ERROR;
	}	
	
	LARGE_INTEGER fSize;
	GetFileSizeEx(fS,&fSize);
	/*
	if(0==buf)
		buf = new char[512];
	if(0==buf)
		return MEM_ALLOC_ERROR;
	sprintf(buf,"%d\n%I64d",sizeof(fSize.QuadPart),fSize.QuadPart);
	MessageBox(hwndEncSrcFile, buf,"",MB_OK);
	return 1;
	*/
	
	HANDLE fD;
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
		if(0==buf)
			return MEM_ALLOC_ERROR;
		sprintf(buf,"File exists. Overwrite?\n%s",strD);
		if(IDNO==MessageBox(hwndEncSrcFile,buf,"Encryption process",MB_YESNO|MB_ICONQUESTION))
			return 0;
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
		MessageBox(hwndEncSrcFile, "Destination file create error","Encryption failed",IDOK);
		return FILE_OPEN_ERROR;
	}	
	
	byte blockBytes = workMode.blockSize/8;
	
	byte *fbuf = new byte[blockBytes];
	if(0==fbuf){
			return MEM_ALLOC_ERROR;
	}
	
	DWORD nRead,nWritten;
	
	memcpy(fbuf,&(fSize.QuadPart),sizeof(fSize.QuadPart));
	if(0==encrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
		return ENCRYPT_INNER_ERROR;
	}
	if(FALSE==WriteFile(fD,fbuf,blockBytes,&nWritten,NULL) || nWritten!=blockBytes){
		return FILE_WRITE_DATA_ERROR;
	}
	
	while(ReadFile(fS,fbuf,blockBytes,&nRead,NULL) && nRead>0){
		for(i=nRead;i<blockBytes;i++)
			fbuf[i]=0;
		if(0==encrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
			return ENCRYPT_INNER_ERROR;
		}
		if(FALSE==WriteFile(fD,fbuf,blockBytes,&nWritten,NULL) || nWritten!=blockBytes){
			return FILE_WRITE_DATA_ERROR;
		}
	}
	
	CloseHandle(fS);
	CloseHandle(fD);
	return NORMAL_FINISH;
}

DWORD WINAPI decryptStart(void*){
	if(0==keyData.rawKey || 0== keyData.expandedKey){
		PostMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,KEY_NO_ENTERED);
		return KEY_NO_ENTERED;
	}
	
	char *strS,*strD,*buf=0;
	int i,j;
	strS = new char[512];
	if(0==strS){
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,MEM_ALLOC_ERROR);
		return MEM_ALLOC_ERROR;
	}
	SendMessage(hwndDecSrcFile,WM_GETTEXT,511,(LPARAM)strS);
	int nS = strlen(strS);
	if(nS<1){
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,FILE_NO_SELECT);
		return FILE_NO_SELECT;
	}
	strD = new char[512];
	if(0==strD){
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,MEM_ALLOC_ERROR);
		return MEM_ALLOC_ERROR;
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
			SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,MEM_ALLOC_ERROR);
			return MEM_ALLOC_ERROR;
		}
		sprintf(buf,"No name for result file. Use default?\n%s",strD);
		if(IDNO==MessageBox(hwndDecSrcFile,buf,"Decryption process",MB_YESNO|MB_ICONQUESTION)){
			SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,USER_CANCEL);
			return USER_CANCEL;
		}
		SendMessage(hwndDecDstFile,WM_SETTEXT,0,(LPARAM)strD);
	}
	HANDLE fS;
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
		//MessageBox(hwndDecSrcFile, "Source file open error","Decryption failed",IDOK);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,FILE_OPEN_ERROR);
		return FILE_OPEN_ERROR;
	}	
	
	HANDLE fD;
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
			SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,MEM_ALLOC_ERROR);
			return MEM_ALLOC_ERROR;
		}
		sprintf(buf,"File exists. Overwrite?\n%s",strD);
		if(IDNO==MessageBox(hwndDecSrcFile,buf,"Decryption process",MB_YESNO|MB_ICONQUESTION)){
			SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,USER_CANCEL);
			return USER_CANCEL;
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
		MessageBox(hwndDecSrcFile, "Destination file create error","Decryption failed",MB_OK);
		CloseHandle(fS);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,FILE_OPEN_ERROR);
		return FILE_OPEN_ERROR;
	}	
	
	byte blockBytes = workMode.blockSize/8;
	
	byte *fbuf = new byte[blockBytes];
	if(0==fbuf){
		CloseHandle(fS);
		CloseHandle(fD);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,MEM_ALLOC_ERROR);
		return MEM_ALLOC_ERROR;
	}
	DWORD nRead,nWritten;
	LARGE_INTEGER fSize,fDSize;
	GetFileSizeEx(fS,&fDSize);
	LONGLONG fDSave = fDSize.QuadPart;

	ReadFile(fS,fbuf,blockBytes,&nRead,NULL);
	if(nRead<blockBytes){
		CloseHandle(fS);
		CloseHandle(fD);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,FILE_READ_DATA_ERROR);
		return FILE_READ_DATA_ERROR;
	}
	if(0==decrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
		CloseHandle(fS);
		CloseHandle(fD);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,ENCRYPT_INNER_ERROR);
		return ENCRYPT_INNER_ERROR;
	}
	memcpy(&(fSize.QuadPart),fbuf,sizeof(fSize.QuadPart));
	if(0==buf)
		buf = new char[512];
	if(0==buf){
		CloseHandle(fS);
		CloseHandle(fD);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,MEM_ALLOC_ERROR);
		return MEM_ALLOC_ERROR;
	}
	fDSize.QuadPart -= nRead;
	//doneNew += nRead;
	

				
	while(fDSize.QuadPart > blockBytes){
		ReadFile(fS,fbuf,blockBytes,&nRead,NULL); 
		if(nRead != blockBytes){
			CloseHandle(fS);
			CloseHandle(fD);
			SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,FILE_READ_DATA_ERROR);
			return FILE_READ_DATA_ERROR;
		}
		if(0==decrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
			CloseHandle(fS);
			CloseHandle(fD);
			SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,ENCRYPT_INNER_ERROR);
			return ENCRYPT_INNER_ERROR;
		}
		if(FALSE==WriteFile(fD,fbuf,blockBytes,&nWritten,NULL) || nWritten!=blockBytes){
			CloseHandle(fS);
			CloseHandle(fD);
			SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,FILE_WRITE_DATA_ERROR);
			return FILE_WRITE_DATA_ERROR;
		}
		fDSize.QuadPart -= nRead;
		fSize.QuadPart  -= nRead;
		
		SendMessage(hwndProgressControl, PBM_SETPOS, (int)(100-100*fDSize.QuadPart/fDSave), 0); 
		
	}

	//last block
	if(fDSize.QuadPart != blockBytes){
		CloseHandle(fS);
		CloseHandle(fD);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,FILE_WRONG_SIZE);
		return FILE_WRONG_SIZE;
	}
	ReadFile(fS,fbuf,blockBytes,&nRead,NULL); 
	if(nRead != blockBytes){
		CloseHandle(fS);
		CloseHandle(fD);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,FILE_READ_DATA_ERROR);
		return FILE_READ_DATA_ERROR;
	}
	if(0==decrypt(workMode.blockSize,workMode.keySize,fbuf,keyData.expandedKey,1)){
		CloseHandle(fS);
		CloseHandle(fD);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,ENCRYPT_INNER_ERROR);
		return ENCRYPT_INNER_ERROR;
	}
	if(fSize.QuadPart<=0 || fSize.QuadPart > blockBytes){
		CloseHandle(fS);
		CloseHandle(fD);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,DECRYPT_SIZE_RESTORE_ERROR);
		return DECRYPT_SIZE_RESTORE_ERROR;
	}
	if(FALSE==WriteFile(fD,fbuf,fSize.QuadPart,&nWritten,NULL) || nWritten!=fSize.QuadPart){
		CloseHandle(fS);
		CloseHandle(fD);
		SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,FILE_WRITE_DATA_ERROR);
		return FILE_WRITE_DATA_ERROR;
	}
	SendMessage(hwndProgressControl, PBM_SETPOS, 100, 0); 
		
	CloseHandle(fS);
	CloseHandle(fD);
	SendMessage(msgWin,WM_COMMAND,IDC_THREADSTOP,NORMAL_FINISH);
	return NORMAL_FINISH;
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
	
	DWORD nWritten, keyStrLen = workMode.keySize / 4;;
	char digit[] = "0123456789ABCDEF";
	char *keyStr = new char[keyStrLen+1];
	int i;
	
	srand(time(NULL));
	for(i=0;i<keyStrLen;i++)
		keyStr[i] = digit[rand()%16];
	keyStr[i] = '\0';
	
	if(FALSE==WriteFile(fK,keyStr,keyStrLen,&nWritten,NULL) || nWritten!=keyStrLen){
		CloseHandle(fK);
		MessageBox(hwndMainWindow, "Key file write error","Key generation failed",MB_OK);
		return FILE_WRITE_DATA_ERROR;
	}
	
	CloseHandle(fK);
	MessageBox(hwndMainWindow, "OK","Key generation",MB_OK);
		
	return NORMAL_FINISH;
}
