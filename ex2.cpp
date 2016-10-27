#include<stdio.h>
unsigned short Add_Append(unsigned short x, unsigned short y);
int main(int argc, char** argv)
{
	unsigned short h[14];
	h[0]  = 0x4500; h[1] = 0x001C;//version & head length & total length
	h[2]  = 0x8308; h[3] = 0x0000;//flag & fragment offset
	h[4]  = 0xFF01; h[5] = 0x0000;//TTL & protocol & checksum
	h[6] = h[7] = h[8] = h[9] = 0;//source & destination address
	h[10] = 0x0800;h[11] = 0x3233;//variable part
	h[12] = 0x6261;h[13] = 0x636B;//data
	
	unsigned int Src, Des;
	printf("input source address: ");
	scanf("%x",&Src);
	printf("input destination address: ");
	scanf("%x", &Des);
	h[7] = (short)Src;h[6] = Src / 0x10000;
	h[9] = (short)Des;h[8] = Des / 0x10000;

	unsigned short sum=0, i=0;
	for (i = 0; i < 14; ++i)
		sum = Add_Append(~h[i],sum);
	printf("\n\nsource address = %x\n",Src);
	printf("destination address = %x\n",Des);
	printf("checksum = %x\n", (unsigned short)sum);
	printf("---- ip datagram ----\n");
	for (i = 0; i < 14; ++i)
	{
		if (h[i] < 0x10) printf("000");
		else if (h[i] < 0x100) printf("00");
		else if (h[i] < 0x1000)	printf("0");
		printf("%x  ", h[i]);
		if (i % 2) printf("\n");
	}
	printf("---------------------\n");
	return 0;
}
unsigned short Add_Append(unsigned short x, unsigned short y)
{
	int test1 = 0x00010000;//test 17th bit of sum is 1 or 0
	int tmpSum = 0;
	tmpSum = x + y;
	return ((tmpSum & test1) != 0) ? Add_Append((unsigned short)tmpSum, 1) : (unsigned short)tmpSum;
		
}