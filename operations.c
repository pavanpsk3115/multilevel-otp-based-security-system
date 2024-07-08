
int count;
char p[10];
char q[10];

//-----------------------------------UNLOCKING----------------------------------

void open_lock()
{
	char*op;int i;
	
	//~~~~~~~~~~~~password verification~~~~~~~~~~~~~~
	cmd(0x01);
	cmd(0x80);
	lcd_str("enter pwd");
	
	pswd:
	cmd(0xc0);
	//uart_read_pwd(q,4);			//keypad
	for(i=0;i<4;i++)
	{
		q[i]=keyscan();
		data('x');
	}
	q[i]='\0';
	cmd(0x01);
	
	

	eeprom_seq_read(0x50,0x00,p,4);
	
	if(strncmp(p,q,4)!=0)
	{
		cmd(0x01);
		cmd(0x80);
		lcd_str("wrong password");
		count++;
		delay_sec(3);
		cmd(0x01);
		cmd(0x80);
		lcd_str("re-enter pswd");
		if(count<3)
		goto pswd;
		else
		{
			cmd(0x01);
			cmd(0x80);
			lcd_str("sytem blocked");
			cmd(0xc0);
			count=0;
			lcd_str("wait 24hrs");
			gsm("ALERT:system was trying to unlock by anonymous person take an action immediately\r\n"); 
			delay_sec(10);
			cmd(0x01);
			cmd(0x80);
			lcd_str("re-enter pswd");
			goto pswd;
		}	
	}
	cmd(0x01);
	lcd_str("correct password");
	delay_sec(2);

	//~~~~~~~~~~otp verification~~~~~~~~~~~~~
	count=0;
	cmd(0x01);
	cmd(0x80);
	op=otp();				//generates otp
	
	cmd(0x01);
	cmd(0x80);
	lcd_str("enter otp");
	
	repeat:
	cmd(0xc0);								
//	uart_read_pwd(q,4);			//keypad
	for(i=0;i<4;i++)
	{
		q[i]=keyscan();
		data('x');
	}
	q[i]='\0';

	if(strncmp(q,op,4)!=0)
	{
		cmd(0x01);
		cmd(0x80);
		lcd_str("wrong otp");
		count++;
		delay_sec(3);
		//lcd_str("re-enter otp");
		if(count<3)
		{
			op=otp();				//generates otp
			cmd(0x01);
			cmd(0x80);
			lcd_str("re-enter otp");
			goto repeat;
		}
		else
		{
			cmd(0x01);
			cmd(0x80);
			lcd_str("sytem blocked");
			cmd(0xc0);
			count=0;
			lcd_str("wait 24hrs");
			gsm("ALERT:system was trying to unlock by anonymous person take an action immediately\r\n");
			delay_sec(20);
			op=otp();
			cmd(0x01);
			cmd(0x80);
			lcd_str("re-enter otp");
			goto repeat;
		}
	}
	cmd(0x01);
	cmd(0x80);
	lcd_str("verifying");
	delay_sec(3);
	cmd(0x01);
	cmd(0x80);
	lcd_str("system unlocked");
	motor();
	
	
}

//-------------------------------SET PASSWORD----------------------------------


void set_pswd()
{
	int i;
	char*op;
	count=0;
	//~~~~~~~~~~password verification~~~~~~~~~~~~~~~
	cmd(0x01);
	cmd(0x80);
	lcd_str("enter old pwd");
	
	pswd:
	cmd(0xc0);
//	uart_read_pwd(q,4);			//keypad
	for(i=0;i<4;i++)
	{
		q[i]=keyscan();
		data('x');
	}
	q[i]='\0';
	
	eeprom_seq_read(0x50,0x00,p,4);
	if(strncmp(p,q,4)!=0)
	{
		cmd(0x01);
		cmd(0x80);
		lcd_str("wrong password");
		count++;
		delay_sec(3);
		cmd(0x01);
		cmd(0x80);
		lcd_str("re-enter pswd");
		if(count<3)
		goto pswd;
		else
		{
			cmd(0x01);
			cmd(0x80);
			lcd_str("sytem blocked");
			cmd(0xc0);
			count=0;
			lcd_str("wait 24hrs");
			gsm("ALERT:system was trying to unlock by anonymous person take an action immediately\r\n");
			delay_ms(1000);
			cmd(0x01);
			cmd(0x80);
			lcd_str("re-enter pswd");
			goto pswd;
		}	
	}
	cmd(0x01);
	lcd_str("correct password");
	delay_sec(2);
	
	//~~~~~~~~~~~~~~~~otp verification~~~~~~~~~~~~~
	count=0;
	
	op=otp();				//generates otp
	
	cmd(0x01);
	cmd(0x80);
	lcd_str("enter otp");

	repeat:
	cmd(0xc0);
//	uart_read_pwd(q,4);			//keypad
 	for(i=0;i<4;i++)
	{
		q[i]=keyscan();
		data('x');
	}
	q[i]='\0';

	if(strncmp(q,op,4)!=0)
	{
		cmd(0x01);
		cmd(0x80);
		lcd_str("wrong otp");
		count++;
		delay_ms(100);
		cmd(0x01);
		cmd(0x80);
		//lcd_str("re-enter new otp");
		if(count<3)
		{
			op=otp();
			cmd(0x01);
			cmd(0x80);
			lcd_str("re-enter new otp");			//generates otp
			goto repeat;
		}
		else
		{
			cmd(0x01);
			cmd(0x80);
			lcd_str("sytem blocked");
			cmd(0xc0);
			count=0;
			lcd_str("wait 24hrs");
			gsm("ALERT:system was trying to unlock by anonymous person take an action immediately\r\n");
			delay_sec(20);
			op=otp();								//generates otp
			cmd(0x01);
			cmd(0x80);
			lcd_str("re-enter otp");
			
			goto repeat;
		}
		
	}
	
	cmd(0x01);
	cmd(0x80);
	lcd_str("set the password");
	cmd(0xc0);
//	uart_read_pwd(q,4);						   //keypad
	for(i=0;i<4;i++)
	{
		q[i]=keyscan();
		data('x');
	}
	q[i]='\0';
	eeprom_seq_write(0x50,0x00,q,4);
	cmd(0x01);
	cmd(0x80);
	lcd_str("password changed");
	cmd(0xc0);
	lcd_str("successfully");
	delay_sec(5);
	
}
