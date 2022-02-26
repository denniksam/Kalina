#include <stdio.h>
#include <conio.h>

#define ROWLENGTH 8
typedef unsigned char byte;

const byte pw2val[] = {1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,44,88,176,125,250,233,207,131,27,54,108,216,173,71,142,1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,44,88,176,125,250,233,207,131,27,54,108,216,173,71,142,1};
const byte pw2ind[] = {0,0,1,25,2,50,26,198,3,223,51,238,27,104,199,75,4,100,224,14,52,141,239,129,28,193,105,248,200,8,76,113,5,138,101,47,225,36,15,33,53,147,142,218,240,18,130,69,29,181,194,125,106,39,249,185,201,154,9,120,77,228,114,166,6,191,139,98,102,221,48,253,226,152,37,179,16,145,34,136,54,208,148,206,143,150,219,189,241,210,19,92,131,56,70,64,30,66,182,163,195,72,126,110,107,58,40,84,250,133,186,61,202,94,155,159,10,21,121,43,78,212,229,172,115,243,167,87,7,112,192,247,140,128,99,13,103,74,222,237,49,197,254,24,227,165,153,119,38,184,180,124,17,68,146,217,35,32,137,46,55,63,209,91,149,188,207,205,144,135,151,178,220,252,190,97,242,86,211,171,20,42,93,158,132,60,57,83,71,109,65,162,31,45,67,216,183,123,164,118,196,23,73,236,127,12,111,246,108,161,59,82,41,157,85,170,251,96,134,177,187,204,62,90,203,89,95,176,156,169,160,81,11,245,22,235,122,117,44,215,79,174,213,233,230,231,173,232,116,214,244,234,168,80,88,175};

