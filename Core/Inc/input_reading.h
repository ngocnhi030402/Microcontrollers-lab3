/*
 * input_reading.h
 *
 *  Created on: 31 thg 10, 2022
 *      Author: Guest_demo
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#define NO_OF_BUTTONS 	3

#define BTN_1	0
#define BTN_2	1
#define BTN_3	2

void button_reading(void);
int isBtnPressed(int index);
void subKeyProcess(int index);

#endif /* INC_INPUT_READING_H_ */
