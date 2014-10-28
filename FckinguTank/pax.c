
typedef enum st_bt_pci_test_step{
	step_bt_open = 0,
	step_bt_set_pair,
	step_bt_set_ssp,
	step_bt_wait_spp,
	step_bt_wait_yes_no,
	step_bt_wait_key,
	step_bt_data_rx,
	step_bt_data_tx,
	step_bt_close,
	step_bt_re_select,
	step_bt_exit,
	step_bt_err,
}BT_STEP_t;

void BtPciTestStepPrompt(int step)
{
	int i;
	struct step_prompt{
		int step;
		char prompt[32];
	};
	struct step_prompt prompt[] = {
		step_bt_open, "Bt Open...",
		step_bt_set_ssp, "Bt Set SSP...",
		step_bt_wait_spp, "Bt Waiting SPP..",
		step_bt_data_rx, "Bt Rx Data...",
		step_bt_data_tx, "Bt Tx Data...",
		step_bt_close, "Bt Close...",
		step_bt_exit, "Bt Exit...",
		step_bt_err, "Bt Error...",
	};
	ScrCls();
	for(i = 0; i < sizeof(prompt)/sizeof(prompt[0]); i++)
	{
		if(step == prompt[i].step)
		{
			ScrPrint(0, 3, 0x00, "%s", prompt[i].prompt);
		}
	}
}

typedef struct st_bt_pci_test_opt{
	int last_step;
	int key_response;
	int yes_no_value;
	unsigned char data_rx;
}ST_BT_TEST_OPT;

/* return next step */
BT_STEP_t BtPciTestStepOpen(ST_BT_TEST_OPT *opt)
{
	int iRet;

	opt->last_step= step_bt_open;
	
	iRet = BtOpen();
	if(iRet != 0)
		return step_bt_close;
	iRet = PortOpen(7, "115200,8,n,1");
	if(iRet != 0)
		return step_bt_close;

	return step_bt_set_pair;
}

BT_STEP_t BtPciTestStepSetPair(ST_BT_TEST_OPT *opt)
{
	int iRet;
	static int iCnt = 0;
	unsigned int pArgIn = 2;
	
	if(opt->last_step == step_bt_set_pair && iCnt++ >= 3)
	{
		iCnt = 0;
		return step_bt_close;
	}
	
	opt->last_step = step_bt_set_pair;
	iRet = BtCtrl(2, (unsigned int *)&pArgIn, 1, 0, 0);
	if(iRet != 0)
	{
		return step_bt_set_pair;
	}
	iCnt = 0;
	
	return step_bt_set_ssp;

}

BT_STEP_t BtPciTestStepSetSSP(ST_BT_TEST_OPT *opt)
{
	int iRet;
	static int iCnt = 0;
	unsigned int pArgIn = 1;

	if(opt->last_step == step_bt_set_ssp && iCnt++ >= 3)
	{
		iCnt = 0;
		return step_bt_close;
	}
	
	opt->last_step = step_bt_set_ssp;
	iRet = BtCtrl(4, (unsigned int *)&pArgIn, 1, 0, 0);
	if(iRet != 0)
	{
		return step_bt_set_ssp;
	}
	iCnt = 0;
	
	return step_bt_wait_spp;
}

BT_STEP_t BtPciTestStepWaitSPP(ST_BT_TEST_OPT *opt)
{
	int iRet;
	int pArgOut[2];
	ST_BT_STATUS tBtStatus;

	opt->last_step = step_bt_wait_spp;
	iRet = BtGetStatus(&tBtStatus);
	if(iRet != 0) /* unlikely */
	{
		return step_bt_close;
	}
	
	if(kbhit() == 0x00 && getkey() == KEYCANCEL)
		return step_bt_close;
	
	if(tBtStatus.status == 0)
	{
		iRet = BtCtrl(7, 0, 0, pArgOut, 2);
		if(pArgOut[0] == 0)
		{
			return step_bt_wait_spp;
		}
		else if (pArgOut[0] == 1)
		{
			opt->yes_no_value = pArgOut[1];
			return step_bt_wait_yes_no;
		}
		else /* pArgOut[0] == 2 */
		{
			return step_bt_wait_key;
		}
	}
	else
	{
		return step_bt_data_rx;
	}
}
BT_STEP_t BtPciTestStepWaitYesNo(ST_BT_TEST_OPT *opt)
{
	int iRet;
	unsigned int pIn[10];
	unsigned char ucKey;
	unsigned char str_key[10];
	unsigned int passkey;
	
	ScrCls();
	ScrPrint(0, 0, 0x00, "KeyInfo: %06u", opt->yes_no_value);
	ScrPrint(0, 1, 0x00, "Response Yes/NO");
	ScrPrint(0, 2, 0x00, "1. Yes");
	ScrPrint(0, 3, 0x00, "0. No");
	while(1)
	{
		ucKey = getkey();
		if(ucKey == KEYCANCEL)
			return step_bt_wait_spp;
		if(ucKey == KEY1 || ucKey == KEY0)
			break;
	}
	pIn[0] = ucKey - KEY0;
	iRet = BtCtrl(5, pIn, 1, 0, 0);

	return step_bt_wait_spp;
}

