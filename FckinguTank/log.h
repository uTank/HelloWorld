#ifndef __U_LOG_H__
#define __U_LOG_H__

#include "base.h"
#include <string.h>

#define _UTANK_LOG_

#ifdef _UTANK_LOG_

void SendLog(char *buf);
void SendLogMem(char *start, void *pMem, int iLen);
void SendLogHex(char *start, void *pBuf, int iLen);

#define log(...) do{\
	char logBufInLog_h[512];\
	snprintf(logBufInLog_h, sizeof(logBufInLog_h), "[%s]<%s><%d> ",\
		__FILE__, __FUNCTION__, __LINE__);\
	snprintf(logBufInLog_h+strlen(logBufInLog_h),\
		sizeof(logBufInLog_h)-strlen(logBufInLog_h), __VA_ARGS__);\
	SendLog(logBufInLog_h);\
}while(0)


#define logMem(pMem, iLen, ...) do{\
	char logMemBufInLog_h[512];\
	snprintf(logMemBufInLog_h, sizeof(logMemBufInLog_h),\
		"[%s]<%s><%d>", __FILE__, __FUNCTION__, __LINE__);\
	snprintf(logMemBufInLog_h+strlen(logMemBufInLog_h),\
		sizeof(logMemBufInLog_h)-strlen(logMemBufInLog_h), __VA_ARGS__);\
	SendLogMem(logMemBufInLog_h, pMem, iLen);\
}while(0)

#define logHex(pMem, iLen, ...) do{\
	char logHexBufInLog_h[512];\
	snprintf(logHexBufInLog_h, sizeof(logHexBufInLog_h), "[%s]<%s><%d>",\
		__FILE__, __FUNCTION__, __LINE__);\
	snprintf(logHexBufInLog_h+strlen(logHexBufInLog_h),\
		sizeof(logHexBufInLog_h)-strlen(logHexBufInLog_h), __VA_ARGS__);\
	SendLogHex(logHexBufInLog_h, pMem, iLen);\
}while(0)


#define dbg(...)  do{\
	char dbgBufInLog_h[512];\
	snprintf(dbgBufInLog_h, sizeof(dbgBufInLog_h), __VA_ARGS__);\
	SendLog(dbgBufInLog_h);\
}while(0)
	
#define dbgMem(pMem, iLen, ...) do{\
	char logMemBufInLog_h[512];\
	snprintf(logMemBufInLog_h, sizeof(logMemBufInLog_h), __VA_ARGS__);\
	SendLogMem(logMemBufInLog_h, pMem, iLen);\
}while(0)
		
#define dbgHex(pMem, iLen, ...) do{\
	char logHexBufInLog_h[512];\
	snprintf(logHexBufInLog_h, sizeof(logHexBufInLog_h), __VA_ARGS__);\
	SendLogHex(logHexBufInLog_h, pMem, iLen);\
}while(0)


#else

#define log(...)
#define logMem(pMem, iLen, ...)
#define	logHex(pMem, iLen, ...)

#define dbg(...)
#define dbgMem(pMem, iLen, ...)
#define	dbgHex(pMem, iLen, ...)

#endif


#endif /* __U_LOG_H__ */
