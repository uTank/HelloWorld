#include <stdio.h>
#include <string.h>

#define PCM_NAME   "/home/utank/pax/pcmmsg.wav"

unsigned char wav_buf[1024*50];
int wav_size;

int main(int argc, char *argv[])
{
	FILE *fd;
	int iRet, iSize, iLen, i, n;
    if(argc == 2)
    {
        printf("wavefile_data [file_name]\n");
        exit(1);
    }
//	fd = fopen(PCM_NAME, "rb+");
    fd = fopen(argv[1], "rb+");
	if(fd == NULL)
	{
		printf(" fopen wav file error\n\n");
		return 0;
	}	
	printf(" fopen fd = %p\n\n", fd);

	iRet = fseek(fd, 0, SEEK_END);   /* �ض�λ��(������/�ļ�)�ϵ��ļ��ڲ�λ��ָ�� */
	printf(" fseek iRet = %d\n\n", iRet);

	iLen = ftell(fd);                /* ���ص�ǰ�ļ�λ�� */
	printf(" ftell iRet = %d\n\n", iLen);

	wav_size = iLen;
	printf(" wav_size = %d\n\n", wav_size);

	iRet = fseek(fd, 0, SEEK_SET);
	printf(" fseek iRet = %d\n\n", iRet);

	iRet = fread(wav_buf, 1, wav_size, fd);	
	printf(" fread iRet = %d\n\n", iRet);

	for(i=0; i<wav_size; i++)
		printf((i+1)%16 ? "0x%02x," : "0x%02x,\n", wav_buf[i]);
	printf(wav_size % 16 ? "\n\n" : "\n");

	fclose(fd);

	return 0;
}

/**
 *  SEEK_SET : �ļ���ͷ
 *  SEEK_CUR : ��ǰλ��
 *  SEEK_END : �ļ���β
**/

