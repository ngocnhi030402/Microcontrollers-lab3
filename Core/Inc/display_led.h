/*
 * display_led.h
 *
 *  Created on: 1 thg 11, 2022
 *      Author: Guest_demo
 */

#ifndef INC_DISPLAY_LED_H_
#define INC_DISPLAY_LED_H_

#define LED_RED		0
#define LED_AMBER	1
#define LED_GREEN	2

#define DISP_INIT	22
#define DISP_RED 	23
#define DISP_GREEN 	24
#define DISP_AMBER 	25

void clear_all_led();

//for test led in PA5
void display_test_led();
void clear_test_led();

//for normal led
void display_blinky_led(int index);

//for 7 segments led
void display_7_seg(int num);
void enable_7_seg(int index);

//for traffic light
void display_light(int index, int type);
void display_time_7seg();
void display_traffic_led(int index);

#endif /* INC_DISPLAY_LED_H_ */
