/* 
 * File:   delay.h
 * Author: jamie
 *
 * Created on October 26, 2022, 12:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <time.h>
#include <unistd.h>
#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif

void delay_ms(uint16_t t);


#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

