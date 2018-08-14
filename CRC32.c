#include<stdio.h>

unsigned char table[] = {"helloword!"};

typedef struct tag_CRC32_DATA
{
	unsigned int CRC;				
	unsigned int CRC_32_Tbl[256];	//用来保存码表
}CRC32_DATA_t;

unsigned int calc_crc32(void * buffer, unsigned int length)
{
	unsigned int i, j;
	CRC32_DATA_t crc32;		//
	unsigned int CRC32 = 0xffffffff; //设置初始值

	crc32.CRC = 0;

	for( i = 0; i < 256; ++i)//用++i以提高效率
	{
		crc32.CRC = i;
		for( j = 0; j < 8 ; ++j)
		{
			//这个循环实际上就是用"计算法"来求取CRC的校验码
			if(crc32.CRC & 1)
				crc32.CRC = (crc32.CRC >> 1) ^ 0xEDB88320;
			else //0xEDB88320就是CRC-32多项表达式的值
				crc32.CRC >>= 1;
		}
		crc32.CRC_32_Tbl[i] = crc32.CRC;
	}

	CRC32 = 0xffffffff; //设置初始值
    for( i = 0; i < length; ++i)
    {
        CRC32 = crc32.CRC_32_Tbl[(CRC32^((unsigned char*)buffer)[i]) & 0xff] ^ (CRC32>>8);
    }

    //return CRC32;
	return CRC32^0xffffffff;
}

int main()
{
    unsigned int a;
    a = calc_crc32(table,sizeof(table));
    printf("crc32的值 %d",a);
    return 0;
}