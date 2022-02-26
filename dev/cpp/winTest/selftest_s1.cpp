#include "wintest.h"

TSample sample[5];


int selfTest(HWND hwnd){
	HINSTANCE hDLL;
	pmul GFmul;
	lpfnexpandKey expandKey;
	lpfncrypt encrypt,decrypt;
	HDC hdc;
	byte f,i,k;
	
	hDLL = LoadLibrary("..\\..\\DLL\\Release\\DLL.dll");
	if(hDLL == NULL){
		MessageBox(NULL, "winDLL Load Failure","Error",MB_ICONEXCLAMATION|MB_OK);
		return EXIT_FAILURE;
	}
	GFmul = (pmul)GetProcAddress(hDLL,"GFmul");
	if(GFmul == NULL){
		MessageBox(NULL, "GFmul locate Failure","Error",MB_ICONEXCLAMATION|MB_OK);
		return EXIT_FAILURE;
	}
	expandKey = (lpfnexpandKey)GetProcAddress(hDLL,"expandKey");
	if(expandKey == NULL){
		MessageBox(NULL, "expandKey locate Failure","Error",MB_ICONEXCLAMATION|MB_OK);
		return EXIT_FAILURE;
	}
	encrypt = (lpfncrypt)GetProcAddress(hDLL,"encrypt");
	if(encrypt == NULL){
		MessageBox(NULL, "encrypt locate Failure","Error",MB_ICONEXCLAMATION|MB_OK);
		return EXIT_FAILURE;
	}
	decrypt = (lpfncrypt)GetProcAddress(hDLL,"decrypt");
	if(decrypt == NULL){
		MessageBox(NULL, "decrypt locate Failure","Error",MB_ICONEXCLAMATION|MB_OK);
		return EXIT_FAILURE;
	}
	
	hdc = GetDC(hwnd);
	
	for(k=0;k<5;k++){
		sample[k].eAns = encrypt(sample[k].blockSize,sample[k].keySize,sample[k].eBlock,expandKey(sample[k].blockSize,sample[k].keySize,sample[k].eKey,0),0);
		f=1;
		for(i=0;i<sample[k].blockSize/8;i++)
			if(sample[k].eAns[i]!=sample[k].eRes[i])
				f=0;
		sample[k].eStatus = f;
			
		/*
		TextOut(hdc,0,30+k*80,pbyte2str(sample[k].blockSize,res),sample[k].blockSize/4 + sample[k].blockSize/64 - 1);
		TextOut(hdc,0,30+k*80+15,pbyte2str(sample[k].blockSize,sample[k].eRes),sample[k].blockSize/4 + sample[k].blockSize/64 - 1);
		*/
		
		sample[k].dAns = decrypt(sample[k].blockSize,sample[k].keySize,sample[k].dBlock,expandKey(sample[k].blockSize,sample[k].keySize,sample[k].dKey,0),0);
		f=1;
		for(i=0;i<sample[k].blockSize/8;i++)
			if(sample[k].dAns[i]!=sample[k].dRes[i])
				f=0;
		sample[k].eStatus = f;
		/*
		TextOut(hdc,0,30+k*80+40,pbyte2str(sample[k].blockSize,res),sample[k].blockSize/4 + sample[k].blockSize/64 - 1);
		TextOut(hdc,0,30+k*80+55,pbyte2str(sample[k].blockSize,sample[k].dRes),sample[k].blockSize/4 + sample[k].blockSize/64 - 1);
		*/
	}
	return 0;
}


