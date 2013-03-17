#ifndef _I2C_GPIO_H
#define _I2C_GPIO_H
/**
 * Samsung S3C2410 for T60.
 * GPE[14] - IICSCL ; GPE[15] - IICSDA
**/
#define rGPECON
#define rGPEDAT

#define I2CSDA_DAT           (1<<15)
#define I2CSCL_DAT           (1<<14)

#define I2CSDA_IN_CFG()      {rGPECON &= ~(3<<30);}
#define I2CSDA_OUT_CFG()     {rGPECON &= ~(3<<30); rGPECON |= (1<<30);}
#define I2CSDA_H()           {rGPEDAT  |=  I2CSDA_DAT;}
#define I2CSDA_L()           {rGPEDAT  &= ~I2CSDA_DAT;}

#define I2CSDA_GET_DATA()    (rGPEDAT & I2CSDA_DAT)
#define I2CSCLK_CHECK()      (rGPEDAT & I2CSCL_DAT)

#define I2CSCL_OUT_CFG()     {rGPECON &= ~(3<<28); rGPECON |= (1<<28);}     
#define I2CSCL_H()           {rGPEDAT  |=  I2CSCL_DAT;}
#define I2CSCL_L()           {rGPEDAT  &= ~I2CSCL_DAT;}

/**
 * Define element functions simulating I2C BUS.
 * These functions is local.
**/
static void i2c_start(void);
static void i2c_stop(void);
static void i2c_ack(void);
static void i2c_nack(void);
static int  i2c_cack(void);
static int  i2c_wbyte(unsigned char byte);
static int  i2c_rbyte(unsigned char* byte);
static void i2c_gap(void);
static void i2c_etu(void);

/**
 * External interface on i2c bus protocol.
**/
int    i2c_config(void);
int    i2c_write(unsigned char slave, unsigned char* data, int len);  
int    i2c_read(unsigned char slave, unsigned char* data, int len);


#endif