const byte Sbox[][256]  = {
	{0xA8,0x43,0x5F,0x06,0x6B,0x75,0x6C,0x59,0x71,0xDF,0x87,0x95,0x17,0xF0,0xD8,0x09,0x6D,0xF3,0x1D,0xCB,0xC9,0x4D,0x2C,0xAF,0x79,0xE0,0x97,0xFD,0x6F,0x4B,0x45,0x39,0x3E,0xDD,0xA3,0x4F,0xB4,0xB6,0x9A,0x0E,0x1F,0xBF,0x15,0xE1,0x49,0xD2,0x93,0xC6,0x92,0x72,0x9E,0x61,0xD1,0x63,0xFA,0xEE,0xF4,0x19,0xD5,0xAD,0x58,0xA4,0xBB,0xA1,0xDC,0xF2,0x83,0x37,0x42,0xE4,0x7A,0x32,0x9C,0xCC,0xAB,0x4A,0x8F,0x6E,0x04,0x27,0x2E,0xE7,0xE2,0x5A,0x96,0x16,0x23,0x2B,0xC2,0x65,0x66,0x0F,0xBC,0xA9,0x47,0x41,0x34,0x48,0xFC,0xB7,0x6A,0x88,0xA5,0x53,0x86,0xF9,0x5B,0xDB,0x38,0x7B,0xC3,0x1E,0x22,0x33,0x24,0x28,0x36,0xC7,0xB2,0x3B,0x8E,0x77,0xBA,0xF5,0x14,0x9F,0x08,0x55,0x9B,0x4C,0xFE,0x60,0x5C,0xDA,0x18,0x46,0xCD,0x7D,0x21,0xB0,0x3F,0x1B,0x89,0xFF,0xEB,0x84,0x69,0x3A,0x9D,0xD7,0xD3,0x70,0x67,0x40,0xB5,0xDE,0x5D,0x30,0x91,0xB1,0x78,0x11,0x01,0xE5,0x00,0x68,0x98,0xA0,0xC5,0x02,0xA6,0x74,0x2D,0x0B,0xA2,0x76,0xB3,0xBE,0xCE,0xBD,0xAE,0xE9,0x8A,0x31,0x1C,0xEC,0xF1,0x99,0x94,0xAA,0xF6,0x26,0x2F,0xEF,0xE8,0x8C,0x35,0x03,0xD4,0x7F,0xFB,0x05,0xC1,0x5E,0x90,0x20,0x3D,0x82,0xF7,0xEA,0x0A,0x0D,0x7E,0xF8,0x50,0x1A,0xC4,0x07,0x57,0xB8,0x3C,0x62,0xE3,0xC8,0xAC,0x52,0x64,0x10,0xD0,0xD9,0x13,0x0C,0x12,0x29,0x51,0xB9,0xCF,0xD6,0x73,0x8D,0x81,0x54,0xC0,0xED,0x4E,0x44,0xA7,0x2A,0x85,0x25,0xE6,0xCA,0x7C,0x8B,0x56,0x80},
	{0xCE,0xBB,0xEB,0x92,0xEA,0xCB,0x13,0xC1,0xE9,0x3A,0xD6,0xB2,0xD2,0x90,0x17,0xF8,0x42,0x15,0x56,0xB4,0x65,0x1C,0x88,0x43,0xC5,0x5C,0x36,0xBA,0xF5,0x57,0x67,0x8D,0x31,0xF6,0x64,0x58,0x9E,0xF4,0x22,0xAA,0x75,0x0F,0x02,0xB1,0xDF,0x6D,0x73,0x4D,0x7C,0x26,0x2E,0xF7,0x08,0x5D,0x44,0x3E,0x9F,0x14,0xC8,0xAE,0x54,0x10,0xD8,0xBC,0x1A,0x6B,0x69,0xF3,0xBD,0x33,0xAB,0xFA,0xD1,0x9B,0x68,0x4E,0x16,0x95,0x91,0xEE,0x4C,0x63,0x8E,0x5B,0xCC,0x3C,0x19,0xA1,0x81,0x49,0x7B,0xD9,0x6F,0x37,0x60,0xCA,0xE7,0x2B,0x48,0xFD,0x96,0x45,0xFC,0x41,0x12,0x0D,0x79,0xE5,0x89,0x8C,0xE3,0x20,0x30,0xDC,0xB7,0x6C,0x4A,0xB5,0x3F,0x97,0xD4,0x62,0x2D,0x06,0xA4,0xA5,0x83,0x5F,0x2A,0xDA,0xC9,0x00,0x7E,0xA2,0x55,0xBF,0x11,0xD5,0x9C,0xCF,0x0E,0x0A,0x3D,0x51,0x7D,0x93,0x1B,0xFE,0xC4,0x47,0x09,0x86,0x0B,0x8F,0x9D,0x6A,0x07,0xB9,0xB0,0x98,0x18,0x32,0x71,0x4B,0xEF,0x3B,0x70,0xA0,0xE4,0x40,0xFF,0xC3,0xA9,0xE6,0x78,0xF9,0x8B,0x46,0x80,0x1E,0x38,0xE1,0xB8,0xA8,0xE0,0x0C,0x23,0x76,0x1D,0x25,0x24,0x05,0xF1,0x6E,0x94,0x28,0x9A,0x84,0xE8,0xA3,0x4F,0x77,0xD3,0x85,0xE2,0x52,0xF2,0x82,0x50,0x7A,0x2F,0x74,0x53,0xB3,0x61,0xAF,0x39,0x35,0xDE,0xCD,0x1F,0x99,0xAC,0xAD,0x72,0x2C,0xDD,0xD0,0x87,0xBE,0x5E,0xA6,0xEC,0x04,0xC6,0x03,0x34,0xFB,0xDB,0x59,0xB6,0xC2,0x01,0xF0,0x5A,0xED,0xA7,0x66,0x21,0x7F,0x8A,0x27,0xC7,0xC0,0x29,0xD7},
	{0x93,0xD9,0x9A,0xB5,0x98,0x22,0x45,0xFC,0xBA,0x6A,0xDF,0x02,0x9F,0xDC,0x51,0x59,0x4A,0x17,0x2B,0xC2,0x94,0xF4,0xBB,0xA3,0x62,0xE4,0x71,0xD4,0xCD,0x70,0x16,0xE1,0x49,0x3C,0xC0,0xD8,0x5C,0x9B,0xAD,0x85,0x53,0xA1,0x7A,0xC8,0x2D,0xE0,0xD1,0x72,0xA6,0x2C,0xC4,0xE3,0x76,0x78,0xB7,0xB4,0x09,0x3B,0x0E,0x41,0x4C,0xDE,0xB2,0x90,0x25,0xA5,0xD7,0x03,0x11,0x00,0xC3,0x2E,0x92,0xEF,0x4E,0x12,0x9D,0x7D,0xCB,0x35,0x10,0xD5,0x4F,0x9E,0x4D,0xA9,0x55,0xC6,0xD0,0x7B,0x18,0x97,0xD3,0x36,0xE6,0x48,0x56,0x81,0x8F,0x77,0xCC,0x9C,0xB9,0xE2,0xAC,0xB8,0x2F,0x15,0xA4,0x7C,0xDA,0x38,0x1E,0x0B,0x05,0xD6,0x14,0x6E,0x6C,0x7E,0x66,0xFD,0xB1,0xE5,0x60,0xAF,0x5E,0x33,0x87,0xC9,0xF0,0x5D,0x6D,0x3F,0x88,0x8D,0xC7,0xF7,0x1D,0xE9,0xEC,0xED,0x80,0x29,0x27,0xCF,0x99,0xA8,0x50,0x0F,0x37,0x24,0x28,0x30,0x95,0xD2,0x3E,0x5B,0x40,0x83,0xB3,0x69,0x57,0x1F,0x07,0x1C,0x8A,0xBC,0x20,0xEB,0xCE,0x8E,0xAB,0xEE,0x31,0xA2,0x73,0xF9,0xCA,0x3A,0x1A,0xFB,0x0D,0xC1,0xFE,0xFA,0xF2,0x6F,0xBD,0x96,0xDD,0x43,0x52,0xB6,0x08,0xF3,0xAE,0xBE,0x19,0x89,0x32,0x26,0xB0,0xEA,0x4B,0x64,0x84,0x82,0x6B,0xF5,0x79,0xBF,0x01,0x5F,0x75,0x63,0x1B,0x23,0x3D,0x68,0x2A,0x65,0xE8,0x91,0xF6,0xFF,0x13,0x58,0xF1,0x47,0x0A,0x7F,0xC5,0xA7,0xE7,0x61,0x5A,0x06,0x46,0x44,0x42,0x04,0xA0,0xDB,0x39,0x86,0x54,0xAA,0x8C,0x34,0x21,0x8B,0xF8,0x0C,0x74,0x67},
	{0x68,0x8D,0xCA,0x4D,0x73,0x4B,0x4E,0x2A,0xD4,0x52,0x26,0xB3,0x54,0x1E,0x19,0x1F,0x22,0x03,0x46,0x3D,0x2D,0x4A,0x53,0x83,0x13,0x8A,0xB7,0xD5,0x25,0x79,0xF5,0xBD,0x58,0x2F,0x0D,0x02,0xED,0x51,0x9E,0x11,0xF2,0x3E,0x55,0x5E,0xD1,0x16,0x3C,0x66,0x70,0x5D,0xF3,0x45,0x40,0xCC,0xE8,0x94,0x56,0x08,0xCE,0x1A,0x3A,0xD2,0xE1,0xDF,0xB5,0x38,0x6E,0x0E,0xE5,0xF4,0xF9,0x86,0xE9,0x4F,0xD6,0x85,0x23,0xCF,0x32,0x99,0x31,0x14,0xAE,0xEE,0xC8,0x48,0xD3,0x30,0xA1,0x92,0x41,0xB1,0x18,0xC4,0x2C,0x71,0x72,0x44,0x15,0xFD,0x37,0xBE,0x5F,0xAA,0x9B,0x88,0xD8,0xAB,0x89,0x9C,0xFA,0x60,0xEA,0xBC,0x62,0x0C,0x24,0xA6,0xA8,0xEC,0x67,0x20,0xDB,0x7C,0x28,0xDD,0xAC,0x5B,0x34,0x7E,0x10,0xF1,0x7B,0x8F,0x63,0xA0,0x05,0x9A,0x43,0x77,0x21,0xBF,0x27,0x09,0xC3,0x9F,0xB6,0xD7,0x29,0xC2,0xEB,0xC0,0xA4,0x8B,0x8C,0x1D,0xFB,0xFF,0xC1,0xB2,0x97,0x2E,0xF8,0x65,0xF6,0x75,0x07,0x04,0x49,0x33,0xE4,0xD9,0xB9,0xD0,0x42,0xC7,0x6C,0x90,0x00,0x8E,0x6F,0x50,0x01,0xC5,0xDA,0x47,0x3F,0xCD,0x69,0xA2,0xE2,0x7A,0xA7,0xC6,0x93,0x0F,0x0A,0x06,0xE6,0x2B,0x96,0xA3,0x1C,0xAF,0x6A,0x12,0x84,0x39,0xE7,0xB0,0x82,0xF7,0xFE,0x9D,0x87,0x5C,0x81,0x35,0xDE,0xB4,0xA5,0xFC,0x80,0xEF,0xCB,0xBB,0x6B,0x76,0xBA,0x5A,0x7D,0x78,0x0B,0x95,0xE3,0xAD,0x74,0x98,0x3B,0x36,0x64,0x6D,0xDC,0xF0,0x59,0xA9,0x4C,0x17,0x7F,0x91,0xB8,0xC9,0x57,0x1B,0xE0,0x61}
};
const byte _Sbox[][256] = {
	{0xA4,0xA2,0xA9,0xC5,0x4E,0xC9,0x03,0xD9,0x7E,0x0F,0xD2,0xAD,0xE7,0xD3,0x27,0x5B,0xE3,0xA1,0xE8,0xE6,0x7C,0x2A,0x55,0x0C,0x86,0x39,0xD7,0x8D,0xB8,0x12,0x6F,0x28,0xCD,0x8A,0x70,0x56,0x72,0xF9,0xBF,0x4F,0x73,0xE9,0xF7,0x57,0x16,0xAC,0x50,0xC0,0x9D,0xB7,0x47,0x71,0x60,0xC4,0x74,0x43,0x6C,0x1F,0x93,0x77,0xDC,0xCE,0x20,0x8C,0x99,0x5F,0x44,0x01,0xF5,0x1E,0x87,0x5E,0x61,0x2C,0x4B,0x1D,0x81,0x15,0xF4,0x23,0xD6,0xEA,0xE1,0x67,0xF1,0x7F,0xFE,0xDA,0x3C,0x07,0x53,0x6A,0x84,0x9C,0xCB,0x02,0x83,0x33,0xDD,0x35,0xE2,0x59,0x5A,0x98,0xA5,0x92,0x64,0x04,0x06,0x10,0x4D,0x1C,0x97,0x08,0x31,0xEE,0xAB,0x05,0xAF,0x79,0xA0,0x18,0x46,0x6D,0xFC,0x89,0xD4,0xC7,0xFF,0xF0,0xCF,0x42,0x91,0xF8,0x68,0x0A,0x65,0x8E,0xB6,0xFD,0xC3,0xEF,0x78,0x4C,0xCC,0x9E,0x30,0x2E,0xBC,0x0B,0x54,0x1A,0xA6,0xBB,0x26,0x80,0x48,0x94,0x32,0x7D,0xA7,0x3F,0xAE,0x22,0x3D,0x66,0xAA,0xF6,0x00,0x5D,0xBD,0x4A,0xE0,0x3B,0xB4,0x17,0x8B,0x9F,0x76,0xB0,0x24,0x9A,0x25,0x63,0xDB,0xEB,0x7A,0x3E,0x5C,0xB3,0xB1,0x29,0xF2,0xCA,0x58,0x6E,0xD8,0xA8,0x2F,0x75,0xDF,0x14,0xFB,0x13,0x49,0x88,0xB2,0xEC,0xE4,0x34,0x2D,0x96,0xC6,0x3A,0xED,0x95,0x0E,0xE5,0x85,0x6B,0x40,0x21,0x9B,0x09,0x19,0x2B,0x52,0xDE,0x45,0xA3,0xFA,0x51,0xC2,0xB5,0xD1,0x90,0xB9,0xF3,0x37,0xC1,0x0D,0xBA,0x41,0x11,0x38,0x7B,0xBE,0xD0,0xD5,0x69,0x36,0xC8,0x62,0x1B,0x82,0x8F},
	{0x83,0xF2,0x2A,0xEB,0xE9,0xBF,0x7B,0x9C,0x34,0x96,0x8D,0x98,0xB9,0x69,0x8C,0x29,0x3D,0x88,0x68,0x06,0x39,0x11,0x4C,0x0E,0xA0,0x56,0x40,0x92,0x15,0xBC,0xB3,0xDC,0x6F,0xF8,0x26,0xBA,0xBE,0xBD,0x31,0xFB,0xC3,0xFE,0x80,0x61,0xE1,0x7A,0x32,0xD2,0x70,0x20,0xA1,0x45,0xEC,0xD9,0x1A,0x5D,0xB4,0xD8,0x09,0xA5,0x55,0x8E,0x37,0x76,0xA9,0x67,0x10,0x17,0x36,0x65,0xB1,0x95,0x62,0x59,0x74,0xA3,0x50,0x2F,0x4B,0xC8,0xD0,0x8F,0xCD,0xD4,0x3C,0x86,0x12,0x1D,0x23,0xEF,0xF4,0x53,0x19,0x35,0xE6,0x7F,0x5E,0xD6,0x79,0x51,0x22,0x14,0xF7,0x1E,0x4A,0x42,0x9B,0x41,0x73,0x2D,0xC1,0x5C,0xA6,0xA2,0xE0,0x2E,0xD3,0x28,0xBB,0xC9,0xAE,0x6A,0xD1,0x5A,0x30,0x90,0x84,0xF9,0xB2,0x58,0xCF,0x7E,0xC5,0xCB,0x97,0xE4,0x16,0x6C,0xFA,0xB0,0x6D,0x1F,0x52,0x99,0x0D,0x4E,0x03,0x91,0xC2,0x4D,0x64,0x77,0x9F,0xDD,0xC4,0x49,0x8A,0x9A,0x24,0x38,0xA7,0x57,0x85,0xC7,0x7C,0x7D,0xE7,0xF6,0xB7,0xAC,0x27,0x46,0xDE,0xDF,0x3B,0xD7,0x9E,0x2B,0x0B,0xD5,0x13,0x75,0xF0,0x72,0xB6,0x9D,0x1B,0x01,0x3F,0x44,0xE5,0x87,0xFD,0x07,0xF1,0xAB,0x94,0x18,0xEA,0xFC,0x3A,0x82,0x5F,0x05,0x54,0xDB,0x00,0x8B,0xE3,0x48,0x0C,0xCA,0x78,0x89,0x0A,0xFF,0x3E,0x5B,0x81,0xEE,0x71,0xE2,0xDA,0x2C,0xB8,0xB5,0xCC,0x6E,0xA8,0x6B,0xAD,0x60,0xC6,0x08,0x04,0x02,0xE8,0xF5,0x4F,0xA4,0xF3,0xC0,0xCE,0x43,0x25,0x1C,0x21,0x33,0x0F,0xAF,0x47,0xED,0x66,0x63,0x93,0xAA},
	{0x45,0xD4,0x0B,0x43,0xF1,0x72,0xED,0xA4,0xC2,0x38,0xE6,0x71,0xFD,0xB6,0x3A,0x95,0x50,0x44,0x4B,0xE2,0x74,0x6B,0x1E,0x11,0x5A,0xC6,0xB4,0xD8,0xA5,0x8A,0x70,0xA3,0xA8,0xFA,0x05,0xD9,0x97,0x40,0xC9,0x90,0x98,0x8F,0xDC,0x12,0x31,0x2C,0x47,0x6A,0x99,0xAE,0xC8,0x7F,0xF9,0x4F,0x5D,0x96,0x6F,0xF4,0xB3,0x39,0x21,0xDA,0x9C,0x85,0x9E,0x3B,0xF0,0xBF,0xEF,0x06,0xEE,0xE5,0x5F,0x20,0x10,0xCC,0x3C,0x54,0x4A,0x52,0x94,0x0E,0xC0,0x28,0xF6,0x56,0x60,0xA2,0xE3,0x0F,0xEC,0x9D,0x24,0x83,0x7E,0xD5,0x7C,0xEB,0x18,0xD7,0xCD,0xDD,0x78,0xFF,0xDB,0xA1,0x09,0xD0,0x76,0x84,0x75,0xBB,0x1D,0x1A,0x2F,0xB0,0xFE,0xD6,0x34,0x63,0x35,0xD2,0x2A,0x59,0x6D,0x4D,0x77,0xE7,0x8E,0x61,0xCF,0x9F,0xCE,0x27,0xF5,0x80,0x86,0xC7,0xA6,0xFB,0xF8,0x87,0xAB,0x62,0x3F,0xDF,0x48,0x00,0x14,0x9A,0xBD,0x5B,0x04,0x92,0x02,0x25,0x65,0x4C,0x53,0x0C,0xF2,0x29,0xAF,0x17,0x6C,0x41,0x30,0xE9,0x93,0x55,0xF7,0xAC,0x68,0x26,0xC4,0x7D,0xCA,0x7A,0x3E,0xA0,0x37,0x03,0xC1,0x36,0x69,0x66,0x08,0x16,0xA7,0xBC,0xC5,0xD3,0x22,0xB7,0x13,0x46,0x32,0xE8,0x57,0x88,0x2B,0x81,0xB2,0x4E,0x64,0x1C,0xAA,0x91,0x58,0x2E,0x9B,0x5C,0x1B,0x51,0x73,0x42,0x23,0x01,0x6E,0xF3,0x0D,0xBE,0x3D,0x0A,0x2D,0x1F,0x67,0x33,0x19,0x7B,0x5E,0xEA,0xDE,0x8B,0xCB,0xA9,0x8C,0x8D,0xAD,0x49,0x82,0xE4,0xBA,0xC3,0x15,0xD1,0xE0,0x89,0xFC,0xB1,0xB9,0xB5,0x07,0x79,0xB8,0xE1},
	{0xB2,0xB6,0x23,0x11,0xA7,0x88,0xC5,0xA6,0x39,0x8F,0xC4,0xE8,0x73,0x22,0x43,0xC3,0x82,0x27,0xCD,0x18,0x51,0x62,0x2D,0xF7,0x5C,0x0E,0x3B,0xFD,0xCA,0x9B,0x0D,0x0F,0x79,0x8C,0x10,0x4C,0x74,0x1C,0x0A,0x8E,0x7C,0x94,0x07,0xC7,0x5E,0x14,0xA1,0x21,0x57,0x50,0x4E,0xA9,0x80,0xD9,0xEF,0x64,0x41,0xCF,0x3C,0xEE,0x2E,0x13,0x29,0xBA,0x34,0x5A,0xAE,0x8A,0x61,0x33,0x12,0xB9,0x55,0xA8,0x15,0x05,0xF6,0x03,0x06,0x49,0xB5,0x25,0x09,0x16,0x0C,0x2A,0x38,0xFC,0x20,0xF4,0xE5,0x7F,0xD7,0x31,0x2B,0x66,0x6F,0xFF,0x72,0x86,0xF0,0xA3,0x2F,0x78,0x00,0xBC,0xCC,0xE2,0xB0,0xF1,0x42,0xB4,0x30,0x5F,0x60,0x04,0xEC,0xA5,0xE3,0x8B,0xE7,0x1D,0xBF,0x84,0x7B,0xE6,0x81,0xF8,0xDE,0xD8,0xD2,0x17,0xCE,0x4B,0x47,0xD6,0x69,0x6C,0x19,0x99,0x9A,0x01,0xB3,0x85,0xB1,0xF9,0x59,0xC2,0x37,0xE9,0xC8,0xA0,0xED,0x4F,0x89,0x68,0x6D,0xD5,0x26,0x91,0x87,0x58,0xBD,0xC9,0x98,0xDC,0x75,0xC0,0x76,0xF5,0x67,0x6B,0x7E,0xEB,0x52,0xCB,0xD1,0x5B,0x9F,0x0B,0xDB,0x40,0x92,0x1A,0xFA,0xAC,0xE4,0xE1,0x71,0x1F,0x65,0x8D,0x97,0x9E,0x95,0x90,0x5D,0xB7,0xC1,0xAF,0x54,0xFB,0x02,0xE0,0x35,0xBB,0x3A,0x4D,0xAD,0x2C,0x3D,0x56,0x08,0x1B,0x4A,0x93,0x6A,0xAB,0xB8,0x7A,0xF2,0x7D,0xDA,0x3F,0xFE,0x3E,0xBE,0xEA,0xAA,0x44,0xC6,0xD0,0x36,0x48,0x70,0x96,0x77,0x24,0x53,0xDF,0xF3,0x83,0x28,0x32,0x45,0x1E,0xA4,0xD3,0xA2,0x46,0x6E,0x9C,0xDD,0x63,0xD4,0x9D}
};
const byte shiftedteta[][ROWLENGTH] = {
		{0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00},
		{0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00},
		{0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00},
		{0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00},
		{0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00},
		{0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00},
		{0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00},
		{0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00},
		{0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01},
		{0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02}
	};

