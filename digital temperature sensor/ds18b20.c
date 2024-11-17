#include "ds18b20.h"
#include<reg51.h>

void SENSOR_delay(unsigned int useconds)    //using 12MHz
{
    int s;
    for(s=0;s<useconds;s++);
}

unsigned char reset(void)
{
    unsigned char presence;
    DQ=0; //pull DQ line low
    SENSOR_delay(29); // leave it low for 480us
    DQ=1; // allow line to return high
    SENSOR_delay(3); // wait for presence
    presence=DQ; // get presence signal
    SENSOR_delay(25); // wait for end of timeslot
    return(presence); // presence signal returned
} // 0=presence, 1 = no part

unsigned char read_bit(void)
{
    unsigned char i;
    DQ=0; // pull DQ low to start timeslot
    DQ=1; // then return high
    for(i=0;i<3;i++); // delay 15us from start of timeslot
    return(DQ); // return value of DQ line
}

void write_bit(char bitval)
{
    DQ=0; // pull DQ low to start timeslot
    if(bitval==1)
        DQ=1; // return DQ high if write 1
    SENSOR_delay(5); // hold value for remainder of timeslot
    DQ=1;
}// Delay provides 16us per loop, plus 24us. Therefore delay(5) = 104us

unsigned char read_byte(void)
{
    unsigned char i;
    unsigned char value=0;
    for(i=0;i<8;i++)
    {
        if(read_bit()) 
            value|=0x01<<i; // reads byte in, one byte at a time and then shifts it left
        SENSOR_delay(6); // wait for rest of timeslot
    }
    return(value);
}

void write_byte(char val)
{
    unsigned char i;
    unsigned char temp;
    for(i=0;i<8;i++) // writes byte, one bit at a time
    {
        temp=val>>i; // shifts val right 'i' spaces
        temp&=0x01; // copy that bit to temp
        write_bit(temp); // write bit in temp into
    }
    SENSOR_delay(5);
}

void Read_Temperature(void)
{
    char temp_lsb,temp_msb;
    int temp,k;
    temp=0;
    reset();
    write_byte(0xCC); //Skip ROM
    write_byte(0x44); // Start Conversion
    SENSOR_delay(5);
    reset();
    write_byte(0xCC); // Skip ROM
    write_byte(0xBE); // Read Scratch Pad
    for(k=0;k<9;k++)
        ScratchPAD[k]=read_byte();
    temp_msb=ScratchPAD[1]; // Sign byte + lsbit
    temp_lsb=ScratchPAD[0]; // Temp data plus lsb

    
    temp=(temp_msb&0x07);
    temp<<=8;
    temp|=temp_lsb;

    if(temp_msb>=0xF8)
    {
        temp=~temp;
        temp+=1;
    }

    temp_c=temp*0.0625;
    if(temp_msb>=0xF8)
        temp_c*=(-1);

    temp_f=(((int)temp_c)*9)/5+32;
}