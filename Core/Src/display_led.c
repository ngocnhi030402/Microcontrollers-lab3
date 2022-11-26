/*
 * display_led.c
 *
 *  Created on: 1 thg 11, 2022
 *      Author: Guest_demo
 */

#include "display_led.h"
#include "main.h"
#include "global.h"

int led_7seg_index = 0;

void clear_all_led(){
	HAL_GPIO_WritePin(GPIOA, LED_TEST_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_R1_Pin | LED_Y1_Pin | LED_G1_Pin
							| LED_R2_Pin | LED_Y2_Pin | LED_G2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin
							| SEG4_Pin | SEG5_Pin | SEG6_Pin, GPIO_PIN_SET);
}

void display_test_led(){
	HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_RESET);
}

void clear_test_led(){
	HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_SET);
}
/*--------------------------7-segment led--------------------------------*/
void blink_led(int index){
	switch(index){
	case LED_RED:
		HAL_GPIO_TogglePin(GPIOA, LED_R1_Pin | LED_R2_Pin);
		break;
	case LED_AMBER:
		HAL_GPIO_TogglePin(GPIOA, LED_Y1_Pin | LED_Y2_Pin);
		break;
		break;
	case LED_GREEN:
		HAL_GPIO_TogglePin(GPIOA, LED_G1_Pin | LED_G2_Pin);
		break;
		break;
	default:
		break;
	}
}

void display_blinky_led(int index){
	if(isTimerFlagOn(TIMER_LED)){
		setTimer(TIMER_LED, 500);
		blink_led(index);
	}
}

/*--------------------------7-segment led--------------------------------*/
void update_time_buffer(int index, int time){
	traffic_time_buffer[index][0] = time/10;
	traffic_time_buffer[index][1] = time%10;
}

void display_7_seg(int num){
	switch (num){
	case 0: // display 0 using leds: a, b, c, d, e, f
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
								SEG3_Pin | SEG4_Pin | SEG5_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG6_Pin, 1);
		break;
	case 1: // display 1 using leds: b, c
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG2_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG3_Pin | SEG4_Pin |
								SEG5_Pin | SEG6_Pin, 1);
		break;
	case 2: // display 2 using leds: a, b, d, e, g
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG3_Pin |
								SEG4_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG2_Pin | SEG5_Pin, 1);
		break;
	case 3: // display 3 using leds: a, b, c, d, g
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
								SEG3_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG4_Pin | SEG5_Pin, 1);
		break;
	case 4: // display 4 using leds: b, c, f, g
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG2_Pin | SEG5_Pin |
								SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG3_Pin | SEG4_Pin, 1);
		break;
	case 5: // display 5 using leds: a, c, d, f, g
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG2_Pin | SEG3_Pin |
								SEG5_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG4_Pin, 1);
		break;
	case 6: // display 6 using leds: a, c, d, e, f, g
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG2_Pin | SEG3_Pin |
								SEG4_Pin | SEG5_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin, 1);
		break;
	case 7: // diplay 7 using leds: a, b, c
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG3_Pin | SEG4_Pin | SEG5_Pin |
								SEG6_Pin, 1);
		break;
	case 8: // display 8 using leds: a, b, c, d, e, f, g
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
								SEG3_Pin | SEG4_Pin | SEG5_Pin |
								SEG6_Pin, 0);
		break;
	case 9: // display 9 using leds: a, b, c, d, f, g
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
								SEG3_Pin | SEG5_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG4_Pin, 1);
		break;
	default:
		break;
	}
}

void enable_7_seg(int index){
	switch (index){
	case 0:
		HAL_GPIO_WritePin(GPIOB, EN0_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN2_Pin | EN3_Pin, SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, EN1_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, EN0_Pin | EN2_Pin | EN3_Pin, SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, EN2_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN0_Pin | EN3_Pin, SET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, EN3_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN2_Pin | EN0_Pin, SET);
		break;
	default:
		break;
	}
	display_7_seg(traffic_time_buffer[index/2][index%2]);
}

/*--------------------------Traffic Light--------------------------------*/
void display_traffic_led(int index){
	switch(traffic_state[index]){
	case DISP_INIT: //intial state
		//TODO
		if (index == TRAFFIC_1ST){
			traffic_state[index] = DISP_RED;
			setTimer(index, traffic_duration[LED_RED]*TIME_UNIT);
		}
		else {
			traffic_state[index] = DISP_GREEN;
			setTimer(index, traffic_duration[LED_GREEN]*TIME_UNIT);
		}
		break;

	case DISP_RED: //display red led
		display_light(index, LED_RED);

		if (isTimerFlagOn(index)){
			traffic_state[index] = DISP_GREEN;
			setTimer(index, traffic_duration[LED_GREEN]*TIME_UNIT);
		}
		break;

	case DISP_GREEN: //display green led
		display_light(index, LED_GREEN);

		if (isTimerFlagOn(index)){
			traffic_state[index] = DISP_AMBER;
			setTimer(index, traffic_duration[LED_AMBER]*TIME_UNIT);
		}
		break;

	case DISP_AMBER: //display amber led
		display_light(index, LED_AMBER);

		if (isTimerFlagOn(index)){
			traffic_state[index] = DISP_RED;
			setTimer(index, traffic_duration[LED_RED]*TIME_UNIT);
		}
		break;

	default:
		break;
	}
	traffic_curr_time[index] = (getCurrTimer(index)+1000)/TIME_UNIT; //get current counter (unit: sec)
	update_time_buffer(index, traffic_curr_time[index]);
}


void display_light(int index, int type){
	switch(index){
	case TRAFFIC_1ST: //Set specific light for the 1st traffic light
		switch(type){
		case LED_RED:
			HAL_GPIO_WritePin(GPIOA, LED_R1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_G1_Pin | LED_Y1_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN:
			HAL_GPIO_WritePin(GPIOA, LED_G1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_Y1_Pin | LED_R1_Pin, GPIO_PIN_SET);
			break;
		case LED_AMBER:
			HAL_GPIO_WritePin(GPIOA, LED_Y1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_R1_Pin | LED_G1_Pin, GPIO_PIN_SET);
			break;
		default:
			break;
		}
		break;
	case TRAFFIC_2ND: //Set specific light for the 2nd traffic light
		switch(type){
		case LED_RED:
			HAL_GPIO_WritePin(GPIOA, LED_R2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_G2_Pin | LED_Y2_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN:
			HAL_GPIO_WritePin(GPIOA, LED_G2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_Y2_Pin | LED_R2_Pin, GPIO_PIN_SET);
			break;
		case LED_AMBER:
			HAL_GPIO_WritePin(GPIOA, LED_Y2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_R2_Pin | LED_G2_Pin, GPIO_PIN_SET);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void display_time_7seg(){
	if (isTimerFlagOn(TIMER_7SEG)){
		setTimer(TIMER_7SEG, 250);
		enable_7_seg(led_7seg_index);
		led_7seg_index = (led_7seg_index+1)%4;
	}
}

