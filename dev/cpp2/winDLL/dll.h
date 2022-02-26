#ifndef _DLL_H_
#define _DLL_H_

#define ROWLENGTH 8
typedef unsigned char byte;
#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

extern "C"{
	DLLIMPORT byte GFmul(byte a,byte b);
	DLLIMPORT byte* expandKey(int blockSize, int keySize, const byte *rawKey, byte *destination = 0);
	DLLIMPORT byte* encrypt(int blockSize, int keySize, byte *initState, const byte *expandedKey, bool rewriteState = false);
	DLLIMPORT byte* decrypt(int blockSize, int keySize, byte *initState, const byte *expandedKey, bool rewriteState = false);
}
#endif
