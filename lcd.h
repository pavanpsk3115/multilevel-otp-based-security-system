
#define lcd 0X0f<<20
#define rs 1<<17	
#define rw 1<<18	
#define e 1<<19
void delay_ms(unsigned int);	
void lcd_start(void);			
void cmd(unsigned char);		
void data(unsigned char);		
void str(char*);
void lcd_start(void)			
{								
	IODIR1|=lcd|rs|rw|e;			
	IOCLR1|=rw;					
	cmd(0x01);					
	cmd(0x02);					
	cmd(0x0c);					
	cmd(0x28);					
	cmd(0x80);					
}								
void cmd(unsigned char cd)		
{								
	IOCLR1|=lcd;					
	IOSET1|=(cd&0xf0)<<16;		
	IOCLR1|=rs;					
	IOSET1|=e;					
	delay_ms(2);				
	IOCLR1|=e;	
													
	IOCLR1|=lcd;					
	IOSET1|=(cd&0x0F)<<20;		
	IOCLR1|=rs;					
	IOSET1|=e;					
	delay_ms(2);				
	IOCLR1|=e;					
}								
void data(unsigned char d)		
{								
	IOCLR1|=lcd;					
	IOSET1|=(d&0xf0)<<16;		
	IOSET1|=rs;					
	IOSET1|=e;					
	delay_ms(2);				
	IOCLR1|=e;					
									
	IOCLR1|=lcd;					
	IOSET1|=(d&0x0F)<<20;	 
	IOSET1|=rs;				 
	IOSET1|=e;				  
	delay_ms(2);			  
	IOCLR1|=e;				  
}							  
void lcd_str(char*s)			  
{							  
	while(*s)
	{
		
		data(*s++);
	}		
}