const byte  v[] = {0x01,0x01,0x05,0x01,0x08,0x06,0x07,0x04};
const byte _v[] = {0xAD,0x95,0x76,0xA8,0x2F,0x49,0xD7,0xCA}; 

byte GFmul(byte a,byte b){
	if(a==0 || b==0) 
		return 0; 
	return pw2val[(pw2ind[a]+pw2ind[b])];
}

void print128(const byte *matrix){
	const byte C = 2;
	for(byte j=0;j<C;j++){
		for(byte i=0;i<ROWLENGTH;i++)
			printf("%02X",matrix[j*ROWLENGTH+i]);
		printf(" ");
	}
	printf("\n");
}
void print256(const byte *matrix){
	const byte C = 4;
	for(byte j=0;j<C;j++){
		for(byte i=0;i<ROWLENGTH;i++)
			printf("%02X",matrix[j*ROWLENGTH+i]);
		printf(" ");
		if(j==1) printf("\n");
	}
	printf("\n");
}

void print512(const byte *matrix){
	const byte C = 8;
	for(byte j=0;j<C;j++){
		for(byte i=0;i<ROWLENGTH;i++)
			printf("%02X",matrix[j*ROWLENGTH+i]);
		printf(" ");
		if(j&1) printf("\n");
	}
	printf("\n");
}

