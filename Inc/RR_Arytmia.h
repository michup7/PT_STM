/*
 * RR_Arytmia.h
 *
 *  Created on: 22.05.2020
 *      Author: micha
 */

#ifndef RR_ARYTMIA_H_
#define RR_ARYTMIA_H_

//typedef enum {false, true} bool;
int ReturnTotalIntervals(void);
int IsArythmiaDetected(void);
int ReturnCategory(int WhichOneFromTheEnd);
void PushInterval(int interval);
void RRArytmia(int lastIndex,int state);
#endif /* RR_ARYTMIA_H_ */
