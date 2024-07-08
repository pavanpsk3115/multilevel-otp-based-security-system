#define txd 1<<0
#define rxd 1<<2
void uart0_init(void)
{
	PINSEL0|=txd|rxd;	//P0.0,P0.1  AS RXD,TXD
	U0LCR=0X83;
	U0DLL=97;
	U0LCR=0X03;
}
void uart0_tx(char ch)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=ch;
}
char uart0_rx(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
void uart_read_pwd(char *q,int n)
{
	u8 i;
	for(i=0;i<n;i++)
	{
		q[i]=uart0_rx();
		
	}
	//q[i]='\0';	
}
