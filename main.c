/*multi level security system*/
#include<LPC21XX.H>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "define.h"
#include "delay.h"
#include "i2c_defines.h"
#include "lcd.h"
#include "i2c.h"
#include "uart0.h"
#include "motor_driver.c"
#include "eeprom_i2c.h"
#include "gsm_otp.c"

#include "keypad.h"


#include "operations.c"


int main()
{
	//char p[5];
	char option;
	char key;
	IODIR1|=in1|in2;
	IOSET1|=	in1|in2;
	i2c_init();

	uart0_init();
	lcd_start();
	//step-1:storing default password in eeprom
	 
	eeprom_seq_write(0x50,0x00,"1234",4);
		//data('a');
	//------------------------------------------

	//step-2: selcet option
	
	while(1)
	{
		cmd(0x80);
		lcd_str("welcome psk"); // display
		
		cmd(0xc0);
		lcd_str("system locked");

		key=keyscan();
		
		//----------unlocking or changing password-------------
		if(key=='\n')
		{
			
			cmd(0x01);
			cmd(0x80);
			lcd_str("1.open lock");
			cmd(0xc0);
			lcd_str("2.set password");
			
				option=keyscan();

				if(option=='1')
				{
					open_lock();						//unlocking
					cmd(0x01);	
				}
				
				else if(option=='2')
				{
					set_pswd();							//change password
					cmd(0x01);	
				}	
		}
	}
}
