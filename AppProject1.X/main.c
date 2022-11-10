/* 
 * File:   main.c
 * Author: jamie
 *
 * Created on October 26, 2022, 12:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <time.h>
#include <unistd.h>
#include "IOs.h"
#include "delay.h"
#include "ChangeClk.h"
#include "UART2.h"

#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled

#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");} //

//int CNflag = 0;
//int T2flag = 0;

int main(void) {
    // set clock speed to 32 kHz
    NewClk(32);

    AD1PCFG = 0xfff;
    IOinit();
    
    while(1){
        IOcheck();
    }
    return 0;
}

    //Timer 2 Interrupt Subroutine
void __attribute__((interrupt,no_auto_psv))_T2Interrupt(void){
    //global variable flag
    //T2flag = 1;
    // reset t2 interrupt flag
    IFS0bits.T2IF=0;
    // turn off clock
    T2CONbits.TON=0;
    
    return;  
}