byte* expandKey(int blockSize, int keySize, const byte *rawKey, byte *destination = 0){
	byte C, R, C1;
	byte shift[ROWLENGTH];
	byte i,j,k,acc,carry_over,rot;
	unsigned int n,s,I,J;
	
	switch(blockSize){
		case 128: C = 2; C1 = 1; break;
		case 256: C = 4; C1 = 3; break;
		case 512: C = 8; C1 = 7; break;
		default: return (byte*)0;
	}
	switch(keySize){
		case 128: R = 10; break;
		case 256: R = 14; break;
		case 512: R = 18; break;
		default: return (byte*)0;
	}
	for(i=0;i<ROWLENGTH;i++)
		shift[i] = (i*blockSize)/512;
	byte CR = C*ROWLENGTH;
	byte *k1 = new byte[CR],//k1[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 *k2 = new byte[CR],
		 *k3 = new byte[CR],
		 *k4 = new byte[CR],
		 *k5 = new byte[CR];
	if(k1==(byte*)0 || k2==(byte*)0 || k3==(byte*)0 || k4==(byte*)0 || k5==(byte*)0)
		return (byte*)0;
	k1[0] = (blockSize + keySize + 64) / 64;
	for(i=1;i<CR;i++)
		k1[i]=0;
	const byte oddshift = (blockSize/4 + 24) / 8;
	const byte omegashift = (keySize == 2*blockSize)?C:0;
	byte *expandedKey;
	
	if(destination)
		expandedKey = destination;
	else{
		expandedKey = new byte[CR*(R+1)];
		if(expandedKey == 0)
			return (byte*)0;
	}
	for(j=0;j<C;j++){
		carry_over=0;
		for(i=0;i<ROWLENGTH;i++){
			k = j*ROWLENGTH+i;
			s = (unsigned int)carry_over + k1[k] + rawKey[k];
			if(s > 0xFF){
				s &= 0xFF;
				carry_over = 1;
			}else carry_over = 0;
			k1[k] = (byte)s;
			k1[k] = Sbox[i&3][k1[k]];
			k2[((j+shift[i])&C1)*ROWLENGTH+i]= k1[k];
		}
	}
	for(j=0;j<C;j++)
	for(i=0;i<ROWLENGTH;i++){
		acc = 0;
		for(k=0;k<ROWLENGTH;k++)
			acc ^= GFmul(v[(k-i+ROWLENGTH)&7],k2[j*ROWLENGTH+k]);
		k1[j*ROWLENGTH+i] = Sbox[i&3][acc ^ rawKey[(j+omegashift)*ROWLENGTH+i]];
		k3[((j+shift[i])&C1)*ROWLENGTH+i]= k1[j*ROWLENGTH+i];
	}
	for(j=0;j<C;j++){
		carry_over=0;
		for(i=0;i<ROWLENGTH;i++){
			acc = 0;
			for(k=0;k<ROWLENGTH;k++)
				acc ^= GFmul(v[(k-i+ROWLENGTH)&7],k3[j*ROWLENGTH+k]);
			s = (unsigned int)carry_over + acc + rawKey[j*ROWLENGTH+i];
			if(s > 0xFF){
				s &= 0xFF;
				carry_over = 1;
			}else carry_over = 0;			
			k1[j*ROWLENGTH+i] = Sbox[i&3][s];			
			k2[((j+shift[i])&C1)*ROWLENGTH+i]= k1[j*ROWLENGTH+i];
		}
	}
	for(j=0;j<C;j++)
	for(i=0;i<ROWLENGTH;i++){
		acc = 0;
		for(k=0;k<8;k++)
			acc ^= GFmul(v[(k-i+ROWLENGTH)&7],k2[j*ROWLENGTH+k]);
		k4[j*ROWLENGTH+i] = acc;
	}
	
	for(n=0;n<=R;n+=2)
	{
		for(j=0;j<C;j++){
			carry_over=0;
			for(i=0;i<ROWLENGTH;i++){
				k = j*ROWLENGTH+i;
				s = (unsigned int)carry_over + shiftedteta[n>>1][i] + k4[k];
				if(s > 0xFF){
					s &= 0xFF;
					carry_over = 1;
				}else carry_over = 0;
				k5[k] = s;
			}
		}
		for(j=0;j<C;j++){
			rot = (omegashift)?((n&2)*(C>>1)+n/4+j)&(2*C1+1):(j+(n/2))&C1;
			carry_over=0;
			for(i=0;i<ROWLENGTH;i++){
				k = j*ROWLENGTH+i;
				s = (unsigned int)carry_over + (rawKey[rot*ROWLENGTH+i]) + k5[k];
				if(s > 0xFF){
					s &= 0xFF;
					carry_over = 1;
				}else carry_over = 0;
				k1[k] = Sbox[i&3][s];
				k2[((j+shift[i])&C1)*ROWLENGTH+i]= k1[k];
			}
		}
		for(j=0;j<C;j++)
		for(i=0;i<ROWLENGTH;i++){
			acc = 0;
			for(k=0;k<8;k++)
				acc ^= GFmul(v[(k-i+ROWLENGTH)&7],k2[j*ROWLENGTH+k]);
			k1[j*ROWLENGTH+i] = Sbox[i&3][acc ^ k5[j*ROWLENGTH+i]];
			k3[((j+shift[i])&C1)*ROWLENGTH+i]= k1[j*ROWLENGTH+i];
		}
		for(j=0;j<C;j++){
			carry_over=0;
			for(i=0;i<ROWLENGTH;i++)
			{
				acc = 0;
				for(k=0;k<ROWLENGTH;k++)
					acc ^= GFmul(v[(k-i+ROWLENGTH)&7],k3[j*ROWLENGTH+k]);
				s = (unsigned int)carry_over + acc  + k5[j*ROWLENGTH+i];
				if(s > 0xFF){
					s &= 0xFF;
					carry_over = 1;
				}else carry_over = 0;
				expandedKey[n*C*ROWLENGTH + j*ROWLENGTH + i] = s;
			}
		}
		if(n<R){
			for(j=0;j<C;j++)
			for(i=0;i<ROWLENGTH;i++){
				I = (i+oddshift)&7;
				J = ((j+(i+oddshift)/ROWLENGTH)&C1);
				expandedKey[(n+1)*C*ROWLENGTH + j*ROWLENGTH + i] = 
					expandedKey[n*C*ROWLENGTH + J*ROWLENGTH + I];
			}
		}
	}
	
	return expandedKey;
}

