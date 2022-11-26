/*
 * fsm_mode_traffic.c
 *
 *  Created on: 21 thg 11, 2022
 *      Author: admin
 */

#include "duration.h"
#include "fsm_mode_traffic.h"
#include "main.h"
#include "global.h"
#include "input_reading.h"
#include "display_led.h"

void fsm_mode_traffic(){
	switch(current_mode){
	/*---------------initial state---------------*/
	case INIT:
		//TODO
		clear_all_led();

		current_mode = MODE_1;
		traffic_state[TRAFFIC_1ST] = DISP_INIT;
		traffic_state[TRAFFIC_2ND] = DISP_INIT;
		setTimer(TIMER_7SEG, 250);
		break;

	/*---------------normal state---------------*/
	case MODE_1:
		//TODO
		display_traffic_led(TRAFFIC_1ST);
		display_traffic_led(TRAFFIC_2ND);
		display_time_7seg();

		//when pressing button 1, change to next mode
		if (isBtnPressed(BTN_1)){
			current_mode = MODE_2;
			change_mode_buffer(MODE_2);
			setTimer(TIMER_LED, 500);
			clear_all_led();
		}
		break;

	/*---------------set led red duration---------------*/
	case MODE_2:
		//TODO
		display_blinky_led(LED_RED);
		display_time_7seg();

		//when pressing button 1, change to next mode
		if (isBtnPressed(BTN_1)){
			current_mode = MODE_3;
			change_mode_buffer(MODE_3);
			setTimer(TIMER_LED, 500);
			clear_all_led();
		}
		//when pressing button 2, increase duration of led red
		if (isBtnPressed(BTN_2)) inc_temp_led_duration();
		//when pressing button 3, apply new duration for led red
		if (isBtnPressed(BTN_3)) update_led_duration(LED_RED);
		break;

	/*---------------set led amber duration---------------*/
	case MODE_3:
		//TODO
		display_blinky_led(LED_AMBER);
		display_time_7seg();

		//when pressing button 1, change to next mode
		if (isBtnPressed(BTN_1)){
			current_mode = MODE_4;
			change_mode_buffer(MODE_4);
			setTimer(TIMER_LED, 500);
			clear_all_led();
		}
		//when pressing button 2, increase duration of led amber
		if (isBtnPressed(BTN_2)) inc_temp_led_duration();
		//when pressing button 3, apply new duration for led amber
		if (isBtnPressed(BTN_3)) update_led_duration(LED_AMBER);
		break;

	/*---------------set led green duration---------------*/
	case MODE_4:
		//TODO
		display_blinky_led(LED_GREEN);
		display_time_7seg();

		//when pressing button 1, change to next mode
		if (isBtnPressed(BTN_1)){
			current_mode = MODE_1;
			traffic_state[TRAFFIC_1ST] = DISP_INIT;
			traffic_state[TRAFFIC_2ND] = DISP_INIT;
			clear_all_led();
		}
		//when pressing button 2, increase duration of led green
		if (isBtnPressed(BTN_2)) inc_temp_led_duration();
		//when pressing button 3, apply new duration for led green
		if (isBtnPressed(BTN_3)) update_led_duration(LED_GREEN);
		break;

	/*---------------other cases---------------*/
	default:
		break;
	}
}
