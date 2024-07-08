#define c0 (IOPIN0&(1<<16))		 //input pins
#define c1 (IOPIN0&(1<<17))
#define c2 (IOPIN0&(1<<18))
#define c3 (IOPIN0&(1<<19))

#define r0 1<<11				 //output pins
#define r1 1<<12
#define r2 1<<13
#define r3 1<<14

unsigned char keys[4][4]=	{{'1','2','3','*'},
							{'4','5','6','-'},
							{'7','8','9','+'},
							{'.','0','=','\n'}};
unsigned char keyscan()
{
	int rows,cols;
	IODIR0=r0|r1|r2|r3;

	while(1)
	{
		IOSET0=c0|c1|c2|c3;
		IOCLR0=r0|r1|r2|r3;
		while((c0&&c1&&c2&&c3)==1);

		IOCLR0=r0;
		IOSET0=r1|r2|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
			rows=0;
			break;
		}
		IOCLR0=r1;
		IOSET0=r0|r2|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
			rows=1;
			break;
		}
		IOCLR0=r2;
		IOSET0=r1|r0|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
			rows=2;
			break;
		}
		IOCLR0=r3;
		IOSET0=r1|r2|r0;
		if((c0&&c1&&c2&&c3)==0)
		{
			rows=3;
			break;
		}
	}
	if(c0==0)
	cols=0;
	else if(c1==0)
	cols=1;
	else if(c2==0)
	cols=2;
	else if(c3==0)
	cols=3;
	delay_ms(200);
	while((c0&&c1&&c2&&c3)==0);
	return keys[rows][cols];
}
