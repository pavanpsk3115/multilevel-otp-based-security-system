//#include<LPC21XX.H>
void delay_ms(u8 n)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<n);
	T0TCR=0X03;
	T0TCR=0;
}

void delay_sec(u8 n)
{
	T0PR=15000000-1;
	T0TCR=0X01;
	while(T0TC<n);
	T0TCR=0X03;
	T0TCR=0;
}
