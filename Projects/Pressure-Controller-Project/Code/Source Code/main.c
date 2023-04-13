#include <stdint.h>
#include <stdio.h>

#include "driver.h"

#define ON				0
#define OFF				1
#define threeshold		20	

volatile unsigned int Pressure_value;

int main (){
	GPIO_INITIALIZATION();
	Set_Alarm_actuator(OFF);
	while (1)
	{
		Pressure_value = getPressureVal();
		if(Pressure_value > threeshold){
			Set_Alarm_actuator(ON);
			Delay(1000);
			Set_Alarm_actuator(OFF);
		}
		Delay(1000);
	}

}
