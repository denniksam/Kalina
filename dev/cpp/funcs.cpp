/*

int expand_128_128(const byte *rawKey, byte *expandedKey){
	const byte C = 2, R=10;
	const byte shift[] = {0,0,0,0,1,1,1,1};
	byte k1[] = {5,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k2[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k3[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k4[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k5[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
	byte carry_over,i,j,k,acc;	 
	unsigned int s,n,I,J;
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
			k2[((j+shift[i])&1)*ROWLENGTH+i]= k1[k];
		}
	}
	for(j=0;j<C;j++)
	for(i=0;i<ROWLENGTH;i++){
		acc = 0;
		for(k=0;k<ROWLENGTH;k++)
			acc ^= GFmul(v[(k-i+ROWLENGTH)&7],k2[j*ROWLENGTH+k]);
		k1[j*ROWLENGTH+i] = Sbox[i&3][acc ^ rawKey[j*ROWLENGTH+i]];
		k3[((j+shift[i])&1)*ROWLENGTH+i]= k1[j*ROWLENGTH+i];
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
			k2[((j+shift[i])&1)*ROWLENGTH+i]= k1[j*ROWLENGTH+i];
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
			carry_over=0;
			for(i=0;i<ROWLENGTH;i++){
				k = j*ROWLENGTH+i;
				s = (unsigned int)carry_over + (rawKey[((j+((n&2)?1:0))&1)*ROWLENGTH+i]) + k5[k];
				if(s > 0xFF){
					s &= 0xFF;
					carry_over = 1;
				}else carry_over = 0;
				k1[k] = Sbox[i&3][s];// pi
				k2[((j+shift[i])&1)*ROWLENGTH+i]= k1[k];//tau
			}
		}
		for(j=0;j<C;j++)
		for(i=0;i<ROWLENGTH;i++){
			acc = 0;
			for(k=0;k<8;k++)
				acc ^= GFmul(v[(k-i+ROWLENGTH)&7],k2[j*ROWLENGTH+k]);
			k1[j*ROWLENGTH+i] = Sbox[i&3][acc ^ k5[j*ROWLENGTH+i]];
			k3[((j+shift[i])&1)*ROWLENGTH+i]= k1[j*ROWLENGTH+i];
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
				I = (i+7)&7;
				J = ((j+(i+7)/ROWLENGTH)&1);
				expandedKey[(n+1)*C*ROWLENGTH + j*ROWLENGTH + i] = 
					expandedKey[n*C*ROWLENGTH + J*ROWLENGTH + I];
			}
		}
	}
	return 0;
}

int expand_256_256(const byte *rawKey, byte *expandedKey){
	const byte C = 4, R=14;
	const byte shift[] = {0,0,1,1,2,2,3,3};
	byte k1[] = {9,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k2[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k3[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k4[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k5[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
	byte carry_over,i,j,k,acc;	 
	unsigned int s,n,I,J;
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
			k2[((j+shift[i])&3)*ROWLENGTH+i]= k1[k];
		}
	}
	for(j=0;j<C;j++)
	for(i=0;i<ROWLENGTH;i++){
		acc = 0;
		for(k=0;k<ROWLENGTH;k++)
			acc ^= GFmul(v[(k-i+ROWLENGTH)&7],k2[j*ROWLENGTH+k]);
		k1[j*ROWLENGTH+i] = Sbox[i&3][acc ^ rawKey[j*ROWLENGTH+i]];
		k3[((j+shift[i])&3)*ROWLENGTH+i]= k1[j*ROWLENGTH+i];
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
			k2[((j+shift[i])&3)*ROWLENGTH+i]= k1[j*ROWLENGTH+i];
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
			carry_over=0;
			for(i=0;i<ROWLENGTH;i++){
				k = j*ROWLENGTH+i;
				s = (unsigned int)carry_over + (rawKey[((j+(n/2))&3)*ROWLENGTH+i]) + k5[k];
				if(s > 0xFF){
					s &= 0xFF;
					carry_over = 1;
				}else carry_over = 0;
				k1[k] = Sbox[i&3][s];// pi
				k2[((j+shift[i])&3)*ROWLENGTH+i]= k1[k];//tau
			}
		}
		for(j=0;j<C;j++)
		for(i=0;i<ROWLENGTH;i++){
			acc = 0;
			for(k=0;k<8;k++)
				acc ^= GFmul(v[(k-i+ROWLENGTH)&7],k2[j*ROWLENGTH+k]);
			k1[j*ROWLENGTH+i] = Sbox[i&3][acc ^ k5[j*ROWLENGTH+i]];
			k3[((j+shift[i])&3)*ROWLENGTH+i]= k1[j*ROWLENGTH+i];
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
				I = (i+11)&7;
				J = ((j+(i+11)/ROWLENGTH)&3);
				expandedKey[(n+1)*C*ROWLENGTH + j*ROWLENGTH + i] = 
					expandedKey[n*C*ROWLENGTH + J*ROWLENGTH + I];
			}
		}
	}
	
	return 0;
}

int expand_512_512(const byte *rawKey, byte *expandedKey){
	const byte C = 8, R=18, C1=7;
	const byte shift[] = {0,1,2,3,4,5,6,7};
	byte k1[] = {17,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k2[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k3[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k4[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
		 k5[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
	byte carry_over,i,j,k,acc;	 
	unsigned int s,n,I,J;
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
		k1[j*ROWLENGTH+i] = Sbox[i&3][acc ^ rawKey[j*ROWLENGTH+i]];
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
			carry_over=0;
			for(i=0;i<ROWLENGTH;i++){
				k = j*ROWLENGTH+i;
				s = (unsigned int)carry_over + (rawKey[((j+(n/2))&C1)*ROWLENGTH+i]) + k5[k];
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
				I = (i+19)&7;
				J = ((j+(i+19)/ROWLENGTH)&C1);
				expandedKey[(n+1)*C*ROWLENGTH + j*ROWLENGTH + i] = 
					expandedKey[n*C*ROWLENGTH + J*ROWLENGTH + I];
			}
		}
	}
	return 0;
}


int encode_128_128(byte *stateMatrix, const byte *expandedKey){
	const byte C = 2, R=10;
	const byte shift[] = {0,0,0,0,1,1,1,1};
	byte i,j,k,acc,carry_over;
	unsigned int n,s;
	byte tmp[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
	
	for(j=0;j<C;j++){
		carry_over=0;
		for(i=0;i<ROWLENGTH;i++){
			k = j*ROWLENGTH+i;
			s = stateMatrix[k] + expandedKey[k] + carry_over;//eta
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
			tmp[((j+shift[i])&1)*ROWLENGTH+i]= stateMatrix[k];
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
		tmp[((j+shift[i])&1)*ROWLENGTH+i]= stateMatrix[k];
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
	return 0;
}

int encode_256_256(byte *stateMatrix, const byte *expandedKey){
	const byte C = 4, R=14, C1=3;
	const byte shift[] = {0,0,1,1,2,2,3,3};
	byte i,j,k,acc,carry_over;
	unsigned int n,s;
	byte tmp[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
	
	for(j=0;j<C;j++){
		carry_over=0;
		for(i=0;i<ROWLENGTH;i++){
			k = j*ROWLENGTH+i;
			s = stateMatrix[k] + expandedKey[k] + carry_over;//eta
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
	return 0;
}

int decode_256_256(byte *stateMatrix, const byte *expandedKey){
	const byte C = 4, R=14, C1=3;
	const byte shift[] = {0,0,1,1,2,2,3,3};
	byte i,j,k,acc,carry_over;
	int n,s;
	byte tmp[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
	
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
	return 0;
}


int decode_128_128(byte *stateMatrix, const byte *expandedKey){
	const byte C = 2, R=10, C1=1;
	const byte shift[] = {0,0,0,0,1,1,1,1};
	byte i,j,k,acc,carry_over;
	int n,s;
	byte tmp[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
	
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
	return 0;
}



byte C=2,C1=1;	 
	for(byte n=0;n<=14;n+=2){
		printf("%d ",n);
		for(byte i=0;i<8;i++)
			printf("%d ",((n&2)*(C>>1)+n/4+i)&(2*C1+1));
		printf("\n");
	}
*/