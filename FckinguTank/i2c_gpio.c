#include "i2c_gpio.h"
//#include "s3c2410.h"

/**
 *  使用GPIO模拟I2C协议的主机端控制
 *  代码是硬件相关的，移植时需要额外的注意等效代码.
**/

void i2c_gap(void)
{
	volatile int j = 0;
	
	for(j = 0; j < 12; j++);
}

void i2c_etu(void)
{
	volatile int j = 0;
	
	for(j = 0; j < 18; j++);
}

/**
 * Simulate i2c-bus protocol.
 * Protocol specify when SCL is HIGH, the SDA generate falling edge.
**/
void i2c_start(void)
{
	/* 
	 * SDA Generate falling edge when SCL is HIGH.
	 */
    I2CSDA_OUT_CFG();
    I2CSCL_OUT_CFG();
    
    I2CSCL_H();
    I2CSDA_H();
    i2c_etu();
    I2CSDA_L();
    i2c_gap();
    I2CSCL_L();
    i2c_gap();
}

/*
 * Simulate i2c-bus protocol.
 * Protocol specify when SCL is HIGH, the SDA generate rising edge.
 */
void i2c_stop(void)
{
	/*OutPut mode*/
    I2CSDA_OUT_CFG();
    
    I2CSDA_L();
    i2c_gap();
	I2CSCL_H();
	i2c_etu();
	I2CSDA_H();
}

/*
 * Simulate i2c-bus protocol.
 * Protocol specify after received the 8th. bit, if the master received right,
 * the master turn SDA to LOW and provide one SCL signal to acknowledge.
 */
void i2c_ack(void)
{
	/*OutPut mode*/
    I2CSDA_OUT_CFG();

    I2CSDA_L();
    i2c_gap();
    I2CSCL_H();
    i2c_etu();
    I2CSCL_L();
    i2c_gap();
}

/*
 * Simulate i2c-bus protocol.
 * Protocol specify after received the 8th. bit, if the master task is over,
 * the master turn SDA to HIGH and provide one SCL signal to ready to generate 
 * stop condition.
 */
void i2c_nack(void)
{
	/*OutPut mode*/
    I2CSDA_OUT_CFG();

	I2CSDA_H();
	i2c_gap();
	I2CSCL_H();
	i2c_etu();
	I2CSCL_L();
	i2c_gap();
}

/*
 * Simulate i2c-bus protocol.
 * Protocol specify after transferred the 8th. bit, the master turn SDA to receiving
 * status and provide one SCL signal to detect slave device acknowledge.
 */
int i2c_cack(void)
{
	int rval = 1;
	
	/*InPut-Mode*/
    I2CSDA_IN_CFG();
    
	i2c_gap();
	I2CSCL_H();
	i2c_gap();
	if(I2CSDA_GET_DATA()==0){
		rval = 0;
	}
	i2c_gap();
	I2CSCL_L();
	i2c_gap();

	return rval;	
}
/*
 * Simulate i2c-bus protocol.
 * Transfer one byte to slave device, the first bit is most significant bit.
 */
int i2c_wbyte(unsigned char byte)
{
	int  n = 7;

	/*OutPut mode*/
    I2CSDA_OUT_CFG();
    
	/*
	 * Transfer 8 bits of data.
	 */  
	for(n = 7; n >= 0; n--){
		if(byte & (1<<n)){
			I2CSDA_H();	
		}
		else{
			I2CSDA_L();
		}
		i2c_gap();
		I2CSCL_H();
		i2c_etu();
		I2CSCL_L();
		i2c_gap();
	}

	return 1;
}
/*
 * Simulate i2c-bus protocol.
 * Receive one byte from slave device, the first bit is most significant bit.
 */
int i2c_rbyte(unsigned char* byte)
{
	int n = 7;
	
	*byte = 0;
	/*InPut mode*/
    I2CSDA_IN_CFG();
    
	for(n = 7; n >= 0; n--){
		I2CSDA_H();
		i2c_gap();
		do{
			I2CSCL_H();
			i2c_gap();
			/*If slave need time to process other task, SCL will be hold LOW by slave.*/
			if(I2CSCLK_CHECK()==0){
				continue;
			}
			else{
				break;	
			}
		}while(1);
		if(I2CSDA_GET_DATA()){
			*byte |= (1<<n);
		}
		i2c_gap();
		I2CSCL_L();
		i2c_gap();
	}

	return 1;
}

/*
 * Definitions of Interface functions.
 */
int i2c_config()
{
	/*
	 * Configurate SDA and SCL ports to OutPut-Mode
	 * prohibit other function.
	 */	
    I2CSCL_OUT_CFG();
    I2CSDA_OUT_CFG();
    
    I2CSCL_H();
    I2CSDA_H();
}

/*
 * Transfer data to slave device with i2c bus.
 * parameters:
 *		slave : slave device address.
 *      data  : datas will be written.
 *      len   : the number of datas will be written.
 * return:
 *      if value is 0, means error happened.
 *      if value is equal to len, means operation is right.
 */
int i2c_write(unsigned char slave, unsigned char* data, int len)
{
	int  i = 0;

	i2c_start();
	i2c_wbyte(slave);
	if(i2c_cack() > 0){
		i2c_stop();
		return 0;
	}
	for(i = 0; i<len ; i++){
		i2c_wbyte(data[i]);
		if(i2c_cack() > 0){
			i2c_stop();
			return 0;
		}
	}
	i2c_stop();
	
	return len;
}

/*
 * Read from slave device data in i2c bus.
 * parameters:
 *		slave : slave device address.
 *      data  : datas will be readed.
 *      len   : the number of datas will be readed.
 * return:
 *      if value is 0, means error happened.
 *      if value is equal to len, means operation is right.
 */
int i2c_read(unsigned char slave, unsigned char* data, int len)
{
	int  i = 0;

	i2c_start();
	i2c_wbyte(slave);
	if(i2c_cack() > 0){
		i2c_stop();
		return 0;
	}
	for(i = 0; i<len ; i++){
		i2c_rbyte((data + i));
		if(i == (len-1)){
			i2c_nack();
		}
		else{
			i2c_ack();
		}	
	}
	i2c_stop();
	
	return len;
}

