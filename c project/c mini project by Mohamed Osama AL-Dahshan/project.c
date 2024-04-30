/*
 * project.c
 *
 *  Created on: Dec 25, 2023
 *      Author: mod_n
 */


#include<stdio.h>

#define WITH_ENGINE_TEMP_CONTROLLER 0

enum{OFF,ON
};

typedef struct {
	unsigned short room_temp;
	unsigned short vehicle_speed;
	char AC;

#if  WITH_ENGINE_TEMP_CONTROLLER
	char engine_controller;
	unsigned short engine_temp;
#endif

}vehicle_sensors;// all sensors needed to control the vehicle in the structure



void status_disply(vehicle_sensors * sensors){
	printf("Engine is ON\n");

	if(sensors->AC==OFF)
		printf("AC is OFF\n");
	else
		printf("AC is ON\n");

	printf("vehicle speed = %d km/h\n",sensors->vehicle_speed);

	printf("Room temperature = %d C\n",sensors->room_temp);
#if  WITH_ENGINE_TEMP_CONTROLLER
	if(sensors->engine_controller==OFF)
			printf("Engine temperature controller is OFF\n");
		else
			printf("Engine temperature controller is ON\n");

	printf("Engine temperature = %d C",sensors->engine_temp);
#endif
	printf("\n\n");
return;
}

void System_check(vehicle_sensors * sensors){

	if(sensors->vehicle_speed==30){
#if  WITH_ENGINE_TEMP_CONTROLLER
									sensors->engine_controller=ON;

									sensors->engine_temp=(sensors->engine_temp*(5/4))+1;

#endif

									sensors->AC=ON;

									sensors->room_temp=(sensors->room_temp*(5/4))+1;
	}

	status_disply(sensors);
}
#if  WITH_ENGINE_TEMP_CONTROLLER
void engine_temp_set(vehicle_sensors * sensors){
	printf("Enter engine temperature \n");
		scanf(" %hu",&sensors->engine_temp);

		if(sensors->engine_temp < 100 || sensors->engine_temp >150){
			sensors->engine_temp=125;
			sensors->engine_controller=ON;
		}
		else
			sensors->engine_controller=OFF;
		System_check(sensors);
		return;
}
#endif
void Room_temp_set(vehicle_sensors * sensors){

	printf("Enter room temperature \n");
	scanf(" %hu",&sensors->room_temp);

	if(sensors->room_temp < 10 || sensors->room_temp >30){
		sensors->AC=ON;
	}
	else
		sensors->AC=OFF;
	System_check(sensors);
	return;
}

void Traffic_light_set(vehicle_sensors * sensors){
	char input3;

	while(1){
		printf("G. green\nO. orange\nR. red\n");
		scanf(" %c",&input3);

		switch(input3){
		case 'g' :
		case 'G' :// for  green case
					sensors->vehicle_speed=100;
					break;

		case 'o' :
		case 'O' :  //for orange case
					sensors->vehicle_speed=30;
					break;

		case 'r' :
		case 'R' : // for red case
					sensors->vehicle_speed=0;
					break;

		default:                                 // if it's not red or green or orange ask user again
			continue;
}
		System_check(sensors);
		return;
	}
}

void Sensors_set_menu(vehicle_sensors * sensors){
	char input2;

	while(1){
		printf("a. Turn off the engine\nb. Set the traffic light color.\nc. Set the room temperature (Temperature Sensor)\n");

#if  WITH_ENGINE_TEMP_CONTROLLER
		printf("d. Set the engine temperature (Engine Temperature Sensor)\n");

#endif
		printf("r. Reset all sensors\n");
		scanf(" %c",&input2);

		switch(input2){
		case 'a':
					printf("Turn off the vehicle engine\n\n");
					return;

		case 'b' :
					printf("Set the traffic light color\n\n");
					Traffic_light_set(sensors);// address of the structure which is the pointer value
					break;

		case 'c' :
					printf("Set the room temperature (Temperature Sensor)\n\n");
					Room_temp_set(sensors);
					break;

#if  WITH_ENGINE_TEMP_CONTROLLER

		case 'd' :
					printf("Set the engine temperature (Engine Temperature Sensor))\n\n");
					engine_temp_set(sensors);
					break;
#endif
		case 'r' :
							printf("Reset\n\n");
							sensors->room_temp=20; // initial values
							sensors->vehicle_speed=100;
							sensors->AC=OFF;
#if  WITH_ENGINE_TEMP_CONTROLLER
							sensors->engine_temp=125;
							sensors->engine_controller=OFF;
#endif
							break;
						}


	}
}

void Main_menu(){
	char input1;
	vehicle_sensors sensors;
		sensors.room_temp=20; // initial values
		sensors.vehicle_speed=100;
		sensors.AC=OFF;
#if  WITH_ENGINE_TEMP_CONTROLLER
		sensors.engine_temp=125;
		sensors.engine_controller=OFF;
#endif

		while(1){
			printf("a. Turn on the vehicle engine\nb. Turn off the vehicle engine\nc. Quit the system\n");
			scanf(" %c",&input1);

			switch(input1){

			case 'c':
				printf("Quit the system");
				return;


			case 'b' :
				printf("Turn off the vehicle engine\n\n");
				continue;


			case'a':
				printf("Turn on the vehicle engine\n\n");
				Sensors_set_menu(&sensors);
				break;
			}
		}

}

int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	Main_menu();
	return 0;
}
