/*
 * global.c
 *
 *  Created on: 31 thg 10, 2022
 *      Author: Guest_demo
 */

#include "global.h"

int current_mode = 0;
int traffic_duration[3] = {5, 2, 3};
int traffic_state[2] = {0, 0};
int traffic_curr_time[2] = {0, 0};
int traffic_time_buffer[2][2] = {{0, 5}, {0, 3}};