byte* encrypt(int blockSize, int keySize, byte *initState, const byte *expandedKey, bool rewriteState = false){
	byte C, R, C1;
	byte shift[ROWLENGTH];
	byte i,j,k,acc,carry_over;
	unsigned int n,s;
	byte *stateMatrix,*tmp;
	
	switch(blockSize){
		case 128: C = 2; C1 = 1; break;
		case 256: C = 4; C1 = 3; break;
		case 512: C = 8; C1 = 7; break;
		default: return (byte*)0;
	}
	switch(keySize){
		case 128: R = 10; break;
		case 256: R = 14; break;
		case 512: R = 18; break;
		default: return (byte*)0;
	}
	for(i=0;i<ROWLENGTH;i++)
		shift[i] = (i*blockSize)/512;
	tmp = new byte[C*ROWLENGTH];
	if(tmp == (byte*)0)
		return (byte*)0;
	if(rewriteState)
		stateMatrix = initState;
	else{
		stateMatrix = new byte[C*ROWLENGTH];
		if(stateMatrix == (byte*)0)
			return (byte*)0;
		for(i=0;i<C*ROWLENGTH;i++)
			stateMatrix[i] = initState[i];
	}
	
	for(j=0;j<C;j++){
		carry_over=0;
		for(i=0;i<ROWLENGTH;i++){
			k = j*ROWLENGTH+i;
			s = stateMatrix[k] + expandedKey[k] + carry_over;
			if(s > 0xFF){
				s &= 0xFF;
				carry_over = 1;
			}else carry_over = 0;
			stateMatrix[k] = s;
		}
	}
	for(n=1;n<R;n++){
		for(j=0;j<C;j++)
		for(i=0;i<ROWLENGTH;i++){
			k = j*ROWLENGTH+i;
			stateMatrix[k] = Sbox[i&3][stateMatrix[k]];
			tmp[((j+shift[i])&C1)*ROWLENGTH+i]= stateMatrix[k];
		}
		for(j=0;j<C;j++)
		for(i=0;i<ROWLENGTH;i++){
			acc = 0;
			for(k=0;k<ROWLENGTH;k++)
				acc ^= GFmul(v[(k-i+ROWLENGTH)&7],tmp[j*ROWLENGTH+k]);
			stateMatrix[j*ROWLENGTH+i] = acc ^ expandedKey[n*C*ROWLENGTH + j*ROWLENGTH + i];
		}
	}
	for(j=0;j<C;j++)
	for(i=0;i<ROWLENGTH;i++){
		k = j*ROWLENGTH+i;
		stateMatrix[k] = Sbox[i&3][stateMatrix[k]];
		tmp[((j+shift[i])&C1)*ROWLENGTH+i]= stateMatrix[k];
	}
	for(j=0;j<C;j++){
		carry_over=0;
		for(i=0;i<ROWLENGTH;i++){
			acc = 0;
			for(k=0;k<ROWLENGTH;k++)
				acc ^= GFmul(v[(k-i+ROWLENGTH)&7],tmp[j*ROWLENGTH+k]);

			s = acc + expandedKey[n*C*ROWLENGTH + j*ROWLENGTH + i] + carry_over;
			if(s > 0xFF){
				s &= 0xFF;
				carry_over = 1;
			}else carry_over = 0;
			stateMatrix[j*ROWLENGTH + i] = s;
		}
	}
	return stateMatrix;
}