BT_STEP_t BtPciTestStepWaitKeyResponse(ST_BT_TEST_OPT *opt)
{
	int iRet;
	unsigned int pIn[10];
	unsigned char ucKey;
	unsigned char str_key[10];
	unsigned int passkey;
	
	ScrCls();
	ScrPrint(0, 0, 0x00, "Response Passkey");
	ScrGotoxy(0, 1);
	memset(str_key, 0x00, sizeof(str_key));
	iRet = GetString(str_key, 0x25, 6, 6);
	if(iRet != 0)
	{
		return step_bt_wait_spp;
	}
	passkey = atoi(str_key+1);
	ScrCls();
	iRet = BtCtrl(6, (unsigned int *)&passkey, 1, 0, 0);
	
	return step_bt_wait_spp;		
}

BT_STEP_t BtPciTestStepDataRx(ST_BT_TEST_OPT *opt)
{
	unsigned char ucRet;
	unsigned char ch;
	int iRet;
	ST_BT_STATUS tBtStatus;
	
	iRet = BtGetStatus(&tBtStatus);
	if(iRet != 0) /* unlikely */
	{
		return step_bt_close;
	}
	if(kbhit() == 0x00 && getkey() == KEYCANCEL)
		return step_bt_close;

	if(tBtStatus.status == 0) /* spp disconnect */
	{
		return step_bt_wait_spp;
	}
	else
	{
		iRet = PortRecv(7, &ch, 0);
		if(iRet == 0)
		{
			ScrPrint(0, 6, 0x00, "Rx:%d, %x", iRet, ch);
			opt->data_rx = ch;
			return step_bt_data_tx;
		}
		else
		{
			return step_bt_data_rx;
		}
	}
}
BT_STEP_t BtPciTestStepDataTx(ST_BT_TEST_OPT *opt)
{
	int iRet;
	unsigned char ucRet;
	ST_BT_STATUS tBtStatus;
	unsigned char ch;
	
	iRet = BtGetStatus(&tBtStatus);
	if(iRet != 0) /* unlikely */
	{
		return step_bt_close;
	}

	if(kbhit() == 0x00 && getkey() == KEYCANCEL)
		return step_bt_close;
	
	if(tBtStatus.status == 0)
	{
		return step_bt_wait_spp;
	}
	else
	{
		ucRet = PortSend(7, opt->data_rx);
		if(ucRet != 0)
		{
			return step_bt_close;
		}
		return step_bt_data_rx;
	}
}

BT_STEP_t BtPciTestStepClose(ST_BT_TEST_OPT *opt)
{
	int iRet;

	opt->last_step= step_bt_close;
	iRet = BtClose();
	if(iRet != 0)
		return step_bt_exit;

	return step_bt_re_select;
}

BT_STEP_t BtPciTestStepReSelect(ST_BT_TEST_OPT *opt)
{
	int iRet;
	unsigned char ucKey;
	
	ScrCls();
	ScrPrint(0, 0, 0x00, "1. re-test");
	ScrPrint(0, 1, 0x00, "2. exit-test");
	BtClose();
	while(1)
	{
		ucKey = getkey();
		if(ucKey == KEYCANCEL)
			return step_bt_exit;
		if(ucKey == KEY1 || ucKey == KEY2)
			break;
	}
	if(ucKey == KEY1)
		return step_bt_open;
	else /* KEY2 */
		return step_bt_exit;

}

void BT_PCI_TEST_0(void)
{
	int i;
	int bt_test_opt_step = step_bt_open;
	ST_BT_TEST_OPT bt_opt;
	
	struct step_opt{
		int step;
		BT_STEP_t (*func)(ST_BT_TEST_OPT *);
 	} bt_step_opt[] = {
		step_bt_open, BtPciTestStepOpen,
		step_bt_set_pair, BtPciTestStepSetPair,
		step_bt_set_ssp, BtPciTestStepSetSSP,
		step_bt_wait_spp, BtPciTestStepWaitSPP,
		step_bt_wait_yes_no, BtPciTestStepWaitYesNo,
		step_bt_wait_key, BtPciTestStepWaitKeyResponse,
		step_bt_data_rx, BtPciTestStepDataRx,
		step_bt_data_tx, BtPciTestStepDataTx,
		step_bt_close, BtPciTestStepClose,
		step_bt_re_select, BtPciTestStepReSelect,
		step_bt_exit, NULL,
		//step_bt_err, NULL,
	};
	PortOpen(0, "115200,8,n,1");
	
	memset(&bt_opt, 0x00, sizeof(bt_opt));
	while(1)
	{
		if(bt_test_opt_step == step_bt_exit)
			return ;
		
		for(i = 0; i < sizeof(bt_step_opt)/sizeof(bt_step_opt[0]); i++)
		{
			if(bt_test_opt_step == bt_step_opt[i].step)
			{
				if(bt_step_opt[i].func != NULL)
				{
					BtPciTestStepPrompt(bt_step_opt[i].step);
					bt_test_opt_step = bt_step_opt[i].func(&bt_opt);
				}
				break;
			}
		}
		if(i >= sizeof(bt_step_opt)/sizeof(bt_step_opt[0]))
		{
			ScrCls();
			ScrPrint(0, 3, 0x00, "unkonwn err");
			getkey();
			return ;
		}
	}
}


