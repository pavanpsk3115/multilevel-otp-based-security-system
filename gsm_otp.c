char s[10];
void gsm(char*);
void gsm_cmd_write(char *s);
char* otp(void)
{
	int i;
	cmd(0x01);
	cmd(0x80);
	lcd_str("To Generate OTP");
	cmd(0xc0);
	lcd_str("click switch-2");
	//-----------generates OTP-----------------
	while(1)
	{
		if(((IOPIN0>>sw1)&1)==0)
			break;
		if(i==9999)
			i=1000;
		i++;
	}	
															
	sprintf(s,"%d",i);
	
	s[4]='\r';
	s[5]='\n';
	s[6]='\0';
	
	//lcd_str(s);
	delay_ms(5);
	gsm(s);
	
	return s;

}
void gsm(char*s)
{
	uart0_init();
	gsm_cmd_write("AT\r\n");
	delay_ms(500);
	gsm_cmd_write("AT+CMGF=1\r\n");
	delay_ms(500);
	gsm_cmd_write("AT+CMGS=\"+918328361488\"\r\n");
	delay_ms(500);
	gsm_cmd_write(s);
	uart0_tx(0x1a);
}
void gsm_cmd_write(char *s)
{
	while(*s)
	{
		uart0_tx(*s++);
	}
}