byte* decrypt(int blockSize, int keySize, byte *initState, const byte *expandedKey, bool rewriteState = false){
	byte C, R, C1;
	byte shift[ROWLENGTH];
	byte i,j,k,acc,carry_over;
	int n,s;
	byte *stateMatrix,*tmp;
	
	switch(blockSize){
		case 128: C = 2; C1 = 1; break;
		case 256: C = 4; C1 = 3; break;
		case 512: C = 8; C1 = 7; break;
		default: return (byte*)0;
	}
	switch(keySize){
		case 128: R = 10; break;
		case 256: R = 14; break;
		case 512: R = 18; break;
		default: return (byte*)0;
	}
	for(i=0;i<ROWLENGTH;i++)
		shift[i] = (i*blockSize)/512;
	tmp = new byte[C*ROWLENGTH];
	if(tmp == (byte*)0)
		return (byte*)0;
	if(rewriteState)
		stateMatrix = initState;
	else{
		stateMatrix = new byte[C*ROWLENGTH];
		if(stateMatrix == (byte*)0)
			return (byte*)0;
		for(i=0;i<C*ROWLENGTH;i++)
			stateMatrix[i] = initState[i];
	}
	for(j=0;j<C;j++){
		carry_over=0;
		for(i=0;i<ROWLENGTH;i++){
			k = j*ROWLENGTH+i;
			s = stateMatrix[k] - expandedKey[R*C*ROWLENGTH + k] - carry_over;
			if(s < 0){
				s = (s + 0x100) & 0xFF;
				carry_over = 1;
			}else carry_over = 0;
			stateMatrix[k] = s;
		}
	}
	for(j=0;j<C;j++)
	for(i=0;i<ROWLENGTH;i++){
		acc = 0;
		for(k=0;k<ROWLENGTH;k++)
			acc ^= GFmul(_v[(k-i+ROWLENGTH)&7],stateMatrix[j*ROWLENGTH+k]);
		tmp[((j-shift[i]+C)&C1)*ROWLENGTH+i] = _Sbox[i&3][acc];
	}
	for(n=R-1;n>0;n--)
	{
		for(j=0;j<C;j++)
		for(i=0;i<ROWLENGTH;i++){
			k = j*ROWLENGTH+i;
			stateMatrix[k] = tmp[k] ^ expandedKey[n*C*ROWLENGTH + k];
		}
		for(j=0;j<C;j++)
		for(i=0;i<ROWLENGTH;i++){
			acc = 0;
			for(k=0;k<ROWLENGTH;k++)
				acc ^= GFmul(_v[(k-i+8)&7],stateMatrix[j*ROWLENGTH+k]);
			tmp[((j-shift[i]+C)&C1)*ROWLENGTH+i] = _Sbox[i&3][acc];
		}
	}
	for(j=0;j<C;j++){
		carry_over=0;
		for(i=0;i<ROWLENGTH;i++){
			k = j*ROWLENGTH+i;
			s = tmp[k] - expandedKey[k] - carry_over;
			if(s < 0){
				s = (s + 0x100) & 0xFF;
				carry_over = 1;
			}else carry_over = 0;
			stateMatrix[k] = s;
		}
	}
	return stateMatrix;
}

