#include <stdio.h>
#include "log.h"

#ifdef _UTANK_LOG_

#define LOG_CHARS_PER_LINE   16


void SendLog(char *buf)
{
	printf("%s", buf);
}

void SendLogMem(char *start, void *pMem, int iLen)
{

}

void SendLogHex(char *start, void *pBuf, int iLen)
{
	int i;
	char szBuf[8], iFck[12];
	unsigned char ch;

	printf("%s", start);
	for(i = 0; i < iLen; i++)
	{
		ch = ((unsigned char *)pBuf)[i];
		if(i % LOG_CHARS_PER_LINE == 0)
		{
			snprintf(iFck, sizeof(iFck), "%08x: ", i);
			printf("%s", iFck);
		}
		snprintf(szBuf, sizeof(szBuf), (i+1) % LOG_CHARS_PER_LINE ? "%.2x " : "%.2x\n", ch);
		printf("%s", szBuf);
	}
	if(iLen % LOG_CHARS_PER_LINE)
		printf("\n");
}

#endif


int main(void)
{
	int i;
	int a = 1, b = 2, c = 3;
	char *p = "What Fck";
	char fck[1024];

	for(i = 0; i < sizeof(fck); i++)
		fck[i] = i % 10;

	log("a = %d, b = %d, c = %d\n", a, b, c);
	log("%s\n", p);
	logHex(fck, sizeof(fck)+123, "Fck -> \n");

	return 0;
}