bool fillSample(){
	sample[0].blockSize = 128;
	sample[0].keySize = 128;
	if(!(sample[0].eBlock = str2pbyte("101112131415161718191A1B1C1D1E1F"))) return false;
	if(!(sample[0].eKey = str2pbyte("000102030405060708090A0B0C0D0E0F"))) return false;
	if(!(sample[0].eRes = str2pbyte("81BF1C7D779BAC20E1C9EA39B4D2AD06"))) return false;
	if(!(sample[0].dBlock = str2pbyte("1F1E1D1C1B1A19181716151413121110"))) return false;
	if(!(sample[0].dKey = str2pbyte("0F0E0D0C0B0A09080706050403020100"))) return false;
	if(!(sample[0].dRes = str2pbyte("7291EF2B470CC7846F09C2303973DAD7"))) return false;
	sample[0].eStatus = -1;
	sample[0].eAns = (byte*)0;
	sample[0].dAns = (byte*)0;
	
	
	sample[1].blockSize = 128;
	sample[1].keySize = 256;
	if(!(sample[1].eBlock = str2pbyte("202122232425262728292A2B2C2D2E2F"))) return false;
	if(!(sample[1].eKey = str2pbyte("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"))) return false;
	if(!(sample[1].eRes = str2pbyte("58EC3E091000158A1148F7166F334F14"))) return false;
	if(!(sample[1].dBlock = str2pbyte("2F2E2D2C2B2A29282726252423222120"))) return false;
	if(!(sample[1].dKey = str2pbyte("1F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100"))) return false;
	if(!(sample[1].dRes = str2pbyte("F36DB456CEFDDFE1B45B5F7030CAD996"))) return false;
	sample[1].eStatus = -1;
	sample[1].dStatus = -1;
	sample[1].eAns = (byte*)0;
	sample[1].dAns = (byte*)0;
	
	
	sample[2].blockSize = 256;
	sample[2].keySize = 256;
	if(!(sample[2].eBlock = str2pbyte("202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"))) return false;
	if(!(sample[2].eKey = str2pbyte("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"))) return false;
	if(!(sample[2].eRes = str2pbyte("F66E3D570EC92135AEDAE323DCBD2A8CA03963EC206A0D5A88385C24617FD92C"))) return false;
	if(!(sample[2].dBlock = str2pbyte("3F3E3D3C3B3A393837363534333231302F2E2D2C2B2A29282726252423222120"))) return false;
	if(!(sample[2].dKey = str2pbyte("1F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100"))) return false;
	if(!(sample[2].dRes = str2pbyte("7FC5237896674E8603C1E9B03F8B4BA3AB5B7C592C3FC3D361EDD12586B20FE3"))) return false;
	sample[2].eStatus = -1;
	sample[2].dStatus = -1;
	sample[2].eAns = (byte*)0;
	sample[2].dAns = (byte*)0;
	
	
	sample[3].blockSize = 256;
	sample[3].keySize = 512;
	if(!(sample[3].eBlock = str2pbyte("404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"))) return false;
	if(!(sample[3].eKey = str2pbyte("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"))) return false;
	if(!(sample[3].eRes = str2pbyte("606990E9E6B7B67A4BD6D893D72268B78E02C83C3CD7E102FD2E74A8FDFE5DD9"))) return false;
	if(!(sample[3].dBlock = str2pbyte("5F5E5D5C5B5A595857565554535251504F4E4D4C4B4A49484746454443424140"))) return false;
	if(!(sample[3].dKey = str2pbyte("3F3E3D3C3B3A393837363534333231302F2E2D2C2B2A292827262524232221201F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100"))) return false;
	if(!(sample[3].dRes = str2pbyte("18317A2767DAD482BCCD07B9A1788D075E7098189E5F84972D0B916D79BA6AE0"))) return false;
	sample[3].eStatus = -1;
	sample[3].dStatus = -1;
	sample[3].eAns = (byte*)0;
	sample[3].dAns = (byte*)0;
	
	
	sample[4].blockSize = 512;
	sample[4].keySize = 512;
	if(!(sample[4].eBlock = str2pbyte("404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"))) return false;
	if(!(sample[4].eKey = str2pbyte("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"))) return false;
	if(!(sample[4].eRes = str2pbyte("4A26E31B811C356AA61DD6CA0596231A67BA8354AA47F3A13E1DEEC320EB56B895D0F417175BAB662FD6F134BB15C86CCB906A26856EFEB7C5BC6472940DD9D9"))) return false;
	if(!(sample[4].dBlock = str2pbyte("7F7E7D7C7B7A797877767574737271706F6E6D6C6B6A696867666564636261605F5E5D5C5B5A595857565554535251504F4E4D4C4B4A49484746454443424140"))) return false;
	if(!(sample[4].dKey = str2pbyte("3F3E3D3C3B3A393837363534333231302F2E2D2C2B2A292827262524232221201F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100"))) return false;
	if(!(sample[4].dRes = str2pbyte("CE80843325A052521BEAD714E6A9D829FD381E0EE9A845BD92044554D9FA46A3757FEFDB853BB1F297FF9D833B75E66AAF4157ABB5291BDCF094BB13AA5AFF22"))) return false;
	sample[4].eStatus = -1;
	sample[4].dStatus = -1;
	sample[4].eAns = (byte*)0;
	sample[4].dAns = (byte*)0;
	
	
	return true;
}
