
void motor()
{

	//IODIR1=in1|in2;
	IOCLR1|=in1|in2;

	
		IOSET1|=in1;
		IOCLR1|=in2;
		delay_sec(5);

		IOSET1|=in1|in2;
		delay_sec(10);
		cmd(0x01);
		cmd(0x80);
		lcd_str("system closing");
		IOSET1|=in2;
		IOCLR1|=in1;
		delay_sec(5);

		IOSET1=in1|in2;
	
		
}
