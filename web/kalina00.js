function Kalina(b,k){
    var I=this,i,j;
    if(b==128){I.c = 2; I.c_1 = 1;}else if(b==256){I.c = 4; I.c_1 = 3;}else if(b==512){I.c = 8; I.c_1 = 7;}else throw "Invalid block size"; 
    if(k==128)I.r = 10;else if(k==256)I.r = 14;else if(k==512)I.r = 18;else throw "Invalid key size";
    I.b=b;I.k=k;
    I.pw2val = [1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,44,88,176,125,250,233,207,131,27,54,108,216,173,71,142,1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,44,88,176,125,250,233,207,131,27,54,108,216,173,71,142,1];
    I.pw2ind = [0,0,1,25,2,50,26,198,3,223,51,238,27,104,199,75,4,100,224,14,52,141,239,129,28,193,105,248,200,8,76,113,5,138,101,47,225,36,15,33,53,147,142,218,240,18,130,69,29,181,194,125,106,39,249,185,201,154,9,120,77,228,114,166,6,191,139,98,102,221,48,253,226,152,37,179,16,145,34,136,54,208,148,206,143,150,219,189,241,210,19,92,131,56,70,64,30,66,182,163,195,72,126,110,107,58,40,84,250,133,186,61,202,94,155,159,10,21,121,43,78,212,229,172,115,243,167,87,7,112,192,247,140,128,99,13,103,74,222,237,49,197,254,24,227,165,153,119,38,184,180,124,17,68,146,217,35,32,137,46,55,63,209,91,149,188,207,205,144,135,151,178,220,252,190,97,242,86,211,171,20,42,93,158,132,60,57,83,71,109,65,162,31,45,67,216,183,123,164,118,196,23,73,236,127,12,111,246,108,161,59,82,41,157,85,170,251,96,134,177,187,204,62,90,203,89,95,176,156,169,160,81,11,245,22,235,122,117,44,215,79,174,213,233,230,231,173,232,116,214,244,234,168,80,88,175];
	I.Sbox = [];
    I.Sbox[0]  = [0xA8,0x43,0x5F,0x06,0x6B,0x75,0x6C,0x59,0x71,0xDF,0x87,0x95,0x17,0xF0,0xD8,0x09,0x6D,0xF3,0x1D,0xCB,0xC9,0x4D,0x2C,0xAF,0x79,0xE0,0x97,0xFD,0x6F,0x4B,0x45,0x39,0x3E,0xDD,0xA3,0x4F,0xB4,0xB6,0x9A,0x0E,0x1F,0xBF,0x15,0xE1,0x49,0xD2,0x93,0xC6,0x92,0x72,0x9E,0x61,0xD1,0x63,0xFA,0xEE,0xF4,0x19,0xD5,0xAD,0x58,0xA4,0xBB,0xA1,0xDC,0xF2,0x83,0x37,0x42,0xE4,0x7A,0x32,0x9C,0xCC,0xAB,0x4A,0x8F,0x6E,0x04,0x27,0x2E,0xE7,0xE2,0x5A,0x96,0x16,0x23,0x2B,0xC2,0x65,0x66,0x0F,0xBC,0xA9,0x47,0x41,0x34,0x48,0xFC,0xB7,0x6A,0x88,0xA5,0x53,0x86,0xF9,0x5B,0xDB,0x38,0x7B,0xC3,0x1E,0x22,0x33,0x24,0x28,0x36,0xC7,0xB2,0x3B,0x8E,0x77,0xBA,0xF5,0x14,0x9F,0x08,0x55,0x9B,0x4C,0xFE,0x60,0x5C,0xDA,0x18,0x46,0xCD,0x7D,0x21,0xB0,0x3F,0x1B,0x89,0xFF,0xEB,0x84,0x69,0x3A,0x9D,0xD7,0xD3,0x70,0x67,0x40,0xB5,0xDE,0x5D,0x30,0x91,0xB1,0x78,0x11,0x01,0xE5,0x00,0x68,0x98,0xA0,0xC5,0x02,0xA6,0x74,0x2D,0x0B,0xA2,0x76,0xB3,0xBE,0xCE,0xBD,0xAE,0xE9,0x8A,0x31,0x1C,0xEC,0xF1,0x99,0x94,0xAA,0xF6,0x26,0x2F,0xEF,0xE8,0x8C,0x35,0x03,0xD4,0x7F,0xFB,0x05,0xC1,0x5E,0x90,0x20,0x3D,0x82,0xF7,0xEA,0x0A,0x0D,0x7E,0xF8,0x50,0x1A,0xC4,0x07,0x57,0xB8,0x3C,0x62,0xE3,0xC8,0xAC,0x52,0x64,0x10,0xD0,0xD9,0x13,0x0C,0x12,0x29,0x51,0xB9,0xCF,0xD6,0x73,0x8D,0x81,0x54,0xC0,0xED,0x4E,0x44,0xA7,0x2A,0x85,0x25,0xE6,0xCA,0x7C,0x8B,0x56,0x80];
    I.Sbox[1]  = [0xCE,0xBB,0xEB,0x92,0xEA,0xCB,0x13,0xC1,0xE9,0x3A,0xD6,0xB2,0xD2,0x90,0x17,0xF8,0x42,0x15,0x56,0xB4,0x65,0x1C,0x88,0x43,0xC5,0x5C,0x36,0xBA,0xF5,0x57,0x67,0x8D,0x31,0xF6,0x64,0x58,0x9E,0xF4,0x22,0xAA,0x75,0x0F,0x02,0xB1,0xDF,0x6D,0x73,0x4D,0x7C,0x26,0x2E,0xF7,0x08,0x5D,0x44,0x3E,0x9F,0x14,0xC8,0xAE,0x54,0x10,0xD8,0xBC,0x1A,0x6B,0x69,0xF3,0xBD,0x33,0xAB,0xFA,0xD1,0x9B,0x68,0x4E,0x16,0x95,0x91,0xEE,0x4C,0x63,0x8E,0x5B,0xCC,0x3C,0x19,0xA1,0x81,0x49,0x7B,0xD9,0x6F,0x37,0x60,0xCA,0xE7,0x2B,0x48,0xFD,0x96,0x45,0xFC,0x41,0x12,0x0D,0x79,0xE5,0x89,0x8C,0xE3,0x20,0x30,0xDC,0xB7,0x6C,0x4A,0xB5,0x3F,0x97,0xD4,0x62,0x2D,0x06,0xA4,0xA5,0x83,0x5F,0x2A,0xDA,0xC9,0x00,0x7E,0xA2,0x55,0xBF,0x11,0xD5,0x9C,0xCF,0x0E,0x0A,0x3D,0x51,0x7D,0x93,0x1B,0xFE,0xC4,0x47,0x09,0x86,0x0B,0x8F,0x9D,0x6A,0x07,0xB9,0xB0,0x98,0x18,0x32,0x71,0x4B,0xEF,0x3B,0x70,0xA0,0xE4,0x40,0xFF,0xC3,0xA9,0xE6,0x78,0xF9,0x8B,0x46,0x80,0x1E,0x38,0xE1,0xB8,0xA8,0xE0,0x0C,0x23,0x76,0x1D,0x25,0x24,0x05,0xF1,0x6E,0x94,0x28,0x9A,0x84,0xE8,0xA3,0x4F,0x77,0xD3,0x85,0xE2,0x52,0xF2,0x82,0x50,0x7A,0x2F,0x74,0x53,0xB3,0x61,0xAF,0x39,0x35,0xDE,0xCD,0x1F,0x99,0xAC,0xAD,0x72,0x2C,0xDD,0xD0,0x87,0xBE,0x5E,0xA6,0xEC,0x04,0xC6,0x03,0x34,0xFB,0xDB,0x59,0xB6,0xC2,0x01,0xF0,0x5A,0xED,0xA7,0x66,0x21,0x7F,0x8A,0x27,0xC7,0xC0,0x29,0xD7];
    I.Sbox[2]  = [0x93,0xD9,0x9A,0xB5,0x98,0x22,0x45,0xFC,0xBA,0x6A,0xDF,0x02,0x9F,0xDC,0x51,0x59,0x4A,0x17,0x2B,0xC2,0x94,0xF4,0xBB,0xA3,0x62,0xE4,0x71,0xD4,0xCD,0x70,0x16,0xE1,0x49,0x3C,0xC0,0xD8,0x5C,0x9B,0xAD,0x85,0x53,0xA1,0x7A,0xC8,0x2D,0xE0,0xD1,0x72,0xA6,0x2C,0xC4,0xE3,0x76,0x78,0xB7,0xB4,0x09,0x3B,0x0E,0x41,0x4C,0xDE,0xB2,0x90,0x25,0xA5,0xD7,0x03,0x11,0x00,0xC3,0x2E,0x92,0xEF,0x4E,0x12,0x9D,0x7D,0xCB,0x35,0x10,0xD5,0x4F,0x9E,0x4D,0xA9,0x55,0xC6,0xD0,0x7B,0x18,0x97,0xD3,0x36,0xE6,0x48,0x56,0x81,0x8F,0x77,0xCC,0x9C,0xB9,0xE2,0xAC,0xB8,0x2F,0x15,0xA4,0x7C,0xDA,0x38,0x1E,0x0B,0x05,0xD6,0x14,0x6E,0x6C,0x7E,0x66,0xFD,0xB1,0xE5,0x60,0xAF,0x5E,0x33,0x87,0xC9,0xF0,0x5D,0x6D,0x3F,0x88,0x8D,0xC7,0xF7,0x1D,0xE9,0xEC,0xED,0x80,0x29,0x27,0xCF,0x99,0xA8,0x50,0x0F,0x37,0x24,0x28,0x30,0x95,0xD2,0x3E,0x5B,0x40,0x83,0xB3,0x69,0x57,0x1F,0x07,0x1C,0x8A,0xBC,0x20,0xEB,0xCE,0x8E,0xAB,0xEE,0x31,0xA2,0x73,0xF9,0xCA,0x3A,0x1A,0xFB,0x0D,0xC1,0xFE,0xFA,0xF2,0x6F,0xBD,0x96,0xDD,0x43,0x52,0xB6,0x08,0xF3,0xAE,0xBE,0x19,0x89,0x32,0x26,0xB0,0xEA,0x4B,0x64,0x84,0x82,0x6B,0xF5,0x79,0xBF,0x01,0x5F,0x75,0x63,0x1B,0x23,0x3D,0x68,0x2A,0x65,0xE8,0x91,0xF6,0xFF,0x13,0x58,0xF1,0x47,0x0A,0x7F,0xC5,0xA7,0xE7,0x61,0x5A,0x06,0x46,0x44,0x42,0x04,0xA0,0xDB,0x39,0x86,0x54,0xAA,0x8C,0x34,0x21,0x8B,0xF8,0x0C,0x74,0x67];
    I.Sbox[3]  = [0x68,0x8D,0xCA,0x4D,0x73,0x4B,0x4E,0x2A,0xD4,0x52,0x26,0xB3,0x54,0x1E,0x19,0x1F,0x22,0x03,0x46,0x3D,0x2D,0x4A,0x53,0x83,0x13,0x8A,0xB7,0xD5,0x25,0x79,0xF5,0xBD,0x58,0x2F,0x0D,0x02,0xED,0x51,0x9E,0x11,0xF2,0x3E,0x55,0x5E,0xD1,0x16,0x3C,0x66,0x70,0x5D,0xF3,0x45,0x40,0xCC,0xE8,0x94,0x56,0x08,0xCE,0x1A,0x3A,0xD2,0xE1,0xDF,0xB5,0x38,0x6E,0x0E,0xE5,0xF4,0xF9,0x86,0xE9,0x4F,0xD6,0x85,0x23,0xCF,0x32,0x99,0x31,0x14,0xAE,0xEE,0xC8,0x48,0xD3,0x30,0xA1,0x92,0x41,0xB1,0x18,0xC4,0x2C,0x71,0x72,0x44,0x15,0xFD,0x37,0xBE,0x5F,0xAA,0x9B,0x88,0xD8,0xAB,0x89,0x9C,0xFA,0x60,0xEA,0xBC,0x62,0x0C,0x24,0xA6,0xA8,0xEC,0x67,0x20,0xDB,0x7C,0x28,0xDD,0xAC,0x5B,0x34,0x7E,0x10,0xF1,0x7B,0x8F,0x63,0xA0,0x05,0x9A,0x43,0x77,0x21,0xBF,0x27,0x09,0xC3,0x9F,0xB6,0xD7,0x29,0xC2,0xEB,0xC0,0xA4,0x8B,0x8C,0x1D,0xFB,0xFF,0xC1,0xB2,0x97,0x2E,0xF8,0x65,0xF6,0x75,0x07,0x04,0x49,0x33,0xE4,0xD9,0xB9,0xD0,0x42,0xC7,0x6C,0x90,0x00,0x8E,0x6F,0x50,0x01,0xC5,0xDA,0x47,0x3F,0xCD,0x69,0xA2,0xE2,0x7A,0xA7,0xC6,0x93,0x0F,0x0A,0x06,0xE6,0x2B,0x96,0xA3,0x1C,0xAF,0x6A,0x12,0x84,0x39,0xE7,0xB0,0x82,0xF7,0xFE,0x9D,0x87,0x5C,0x81,0x35,0xDE,0xB4,0xA5,0xFC,0x80,0xEF,0xCB,0xBB,0x6B,0x76,0xBA,0x5A,0x7D,0x78,0x0B,0x95,0xE3,0xAD,0x74,0x98,0x3B,0x36,0x64,0x6D,0xDC,0xF0,0x59,0xA9,0x4C,0x17,0x7F,0x91,0xB8,0xC9,0x57,0x1B,0xE0,0x61];
    I.Sbox[4]  = I.Sbox[0];
    I.Sbox[5]  = I.Sbox[1];
    I.Sbox[6]  = I.Sbox[2];
    I.Sbox[7]  = I.Sbox[3];
    I._Sbox =    [];
    I._Sbox[0] = [0xA4,0xA2,0xA9,0xC5,0x4E,0xC9,0x03,0xD9,0x7E,0x0F,0xD2,0xAD,0xE7,0xD3,0x27,0x5B,0xE3,0xA1,0xE8,0xE6,0x7C,0x2A,0x55,0x0C,0x86,0x39,0xD7,0x8D,0xB8,0x12,0x6F,0x28,0xCD,0x8A,0x70,0x56,0x72,0xF9,0xBF,0x4F,0x73,0xE9,0xF7,0x57,0x16,0xAC,0x50,0xC0,0x9D,0xB7,0x47,0x71,0x60,0xC4,0x74,0x43,0x6C,0x1F,0x93,0x77,0xDC,0xCE,0x20,0x8C,0x99,0x5F,0x44,0x01,0xF5,0x1E,0x87,0x5E,0x61,0x2C,0x4B,0x1D,0x81,0x15,0xF4,0x23,0xD6,0xEA,0xE1,0x67,0xF1,0x7F,0xFE,0xDA,0x3C,0x07,0x53,0x6A,0x84,0x9C,0xCB,0x02,0x83,0x33,0xDD,0x35,0xE2,0x59,0x5A,0x98,0xA5,0x92,0x64,0x04,0x06,0x10,0x4D,0x1C,0x97,0x08,0x31,0xEE,0xAB,0x05,0xAF,0x79,0xA0,0x18,0x46,0x6D,0xFC,0x89,0xD4,0xC7,0xFF,0xF0,0xCF,0x42,0x91,0xF8,0x68,0x0A,0x65,0x8E,0xB6,0xFD,0xC3,0xEF,0x78,0x4C,0xCC,0x9E,0x30,0x2E,0xBC,0x0B,0x54,0x1A,0xA6,0xBB,0x26,0x80,0x48,0x94,0x32,0x7D,0xA7,0x3F,0xAE,0x22,0x3D,0x66,0xAA,0xF6,0x00,0x5D,0xBD,0x4A,0xE0,0x3B,0xB4,0x17,0x8B,0x9F,0x76,0xB0,0x24,0x9A,0x25,0x63,0xDB,0xEB,0x7A,0x3E,0x5C,0xB3,0xB1,0x29,0xF2,0xCA,0x58,0x6E,0xD8,0xA8,0x2F,0x75,0xDF,0x14,0xFB,0x13,0x49,0x88,0xB2,0xEC,0xE4,0x34,0x2D,0x96,0xC6,0x3A,0xED,0x95,0x0E,0xE5,0x85,0x6B,0x40,0x21,0x9B,0x09,0x19,0x2B,0x52,0xDE,0x45,0xA3,0xFA,0x51,0xC2,0xB5,0xD1,0x90,0xB9,0xF3,0x37,0xC1,0x0D,0xBA,0x41,0x11,0x38,0x7B,0xBE,0xD0,0xD5,0x69,0x36,0xC8,0x62,0x1B,0x82,0x8F];
    I._Sbox[1] = [0x83,0xF2,0x2A,0xEB,0xE9,0xBF,0x7B,0x9C,0x34,0x96,0x8D,0x98,0xB9,0x69,0x8C,0x29,0x3D,0x88,0x68,0x06,0x39,0x11,0x4C,0x0E,0xA0,0x56,0x40,0x92,0x15,0xBC,0xB3,0xDC,0x6F,0xF8,0x26,0xBA,0xBE,0xBD,0x31,0xFB,0xC3,0xFE,0x80,0x61,0xE1,0x7A,0x32,0xD2,0x70,0x20,0xA1,0x45,0xEC,0xD9,0x1A,0x5D,0xB4,0xD8,0x09,0xA5,0x55,0x8E,0x37,0x76,0xA9,0x67,0x10,0x17,0x36,0x65,0xB1,0x95,0x62,0x59,0x74,0xA3,0x50,0x2F,0x4B,0xC8,0xD0,0x8F,0xCD,0xD4,0x3C,0x86,0x12,0x1D,0x23,0xEF,0xF4,0x53,0x19,0x35,0xE6,0x7F,0x5E,0xD6,0x79,0x51,0x22,0x14,0xF7,0x1E,0x4A,0x42,0x9B,0x41,0x73,0x2D,0xC1,0x5C,0xA6,0xA2,0xE0,0x2E,0xD3,0x28,0xBB,0xC9,0xAE,0x6A,0xD1,0x5A,0x30,0x90,0x84,0xF9,0xB2,0x58,0xCF,0x7E,0xC5,0xCB,0x97,0xE4,0x16,0x6C,0xFA,0xB0,0x6D,0x1F,0x52,0x99,0x0D,0x4E,0x03,0x91,0xC2,0x4D,0x64,0x77,0x9F,0xDD,0xC4,0x49,0x8A,0x9A,0x24,0x38,0xA7,0x57,0x85,0xC7,0x7C,0x7D,0xE7,0xF6,0xB7,0xAC,0x27,0x46,0xDE,0xDF,0x3B,0xD7,0x9E,0x2B,0x0B,0xD5,0x13,0x75,0xF0,0x72,0xB6,0x9D,0x1B,0x01,0x3F,0x44,0xE5,0x87,0xFD,0x07,0xF1,0xAB,0x94,0x18,0xEA,0xFC,0x3A,0x82,0x5F,0x05,0x54,0xDB,0x00,0x8B,0xE3,0x48,0x0C,0xCA,0x78,0x89,0x0A,0xFF,0x3E,0x5B,0x81,0xEE,0x71,0xE2,0xDA,0x2C,0xB8,0xB5,0xCC,0x6E,0xA8,0x6B,0xAD,0x60,0xC6,0x08,0x04,0x02,0xE8,0xF5,0x4F,0xA4,0xF3,0xC0,0xCE,0x43,0x25,0x1C,0x21,0x33,0x0F,0xAF,0x47,0xED,0x66,0x63,0x93,0xAA];
    I._Sbox[2] = [0x45,0xD4,0x0B,0x43,0xF1,0x72,0xED,0xA4,0xC2,0x38,0xE6,0x71,0xFD,0xB6,0x3A,0x95,0x50,0x44,0x4B,0xE2,0x74,0x6B,0x1E,0x11,0x5A,0xC6,0xB4,0xD8,0xA5,0x8A,0x70,0xA3,0xA8,0xFA,0x05,0xD9,0x97,0x40,0xC9,0x90,0x98,0x8F,0xDC,0x12,0x31,0x2C,0x47,0x6A,0x99,0xAE,0xC8,0x7F,0xF9,0x4F,0x5D,0x96,0x6F,0xF4,0xB3,0x39,0x21,0xDA,0x9C,0x85,0x9E,0x3B,0xF0,0xBF,0xEF,0x06,0xEE,0xE5,0x5F,0x20,0x10,0xCC,0x3C,0x54,0x4A,0x52,0x94,0x0E,0xC0,0x28,0xF6,0x56,0x60,0xA2,0xE3,0x0F,0xEC,0x9D,0x24,0x83,0x7E,0xD5,0x7C,0xEB,0x18,0xD7,0xCD,0xDD,0x78,0xFF,0xDB,0xA1,0x09,0xD0,0x76,0x84,0x75,0xBB,0x1D,0x1A,0x2F,0xB0,0xFE,0xD6,0x34,0x63,0x35,0xD2,0x2A,0x59,0x6D,0x4D,0x77,0xE7,0x8E,0x61,0xCF,0x9F,0xCE,0x27,0xF5,0x80,0x86,0xC7,0xA6,0xFB,0xF8,0x87,0xAB,0x62,0x3F,0xDF,0x48,0x00,0x14,0x9A,0xBD,0x5B,0x04,0x92,0x02,0x25,0x65,0x4C,0x53,0x0C,0xF2,0x29,0xAF,0x17,0x6C,0x41,0x30,0xE9,0x93,0x55,0xF7,0xAC,0x68,0x26,0xC4,0x7D,0xCA,0x7A,0x3E,0xA0,0x37,0x03,0xC1,0x36,0x69,0x66,0x08,0x16,0xA7,0xBC,0xC5,0xD3,0x22,0xB7,0x13,0x46,0x32,0xE8,0x57,0x88,0x2B,0x81,0xB2,0x4E,0x64,0x1C,0xAA,0x91,0x58,0x2E,0x9B,0x5C,0x1B,0x51,0x73,0x42,0x23,0x01,0x6E,0xF3,0x0D,0xBE,0x3D,0x0A,0x2D,0x1F,0x67,0x33,0x19,0x7B,0x5E,0xEA,0xDE,0x8B,0xCB,0xA9,0x8C,0x8D,0xAD,0x49,0x82,0xE4,0xBA,0xC3,0x15,0xD1,0xE0,0x89,0xFC,0xB1,0xB9,0xB5,0x07,0x79,0xB8,0xE1];
    I._Sbox[3] = [0xB2,0xB6,0x23,0x11,0xA7,0x88,0xC5,0xA6,0x39,0x8F,0xC4,0xE8,0x73,0x22,0x43,0xC3,0x82,0x27,0xCD,0x18,0x51,0x62,0x2D,0xF7,0x5C,0x0E,0x3B,0xFD,0xCA,0x9B,0x0D,0x0F,0x79,0x8C,0x10,0x4C,0x74,0x1C,0x0A,0x8E,0x7C,0x94,0x07,0xC7,0x5E,0x14,0xA1,0x21,0x57,0x50,0x4E,0xA9,0x80,0xD9,0xEF,0x64,0x41,0xCF,0x3C,0xEE,0x2E,0x13,0x29,0xBA,0x34,0x5A,0xAE,0x8A,0x61,0x33,0x12,0xB9,0x55,0xA8,0x15,0x05,0xF6,0x03,0x06,0x49,0xB5,0x25,0x09,0x16,0x0C,0x2A,0x38,0xFC,0x20,0xF4,0xE5,0x7F,0xD7,0x31,0x2B,0x66,0x6F,0xFF,0x72,0x86,0xF0,0xA3,0x2F,0x78,0x00,0xBC,0xCC,0xE2,0xB0,0xF1,0x42,0xB4,0x30,0x5F,0x60,0x04,0xEC,0xA5,0xE3,0x8B,0xE7,0x1D,0xBF,0x84,0x7B,0xE6,0x81,0xF8,0xDE,0xD8,0xD2,0x17,0xCE,0x4B,0x47,0xD6,0x69,0x6C,0x19,0x99,0x9A,0x01,0xB3,0x85,0xB1,0xF9,0x59,0xC2,0x37,0xE9,0xC8,0xA0,0xED,0x4F,0x89,0x68,0x6D,0xD5,0x26,0x91,0x87,0x58,0xBD,0xC9,0x98,0xDC,0x75,0xC0,0x76,0xF5,0x67,0x6B,0x7E,0xEB,0x52,0xCB,0xD1,0x5B,0x9F,0x0B,0xDB,0x40,0x92,0x1A,0xFA,0xAC,0xE4,0xE1,0x71,0x1F,0x65,0x8D,0x97,0x9E,0x95,0x90,0x5D,0xB7,0xC1,0xAF,0x54,0xFB,0x02,0xE0,0x35,0xBB,0x3A,0x4D,0xAD,0x2C,0x3D,0x56,0x08,0x1B,0x4A,0x93,0x6A,0xAB,0xB8,0x7A,0xF2,0x7D,0xDA,0x3F,0xFE,0x3E,0xBE,0xEA,0xAA,0x44,0xC6,0xD0,0x36,0x48,0x70,0x96,0x77,0x24,0x53,0xDF,0xF3,0x83,0x28,0x32,0x45,0x1E,0xA4,0xD3,0xA2,0x46,0x6E,0x9C,0xDD,0x63,0xD4,0x9D];
    I._Sbox[4]  = I._Sbox[0];
    I._Sbox[5]  = I._Sbox[1];
    I._Sbox[6]  = I._Sbox[2];
    I._Sbox[7]  = I._Sbox[3];
    I.v  = [0x01,0x01,0x05,0x01,0x08,0x06,0x07,0x04];
    I._v = [0xAD,0x95,0x76,0xA8,0x2F,0x49,0xD7,0xCA]; 
	I.shift = [];for(i=0;i<8;i++)I.shift[i] = parseInt(i*b/512);
	I.G = [];for(j=0;j<I.c;j++)I.G[j] = [0,0,0,0,0,0,0,0];	
    // I.G=[[0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17],[0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F]];
    I.M=function(x,y){if(x==0||y==0)return 0;return I.pw2val[I.pw2ind[x]+I.pw2ind[y]];}
    I.l = (I.k == 2*I.b)?2*I.c:I.c;
    I.K = [];for(j=0;j<I.l;j++)I.K[j] = [0,0,0,0,0,0,0,0];
    I.Kr=[];for(i=0;i<=I.r;i++){I.Kr[i]=[];for(j=0;j<I.c;j++)I.Kr[i][j]=[0,0,0,0,0,0,0,0];}
    
    I.setKeyHex=function(h){
		for(j=0;j<I.l;j++)
			for(i=0;i<8;i++){
				if(h[(j*8+i)*2]!==undefined&&h[(j*8+i)*2+1]!==undefined)
					I.K[j][i] = parseInt(h[(j*8+i)*2]+''+h[(j*8+i)*2+1],16);
				else
					throw "Invalid key hexadecimal format";
			}
        I.expandKey();
	}
    I.toString=function(k=I.G){t="";for(j=0;j<I.c;j++)for(i=0;i<8;i++){if(k[j][i]<16)t+='0';t+=k[j][i].toString(16);} return t;}
    I.keyToString=function(k=I.K){t="";for(j=0;j<I.l;j++)for(i=0;i<8;i++){if(k[j][i]<16)t+='0';t+=k[j][i].toString(16);} return t;}
    
    I.expandKey=function(){
		var i,j,c,acc,Ktmp=[],Ktmp2=[],Ktmp3=[],Ks=[],o=(I.k == 2*I.b)?I.c:0;
		for(j=0;j<I.l;j++){Ktmp[j]=[0,0,0,0,0,0,0,0];Ktmp2[j]=[0,0,0,0,0,0,0,0];Ktmp3[j]=[0,0,0,0,0,0,0,0];Ks[j]=[0,0,0,0,0,0,0,0];}
		Ktmp[0][0] = (I.k+I.b+64)/64;
		for(j=0;j<I.c;j++){
			c=0;
			for(i=0;i<8;i++){
			Ktmp[j][i] = Ktmp[j][i] + I.K[j][i] + c;
				if(Ktmp[j][i] > 0xFF){
					Ktmp[j][i] &= 0xFF;
					c = 1;
				}else c = 0;
				Ktmp[j][i] = I.Sbox[i][Ktmp[j][i]];
				Ktmp2[(j+I.shift[i])&(I.c_1)][i]= Ktmp[j][i];
			}
		}
    //console.log(I.toString(Ktmp));
        for(j=0;j<I.c;j++)
			for(i=0;i<8;i++)
			{
				acc = 0;
				for(k=0;k<8;k++)
					acc ^= I.M(I.v[(k-i+8)&7],Ktmp2[j][k]);
				//(acc & 0xFF) - psi-value. It is possible to apply other transformation in this loop
				
				//xor K_alfa/beta (kappa): (acc & 0xFF) ^ I.K[j+betashift][i]
				//and non-linear mapping (pi): I.Sbox[i]
				Ktmp[j][i] = I.Sbox[i][(acc & 0xFF) ^ I.K[j+o][i]];//+kappa+pi
				
				//permutation (tau).
				Ktmp3[(j+I.shift[i])&(I.c_1)][i]= Ktmp[j][i];//tau
			}
		//second linear transformation (psi) +eta+pi+tau
		for(j=0;j<I.c;j++){
			c=0;
			for(i=0;i<8;i++)
			{
				acc = 0;
				for(k=0;k<8;k++)
					acc ^= I.M(I.v[(k-i+8)&7],Ktmp3[j][k]);
				Ktmp[j][i] = (acc & 0xFF) + I.K[j][i] + c;//+eta
				if(Ktmp[j][i] > 0xFF){
					Ktmp[j][i] &= 0xFF;
					c = 1;
				}else c = 0;				
				Ktmp[j][i] = I.Sbox[i][Ktmp[j][i]];// pi				
				Ktmp2[(j+I.shift[i])&(I.c_1)][i]= Ktmp[j][i];//tau
			}
		}

		//psi - last operation for intermediate key I.Ks		
		for(j=0;j<I.c;j++)
			for(i=0;i<8;i++)
			{
				acc = 0;
				for(k=0;k<8;k++)
					acc ^= I.M(I.v[(k-i+8)&7],Ktmp2[j][k]);
				Ks[j][i] = (acc & 0xFF);
			}
            
        
            
        //round keys
		var shiftedteta = [[],[],[],[],[],[],[],[],[],[]];
        var rotatedkey;
		for(j=0;j<I.c;j++){
			shiftedteta[0][j] = [0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00];
			shiftedteta[1][j] = [0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00];
			shiftedteta[2][j] = [0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00];
			shiftedteta[3][j] = [0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00];
			shiftedteta[4][j] = [0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00];
			shiftedteta[5][j] = [0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00];
			shiftedteta[6][j] = [0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00];
			shiftedteta[7][j] = [0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00];
			shiftedteta[8][j] = [0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01];
			shiftedteta[9][j] = [0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02];
		}
		//Key rotations depend on block size and key size
		if(I.b==128 && I.k==128){
			// for 128-128 mode
			rotatedkey = {0:I.K, 2:{0:I.K[1],1:I.K[0]}};
			for(n=4;n<=I.r;n+=2)
				rotatedkey[n] = rotatedkey[n-4];
		}
        
        
		if(I.b==128 && I.k==256){
			rotatedkey = {0:I.K, 
				2:{0:I.K[2],1:I.K[3],2:I.K[0],3:I.K[1]},
				4:{0:I.K[1],1:I.K[2],2:I.K[3],3:I.K[0]},
				6:{0:I.K[3],1:I.K[0],2:I.K[1],3:I.K[2]},
				8:{0:I.K[2],1:I.K[3],2:I.K[0],3:I.K[1]},
				10:I.K, 
				12:{0:I.K[3],1:I.K[0],2:I.K[1],3:I.K[2]},
                14:{0:I.K[1],1:I.K[2],2:I.K[3],3:I.K[0]}};
			
		}
		if(I.b==256 && I.k==256){
			rotatedkey = {0:I.K, 
				2:{0:I.K[1],1:I.K[2],2:I.K[3],3:I.K[0]},
				4:{0:I.K[2],1:I.K[3],2:I.K[0],3:I.K[1]},
				6:{0:I.K[3],1:I.K[0],2:I.K[1],3:I.K[2]},
				8:I.K, 
				10:{0:I.K[1],1:I.K[2],2:I.K[3],3:I.K[0]},
				12:{0:I.K[2],1:I.K[3],2:I.K[0],3:I.K[1]},
                14:{0:I.K[3],1:I.K[0],2:I.K[1],3:I.K[2]}};
			
		}
        if(I.b==256 && I.k==512){
			rotatedkey = {0:I.K,
                2:  {0:I.K[4],1:I.K[5],2:I.K[6],3:I.K[7],4:I.K[0],5:I.K[1],6:I.K[2],7:I.K[3]}, 
				4:  {0:I.K[1],1:I.K[2],2:I.K[3],3:I.K[4],4:I.K[5],5:I.K[6],6:I.K[7],7:I.K[0]},
				6:  {0:I.K[5],1:I.K[6],2:I.K[7],3:I.K[0],4:I.K[1],5:I.K[2],6:I.K[3],7:I.K[4]},
				8:  {0:I.K[2],1:I.K[3],2:I.K[4],3:I.K[5],4:I.K[6],5:I.K[7],6:I.K[0],7:I.K[1]},
				10: {0:I.K[6],1:I.K[7],2:I.K[0],3:I.K[1],4:I.K[2],5:I.K[3],6:I.K[4],7:I.K[5]},
				12: {0:I.K[3],1:I.K[4],2:I.K[5],3:I.K[6],4:I.K[7],5:I.K[0],6:I.K[1],7:I.K[2]},
				14: {0:I.K[7],1:I.K[0],2:I.K[1],3:I.K[2],4:I.K[3],5:I.K[4],6:I.K[5],7:I.K[6]},
                16: {0:I.K[4],1:I.K[5],2:I.K[6],3:I.K[7],4:I.K[0],5:I.K[1],6:I.K[2],7:I.K[3]}, 
                18: I.K};
        }
		if(I.b==512 && I.k==512){
			rotatedkey = {0:I.K,
                2: {0:I.K[1],1:I.K[2],2:I.K[3],3:I.K[4],4:I.K[5],5:I.K[6],6:I.K[7],7:I.K[0]},
				4: {0:I.K[2],1:I.K[3],2:I.K[4],3:I.K[5],4:I.K[6],5:I.K[7],6:I.K[0],7:I.K[1]},
				6: {0:I.K[3],1:I.K[4],2:I.K[5],3:I.K[6],4:I.K[7],5:I.K[0],6:I.K[1],7:I.K[2]},
				8: {0:I.K[4],1:I.K[5],2:I.K[6],3:I.K[7],4:I.K[0],5:I.K[1],6:I.K[2],7:I.K[3]}, 
				10:{0:I.K[5],1:I.K[6],2:I.K[7],3:I.K[0],4:I.K[1],5:I.K[2],6:I.K[3],7:I.K[4]},
				12:{0:I.K[6],1:I.K[7],2:I.K[0],3:I.K[1],4:I.K[2],5:I.K[3],6:I.K[4],7:I.K[5]},
				14:{0:I.K[7],1:I.K[0],2:I.K[1],3:I.K[2],4:I.K[3],5:I.K[4],6:I.K[5],7:I.K[6]},
                16:I.K,
                18: {0:I.K[1],1:I.K[2],2:I.K[3],3:I.K[4],4:I.K[5],5:I.K[6],6:I.K[7],7:I.K[0]}};
        }
    // console.log(rotatedkey);return;
    //console.log(I.keyToString(rotatedkey[4])) ;return;   
		var n,Kr_tmp, oddshift = (I.b/4+24)/8;

		for(n=0;n<=I.r;n+=2)
		{
			//fi(Ksigma)
			Kr_tmp = [];
			for(j=0;j<I.c;j++){
				c=0;Kr_tmp[j]=[];
				for(i=0;i<8;i++){
					Kr_tmp[j][i] = shiftedteta[n/2][j][i] + Ks[j][i] + c;//fi
					if(Kr_tmp[j][i] > 0xFF){
						Kr_tmp[j][i] &= 0xFF;
						c = 1;
					}else c = 0;
				}
			}
        
			// tau-pi-eta
			for(j=0;j<I.c;j++){
				c=0;
				for(i=0;i<8;i++){
					Ktmp[j][i] = Kr_tmp[j][i] + rotatedkey[n][j][i] + c;//eta
					if(Ktmp[j][i] > 0xFF){
						Ktmp[j][i] &= 0xFF;
						c = 1;
					}else c = 0;
					Ktmp[j][i] = I.Sbox[i][Ktmp[j][i]];// pi
					Ktmp2[(j+I.shift[i])&(I.c_1)][i]= Ktmp[j][i];//tau
				}
			}
            
			// tau-pi-kappa-fi-psi
			for(j=0;j<I.c;j++)
				for(i=0;i<8;i++)
				{
					acc = 0;
					for(k=0;k<8;k++)
						acc ^= I.M(I.v[(k-i+8)&7],Ktmp2[j][k]);
					Ktmp[j][i] = I.Sbox[i][(acc & 0xFF)^Kr_tmp[j][i]];//+kappa-fi+pi
					Ktmp3[(j+I.shift[i])&(I.c_1)][i]= Ktmp[j][i];//tau
				}
                
			//eta-psi 
			for(j=0;j<I.c;j++){
				c=0;
				for(i=0;i<8;i++)
				{
					acc = 0;
					for(k=0;k<8;k++)
						acc ^= I.M(I.v[(k-i+8)&7],Ktmp3[j][k]);

					Ktmp[j][i] = (acc & 0xFF) + Kr_tmp[j][i] + c;//+eta
					if(Ktmp[j][i] > 0xFF){
						Ktmp[j][i] &= 0xFF;
						c = 1;
					}else c = 0;
				}
			}
            
            for(j=0;j<I.c;j++)for(i=0;i<8;i++)I.Kr[n][j][i] = Ktmp[j][i];
			if(n<I.r){
				for(j=0;j<I.c;j++)
					for(i=0;i<8;i++){
						I.Kr[n+1][j][i] = I.Kr[n][(j+parseInt((i+oddshift)/8))&I.c_1][(i+oddshift)&7];
					}
			}
		}
    }
    I.showRoundKeys=function(){for(var n=0;n<=I.r;n++) console.log(n+': '+I.toString(I.Kr[n]));}
    
    
    
    I.encrypt=function(){//transform state matrix prepared by other functions
		var c,i,j,Gtmp = [];
		for(j=0;j<I.c;j++){
			Gtmp[j] = [];
			c=0;
			for(i=0;i<8;i++){
				I.G[j][i] = I.G[j][i] + I.Kr[0][j][i] + c;//eta
				if(I.G[j][i] > 0xFF){
					I.G[j][i] &= 0xFF;
					c = 1;
				}else c = 0;
				Gtmp[j][i] = 0;
			}
		}
		for(round = 1;round < I.r; round++)
		{
			//pi+tau
			for(j=0;j<I.c;j++)
				for(i=0;i<8;i++){
					I.G[j][i] = I.Sbox[i][I.G[j][i]];
					Gtmp[(j+I.shift[i])&(I.c_1)][i]= I.G[j][i];
				}
			//psi+kappa
			for(j=0;j<I.c;j++)
				for(i=0;i<8;i++)
				{
					acc = 0;
					for(k=0;k<8;k++)
						acc ^= I.M(I.v[(k-i+8)&7],Gtmp[j][k]);
					I.G[j][i] = (acc & 0xFF)^(I.Kr[round][j][i]);
				}
		}
		//pi+tau
		for(j=0;j<I.c;j++)
			for(i=0;i<8;i++){
				I.G[j][i] = I.Sbox[i][I.G[j][i]];
				Gtmp[(j+I.shift[i])&(I.c_1)][i]= I.G[j][i];
			}
		//psi+eta
		for(j=0;j<I.c;j++){
			c=0;
			for(i=0;i<8;i++)
			{
				acc = 0;
				for(k=0;k<8;k++)
					acc ^= I.M(I.v[(k-i+8)&7],Gtmp[j][k]);

				I.G[j][i] = (acc & 0xFF) + I.Kr[round][j][i] + c;
				if(I.G[j][i] > 0xFF){
					I.G[j][i] &= 0xFF;
					c = 1;
				}else c = 0;
			}
		}
	}
    
    I.encryptHex=function(s){
        var i,j;
        for(j=0;j<I.c;j++)
			for(i=0;i<8;i++)
				if(s[(j*8+i)*2]!==undefined&&s[(j*8+i)*2+1]!==undefined)
					I.G[j][i] = parseInt(s[(j*8+i)*2]+''+s[(j*8+i)*2+1],16);
				else
					throw "Invalid data hexadecimal string format";
		I.encrypt();	
		return I.toString();
    }
    
    function decrypt(){//transform state matrix
		var c,i,j,Gtmp = [],round = I.r;
		for(j=0;j<I.c;j++){
			Gtmp[j] = [];
			c=0;
			for(i=0;i<8;i++){
				I.G[j][i] = I.G[j][i] - I.Kr[round][j][i] - c;
				if(I.G[j][i] < 0){
					I.G[j][i] = (I.G[j][i]+0x100) & 0xFF;
					c = 1;
				}else c = 0;
				Gtmp[j][i] = 0;
			}
		}
		for(j=0;j<I.c;j++)
			for(i=0;i<8;i++){
				acc = 0;
				for(k=0;k<8;k++)
					acc ^= I.M(I._v[(k-i+8)&7],I.G[j][k]);
				Gtmp[(j-I.shift[i]+I.c)&(I.c_1)][i] = I._Sbox[i][(acc & 0xFF)];
			}
			
		for(round = I.r-1;round>0;round--)
		{
			for(j=0;j<I.c;j++)
				for(i=0;i<8;i++){
					I.G[j][i] = Gtmp[j][i] ^ (I.Kr[round][j][i]);
				}
			for(j=0;j<I.c;j++)
				for(i=0;i<8;i++){
					acc = 0;
					for(k=0;k<8;k++)
						acc ^= I.M(I._v[(k-i+8)&7],I.G[j][k]);
					Gtmp[(j-I.shift[i]+I.c)&(I.c_1)][i] = I._Sbox[i][(acc & 0xFF)];
				}
		}
		for(j=0;j<I.c;j++){
			c=0;
			for(i=0;i<8;i++){
				I.G[j][i] = Gtmp[j][i] - I.Kr[round][j][i] - c;
				if(I.G[j][i] < 0){
					I.G[j][i] = (I.G[j][i]+0x100) & 0xFF;
					c = 1;
				}else c = 0;
			}
		}
	}
    
    I.decryptHex=function(s){
        //console.log('s: '+s);
        var i,j;
        for(j=0;j<I.c;j++)
			for(i=0;i<8;i++)
				if(s[(j*8+i)*2]!==undefined&&s[(j*8+i)*2+1]!==undefined)
					I.G[j][i] = parseInt(s[(j*8+i)*2]+''+s[(j*8+i)*2+1],16);
				else
					throw "Invalid data hexadecimal string format";
		decrypt();	
		return I.toString();
    }
}