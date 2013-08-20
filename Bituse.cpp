#include "Bituse.h"

//低8位和高8位用到的数组
unsigned char D_G1[64][256] = {0};
unsigned char D_G2[16][256] = {0};
unsigned char D_G3[4][256] = {0};

//中8位用到的数组
unsigned char Z1[128][256] = {0};
unsigned char Z2[32][256] = {0};
unsigned char Z3[8][256] = {0};
unsigned char Z4[2][256] = {0};

bool initarr = true;

void InitArray()
{
	for (int i = 0; i < 64; i ++)
	{
		for (int j = 0; j < 4; j ++)
		{
			D_G1[i][j*64] = (i << 2) + j;
		}
	}

	for (int i = 0; i < 16; i ++)
	{
		for (int j = 0; j < 16; j ++)
		{
			D_G2[i][j*16] = (i << 4) + j;
		}
	}

	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 64; j ++)
		{
			D_G3[i][j*4] = (i << 6) + j;
		}
	}

	for (int i = 0; i < 128; i ++)
	{
		for (int j = 0; j < 2; j ++)
		{
			Z1[i][j*128] = (i << 1) + j;
		}
	}

	for (int i = 0; i < 32; i ++)
	{
		for (int j = 0; j < 8; j ++)
		{
			Z2[i][j*32] = (i << 3) + j;
		}
	}

	for (int i = 0; i < 8; i ++)
	{
		for (int j = 0; j < 32; j ++)
		{
			Z3[i][j*8] = (i << 5) + j;
		}
	}

	for (int i = 0; i < 2; i ++)
	{
		for (int j = 0; j < 128; j ++)
		{
			Z4[i][j*2] = (i << 7) + j;
		}
	}
}

void TurnRighttoLift(unsigned char *src, unsigned char *dest, int wid, int high)
{
	unsigned long long *src_l = (unsigned long long *)src;
	unsigned long long *dest_l = (unsigned long long *)dest;
	unsigned long long x;
	int wid_l = wid/8;
	for (int i = 0; i < high; i ++)
	{
		for (int j = 0; j < wid_l; j ++)
		{
			x = *(src_l++);
			x = ((x<<8)&0xFF00FF00FF00FF00) | ((x>>8)&0x00FF00FF00FF00FF);
			x = ((x<<16)&0xFFFF0000FFFF0000) | ((x>>16)&0x0000FFFF0000FFFF);
			*(dest_l + wid_l*i + wid_l - 1 - j) = (x>>32) | (x<<32);
		}
	}
}

int getbitnumofone(long long nValue)
{
	nValue = ((0xaaaaaaaaaaaaaaaa & nValue)>>1) + (0x5555555555555555 & nValue);
	nValue = ((0xcccccccccccccccc & nValue)>>2) + (0x3333333333333333 & nValue);
	nValue = ((0xf0f0f0f0f0f0f0f0 & nValue)>>4) + (0x0f0f0f0f0f0f0f0f & nValue);
	nValue = ((0xff00ff00ff00ff00 & nValue)>>8) + (0x00ff00ff00ff00ff & nValue);
	nValue = ((0xffff0000ffff0000 & nValue)>>16) + (0x0000ffff0000ffff & nValue);
	nValue = ((0xffffffff00000000 & nValue)>>32) + (0x00000000ffffffff & nValue);	
	return (int)nValue;
}

int NewGet8BitOf10(unsigned char * buf, int nBufLen,unsigned char * Outbuf, int nOutBufLen, int Mode)
{
	if (buf == NULL || Outbuf == NULL)
		return -1;
	if (initarr)
	{
		InitArray();
		initarr = false;
	}
	int x,y;

	if (Mode == 3)
	{
		for (int i = 0; i < nBufLen/5; i ++)
		{
			int k = i*5;
			int k2 = i*4;
			x = buf[k] & 0x3f;
			y = buf[k+1] & 0xc0;
			Outbuf[k2] = D_G1[x][y];
			x = buf[k+1] & 0x0f;
			y = buf[k+2] & 0xf0;
			Outbuf[k2+1] = D_G2[x][y];
			x = buf[k+2] & 0x03;
			y = buf[k+3] & 0xfc;
			Outbuf[k2+2] = D_G3[x][y];
			Outbuf[k2+3] = buf[k+4];
		}
	}
	else if (Mode == 2)
	{
		for (int i = 0; i < nBufLen/5; i ++)
		{
			int k = i*5;
			int k2 = i*4;
			x = buf[k] & 0x7f;
			y = buf[k+1] & 0x80;
			Outbuf[k2] = Z1[x][y];
			x = buf[k+1] & 0x1f;
			y = buf[k+2] & 0xe0;
			Outbuf[k2+1] = Z2[x][y];
			x = buf[k+2] & 0x07;
			y = buf[k+3] & 0xf8;
			Outbuf[k2+2] = Z3[x][y];
			x = buf[k+3] & 0x01;
			y = buf[k+4] & 0xfe;
			Outbuf[k2+3] = Z4[x][y];
		}
	}
	else if (Mode == 1)
	{
		for (int i = 0; i < nBufLen/5; i ++)
		{
			int k = i*5;
			int k2 = i*4;
			Outbuf[k2] = buf[k];
			x = buf[k+1] & 0x3f;
			y = buf[k+2] & 0xc0;
			Outbuf[k2+1] = D_G1[x][y];
			x = buf[k+2] & 0x0f;
			y = buf[k+3] & 0xf0;
			Outbuf[k2+2] = D_G2[x][y];
			x = buf[k+3] & 0x03;
			y = buf[k+4] & 0xfc;
			Outbuf[k2+3] = D_G3[x][y];
		}
	}

	return 0;
}

unsigned int * _sort(unsigned int *a)
{
	unsigned int *p = (unsigned int *)malloc(MaxNum/8);
	memset(p,0,MaxNum/8);
	for (int i = 0; i < Number; i ++)
	{
		unsigned int k = (0x80000000 >> (a[i]%32));
		p[a[i]/32] |= k;
	}
	return p;
}