#include<stdio.h>
bool haveCarry(int sum)
{
	int test1 = 0x00010000;//二进制串0000 0001 0000 0000
	if ((sum & test1) == 0)//无进位
		return false;
	else
		return true;
}
unsigned short Add(unsigned short x, unsigned short y)
{
	int tmpSum1 = 0;
	tmpSum1 = x + y;
	if (haveCarry(tmpSum1))
		return Add((unsigned short)tmpSum1, 1);
	else
		return (unsigned short)tmpSum1;
}

int main()
{
	unsigned short h[14];
	h[0]  = 0x4500; h[1] = 0x001C;//total length
	h[2]  = 0x8308; h[3] = 0x0000;//flag and fragment offset
	h[4]  = 0xFF01; h[5] = 0x0000;//TTL and protocol and jian yan he
	h[6]  = 0xAC10; h[7] = 0x0D74;//source address
	h[8]  = 0xAC10; h[9] = 0x0D6E;//destination address
	h[10] = 0x0800;h[11] = 0x3233;//variable part
	h[12] = 0x6261;h[13] = 0x636B;//data
	int i = 0;
	unsigned short sum = Add(~h[0],~h[1]);
	for (i = 2; i < 14; ++i)
	{
		sum = Add(~h[i],sum);
	}
	printf("h[5] = 0x%x", (unsigned short)sum);
	return 0;
}
