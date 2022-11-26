/*
 * software_timer.h
 *
 *  Created on: 31 thg 10, 2022
 *      Author: Guest_demo
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define MAX_TIMER 	4
#define CYCLE 		1
#define TIME_UNIT	1000

#define TRAFFIC_1ST	0
#define TRAFFIC_2ND	1
#define TIMER_7SEG	2
#define TIMER_LED	3

void initTimer();
void setTimer(int index, int duration); //duration count as milisecond (duration==1000 ~ 1000ms)
int getCurrTimer(int index); //get current counter for timer, unit milisec.
char isTimerFlagOn(int index);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