int main(int,char**){
	byte  key128[] = {0,1,2,3,4,5,6,7, 8,9,10,11,12,13,14,15},
		  keyD128[] = {0x6F,0x6E,0x6D,0x6C,0x6B,0x6A,0x69,0x68,0x67,0x66,0x65,0x64,0x63,0x62,0x61,0x60},
		  block128[] = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,  0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F},
		  blockD128[] = {0x1F,0x1E,0x1D,0x1C,0x1B,0x1A,0x19,0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x11,0x10},
		  blockDD128[] = {0x2F,0x2E,0x2D,0x2C,0x2B,0x2A,0x29,0x28,0x27,0x26,0x25,0x24,0x23,0x22,0x21,0x20},
		  key256[] = {0,1,2,3,4,5,6,7, 8,9,10,11,12,13,14,15, 16,17,18,19,20,21,22,23, 24,25,26,27,28,29,30,31},
		  block256[] = {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F, 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F},
		  keyD256[] = {0x1F,0x1E,0x1D,0x1C,0x1B,0x1A,0x19,0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x11,0x10, 0x0F,0x0E,0x0D,0x0C,0x0B,0x0A,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00},
		  blockD256[] = {0x3F,0x3E,0x3D,0x3C,0x3B,0x3A,0x39,0x38,0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30, 0x2F,0x2E,0x2D,0x2C,0x2B,0x2A,0x29,0x28,0x27,0x26,0x25,0x24,0x23,0x22,0x21,0x20},
		  blockDD256[] = {0x5F,0x5E,0x5D,0x5C,0x5B,0x5A,0x59,0x58,0x57,0x56,0x55,0x54,0x53,0x52,0x51,0x50, 0x4F,0x4E,0x4D,0x4C,0x4B,0x4A,0x49,0x48,0x47,0x46,0x45,0x44,0x43,0x42,0x41,0x40},
		  key512[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F, 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F, 0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F, 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F},
		  block512[] = {0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F, 0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F, 0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F, 0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F},
		  keyD512[] = {0x3F,0x3E,0x3D,0x3C,0x3B,0x3A,0x39,0x38,0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30, 0x2F,0x2E,0x2D,0x2C,0x2B,0x2A,0x29,0x28,0x27,0x26,0x25,0x24,0x23,0x22,0x21,0x20, 0x1F,0x1E,0x1D,0x1C,0x1B,0x1A,0x19,0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x11,0x10, 0x0F,0x0E,0x0D,0x0C,0x0B,0x0A,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00},
		  blockD512[] = {0x7F,0x7E,0x7D,0x7C,0x7B,0x7A,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70, 0x6F,0x6E,0x6D,0x6C,0x6B,0x6A,0x69,0x68,0x67,0x66,0x65,0x64,0x63,0x62,0x61,0x60, 0x5F,0x5E,0x5D,0x5C,0x5B,0x5A,0x59,0x58,0x57,0x56,0x55,0x54,0x53,0x52,0x51,0x50, 0x4F,0x4E,0x4D,0x4C,0x4B,0x4A,0x49,0x48,0x47,0x46,0x45,0x44,0x43,0x42,0x41,0x40},
		  *res;
		  
	byte *expandedKey128 = new byte[ROWLENGTH*2*(10+1)],
		 *expandedKey256 = new byte[ROWLENGTH*4*(14+1)],
		 *expandedKey512;// = new byte[ROWLENGTH*8*(18+1)];
	
	//print512(keyD512);
	//print512(blockD512);
	//expand_512_512(keyD512,expandedKey512);
	//res = decrypt(512,512,blockD512,expandedKey512);
	//print512(expandedKey512);
	//print512(res);
	
	//expand_256_256(key256,expandedKey256);
	//encode_256_256(block256,expandedKey256);
	//encrypt(256,256,block256,expandedKey256);
	//print256(block256);
	
	//expand_256_256(key256,expandedKey256);
	//decode_256_256(blockD256,expandedKey256);
	//res = decrypt(256,256,blockD256,expandedKey256);
	//print256(res);
	
	//expand_128_128(key128,expandedKey128);
	//encrypt(128,128,block128,expandedKey128);
	//print128(block128);
		 
	//expand_128_128(key128,expandedKey128);
	//res = decrypt(128,128,blockD128,expandedKey128);
	//print128(res);
	//expandKey(512,512,key512,expandedKey512);
	//expandKey(128,256,key256,expandedKey256);
	//expandKey(256,512,key512,expandedKey512);
	/*for(unsigned char n=0;n<=18;n++){
		printf("%d ",n);
		//print256(expandedKey256 + n*4*ROWLENGTH);
		print256(expandedKey512 + n*4*ROWLENGTH);
		//print128(expandedKey256 + n*2*ROWLENGTH);
		//print512(expandedKey512 + n*8*ROWLENGTH);
	}*/
	
	//encode_128_128(block128,expandedKey128);
		 
	//expandKey(128,256,key256,expandedKey256);
	//res = encrypt(128,256,block256,expandedKey256);
	//print128(res);
	
	//expandKey(128,256,keyD256,expandedKey256);
	//res = decrypt(128,256,blockDD128,expandedKey256);
	//print128(res);
		 
	//expandKey(256,512,key512,expandedKey512);
	//res = encrypt(256,512,block512,expandedKey512);
	//print256(res);
	
	expandedKey512 = expandKey(256,512,keyD512);
	res = decrypt(256,512,blockDD256,expandedKey512);
	print256(res);
	
	return getch();
}
