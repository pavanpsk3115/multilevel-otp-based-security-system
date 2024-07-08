void eeprom_write(u8 slave_add,u8 reg_add,u1 data);
char eeprom_read(u8 slave_add,u8 reg_add);

void eeprom_write(u8 slave_add,u8 reg_add,u1 data)
{
	start();
	write(slave_add<<1);
	write(reg_add);
	write(data);
	stop();
	delay_ms(10);
}
char eeprom_read(u8 slave_add,u8 reg_add)
{
	u8 data;
	start();
	write(slave_add<<1);
	write(reg_add);
	restart();
	write((slave_add<<1)|1);
	data=nack();
	return data;
}
void eeprom_seq_write(u8 slave_add,u8 reg_add,c1*p,u8 n)

{

	u8 i;

	start();

	write(slave_add<<1);

	write(reg_add);

	for(i=0;i<n;i++)

	{

		write(p[i]);

	}

	stop();

	delay_ms(10);

}

void eeprom_seq_read(u8 slave_add,u8 reg_add,c1*p,u8 n)

{

	u8 i;

	start();

	write(slave_add<<1);

	write(reg_add);

	restart();

	write((slave_add<<1)|1);

	for(i=0;i<n-1;i++)

	{

		p[i]=mack();

	}

	p[i]=nack();

	i++;

	p[i]='\0';

	stop();

	

}
