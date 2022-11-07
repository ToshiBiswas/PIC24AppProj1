#include "delay.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <time.h>
#include <unistd.h>
void delay_ms(uint16_t t){
    
    
    // clear timer
    TMR2 = 0;
    
    //configure T2CON bits
    T2CONbits.TSIDL=0;
    T2CONbits.TCKPS=0;
    T2CONbits.TGATE=0;
    T2CONbits.T32=0;
    T2CONbits.TCS=0;
    T2CONbits.TON=1;

    // Configure Timer2 specific bits in IPC1 IEC0 and IFS1
    IPC1bits.T2IP= 1; // lowest priority
    IEC0bits.T2IE=1;
    IFS0bits.T2IF=0;
    PR2 = 16*t;

    Idle();

    return;
}