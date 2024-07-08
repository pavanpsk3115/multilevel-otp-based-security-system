void i2c_init(void)

{

	PINSEL0|=scl|sda;

	I2SCLL=75;

	I2SCLH=75;

	I2CONSET=1<<i2en;

}

void start(void)

{

	I2CONSET=1<<sta;

	while(((I2CONSET>>si)&1)==0);

	I2CONCLR=1<<sta;

}

void restart(void)

{

	I2CONSET=1<<sta;

	I2CONCLR=1<<si;

	while(((I2CONSET>>si)&1)==0);

	I2CONCLR=1<<sta;

}

void write(u8 slave_add)

{

	I2DAT=slave_add;

	I2CONCLR=1<<si;

	while(((I2CONSET>>si)&1)==0);

}

u8 nack(void)

{

	I2CONSET=0x00;

	I2CONCLR=1<<si;

	while(((I2CONSET>>si)&1)==0);

	return I2DAT;

}

char mack(void)

{

	I2CONSET=0X04;

	I2CONCLR=1<<si;

	while(((I2CONSET>>si)&1)==0);

	I2CONCLR=0X04;

	return I2DAT;

}

void stop(void)

{

	I2CONSET=1<<sto;

	I2CONCLR=1<<si;

}
