
static int giBtTestCurrentStep, giBtTestLastStep;
typedef enum st_bt_pci_test_step{
	step_bt_open = 0,
	step_bt_set_ssp,
	step_bt_wait_spp,
	step_bt_data_rx,
	step_bt_data_tx,
	step_bt_close,
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
/* return next step */
BT_STEP_t BtPciTestStepOpen(int *last_step)
{
	int iRet;

	iRet = BtOpen();
	if(iRet != 0)
	{
		*last_step = step_bt_open;
		return step_bt_close;
	}
	last_step = step_bt_open;
	return step_bt_set_ssp;
}
BT_STEP_t BtPciTestStepSetSSP(int *cur, int *last)
{
	int iRet;
	static int iCnt = 0;

	if(*last == step_bt_set_ssp && iCnt++ >= 3)
	{
		*cur = step_bt_close;
		iCnt = 0;
	}
	
	iRet = BtCtrl(4, 2, 1, 0, 0);
	if(iRet != 0)
	{
		*last = step_bt_set_ssp;
		*cur = step_bt_close;
	}
}

BT_STEP_t BtPciTestStepRx(int *cur, int *last)
{
	int iRet;

	iRet = BtGetStatus(&status);
	if(iRet == 0 && status != 1)
	{
		*last = step_bt_data_rx;
		*cur = step_bt_wait_spp;
		return ;
	}
}

BT_STEP_t BtPciTestStepTx(int *cur, int *last)
{
	iRet = BtGetStatus(&status);
	if(iRet == 0 && status != 1)
	{
		*last = step_bt_data_tx;
		*cur = step_bt_wait_spp;
		return ;
	}
	
}

BT_STEP_t BtPciTestStepClose(int *cur, int *last)
{
	int iRet;
	static int iCnt = 0;
	
	if(*last == step_bt_open && iCnt++ >= 3)
	{
		*cur = step_bt_exit;
		iCnt = 0;
		return ;
	}
	if(*last == step_bt_close && iCnt++ >= 3)
	{
		*cur = step_bt_exit;
		iCnt = 0;
		return ;
	}
	
	iRet = BtClose();
	if(iRet != 0)
	{
		*last = step_bt_close;
		*cur = step_bt_close;
		return ;
	}
	iCnt = 0;
}
