#include <mega32.h>

#define CW    1
#define CCW   2
#define STOP  3

char StepperBit[8]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09};
unsigned char MS1=0,MotorMove,SetSpeed;
unsigned int Counter;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void){
    TCNT0=SetSpeed;
    switch(MotorMove){
        case CW:
            MS1++;
            if(MS1==8)  MS1=0;
        break;
        case CCW:
            MS1--;
            if(MS1==255)  MS1=7;
        break;
    }
    PORTC&=0xF0;
    PORTC|=StepperBit[MS1];
    Counter++;
}

void main(void){


PORTC=0x00;
DDRC=0x0F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x04;
TCNT0=0x00;
OCR0=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x41;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// Global enable interrupts
#asm("sei")


MotorMove=CW;
SetSpeed=100;

while (1){

};
}
