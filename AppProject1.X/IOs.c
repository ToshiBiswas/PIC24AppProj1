#include "xc.h"
#include "delay.h"
int button1 = 1;
int button2 = 1;
int button3 = 1;
int interrupt = 1;

int pb3flag = 0;
int timerstart = 0;
int alarm = 0;

int minutes = 0;
int seconds = 0;

void IOinit()
{
    TRISAbits.TRISA2 = 1; //sets input PB1 to RA2
    CNPU2bits.CN30PUE = 1; // pull up
    CNEN2bits.CN30IE = 1;
    
    TRISBbits.TRISB4 = 1; //sets input PB2 to RB4
    CNPU1bits.CN0PUE = 1;
    CNEN1bits.CN0IE = 1;
    
    TRISAbits.TRISA4 = 1; //sets input PB3 to RA4
    CNPU1bits.CN1PUE = 1;
    CNEN1bits.CN1IE = 1;
    
    TRISBbits.TRISB8 = 0; //sets output to RB8
    
    //CN Interrupt settings
    IPC4bits.CNIP = 6; // Highest priority
    IFS1bits.CNIF = 0; // Clear interrupt flag
    IEC1bits.CNIE = 1; //Enable CN interrupts
}

void IOcheck(){
    int position = 0;
    position = (button1*4) + (button2*2) + (button3*1);
    switch(position){
        case(3): //PB1 pressed
            alarm = 0;
            if(minutes == 59){
                minutes = 0;
            }
            else{
                minutes ++;
            }
            updatetime();
            delay_ms(500); // while PB1 is pressed, update minutes every 0.5 seconds
            break;
        case(5): //PB2 pressed
            alarm = 0;
            if(seconds == 59){
                seconds = 0;
            }
            else{
                seconds ++;
            }
            updatetime();
            delay_ms(500); // while PB1 is pressed, update seconds every 0.5 seconds
            break;
        case(6): //PB3 pressed
            interrupt = 0;
            pb3flag = 1;
            delay_ms(3000);
            if(interrupt == 0){
                // long press: stops the countdown and resets the timer to 00m 00s
                pb3flag = 0;
                timerstart = 0;
                minutes = 0;
                seconds = 0;
                updatetime();
            }
            break;
        case(7): //nothing pressed
            if (pb3flag == 1){ 
                pb3flag = 0;
                //short press: starts the timer
                timerstart = 1;
            }

            if (timerstart == 1){
                LATBbits.LATB8 = !LATBbits.LATB8; //led blinks at 1 second intervals
                
                if(seconds == 0){
                    seconds = 59;
                    minutes--;
                }
                else{
                    seconds--;
                }

                if(minutes == 0 && seconds == 0){
                    timerstart = 0;
                    alarm = 1
                }

                updatetime();
                delay_ms(1000);
            }

            if (alarm == 1){ //if alarm is active, idle with led on
                LATBbits.LATB8 = 0; 
                Idle();
            }
            else{ //else idle with led off
                LATBbits.LATB8 = 1;
                Idle();
            }

    }
}



///// Change of pin Interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    //LATBbits.LATB8 = 0;
    T2CONbits.TON=0;   
	//CNflag = 1;   global user defined flag - use only if needed
	IFS1bits.CNIF = 0;		// clear IF flag
    button1 = PORTAbits.RA2;
    button2 = PORTBbits.RB4;
    button3 = PORTAbits.RA4;
    interrupt = 1;
    return;
}

void updatetime(){
    //prints current minutes and seconds to the terminal
    Disp2Dec(minutes);
    Disp2String("m : ");
    Disp2Dec(seconds);
    Disp2String("s ");
    if(alarm == 1){
        Disp2String("-- ALARM");
    }
}
