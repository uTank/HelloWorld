
enum STATE_NUMBER{
	STATE_INIT = 0,
	STATE_1,
	STATE_2,
	STATE_3,
	STATE_4,
	STATE_EXIT
};

int iStateFunInit(int *state)
{
	return STATE_NUMBER;
}
int iStateFun1(int *state)
{
	return STATE_NUMBER;
}
int iStateFun2(int *state)
{
	return STATE_NUMBER;
}
int iStateFun3(int *state)
{
	return STATE_NUMBER;
}
int iStateFun4(int *state)
{
	return STATE_NUMBER;
}
int iStateFunExit(int *state)
{
	return STATE_NUMBER;
}

typedef struct st_state_table{
	int iStateNumber;
	int (*pFunction)(int *);
}ST_STATE_TAB;

int iStateMain(void)
{
	ST_STATE_TAB tStateTab[] = {
		{STATE_INIT, iStateFunInit},
		{STATE_1, iStateFun1},
		{STATE_2, iStateFun2},
		{STATE_3, iStateFun3},
		{STATE_4, iStateFun4},
		{STATE_EXIT, iStateFunExit},
		{-1, 0}
	};
	ST_STATE_TAB *p;
	int iStateNumber;
	int iResult = -1;

	iStateNumber = STATE_INIT;

	while(iStateNumber != STATE_EXIT)
	{
		for(p = (ST_STATE_TAB *)tStateTab; p->pFunction != 0; p++)
		{
			if(iStateNumber == p->iStateNume)
			{
				iStateNumber = (*p->pFunction)(&iResult);
				break;
			}
		}
		if(p->iStateNumber == -1 || p->pFunction == NULL)
		{
			iStateNumber = STATE_EXIT;
		}
	}

	return iResult;
}

/* */

enum TradeState{
	eTradeWaitAmount = 0x00,
	eTradeDoing,
	eTradeWaitPrint,
	eTradeExit
};

int iTradeDone(int *state)
{
	int *p = state;
	switch(*p)
	{
		case eTradeWaitAmount:
			/* 接收数据包 */
			break;
		case eTradeDoing:
			/* 检测卡 */
			break;
		case eTradeWaitPrint:
			/* 接收数据包 */
			break;
		case eTradeExit:
			/* */
			break;
	}
}

