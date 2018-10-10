#include <wiringPi.h>
#include <stdio.h>

#define   SDI   27   //serial data input
#define   RCLK  28   //memory clock input(STCP)
#define   SRCLK 29   //shift register clock input(SHCP)

unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


void pulse(int pin){
	digitalWrite(pin, 0);
	delay(50);
	digitalWrite(pin, 1);
}

void SIPO(unsigned char byte){
	int i;
	int out;

	for(i=0;i<8;i++){
		out = ((byte & (0x80 >> i)) > 0);
		printf("out: %d, %x\n", out, out);
		digitalWrite(SDI, out);
		pulse(SRCLK);
	}
}

void init(void)
{
	pinMode(SDI, OUTPUT); //make P0 output
	pinMode(RCLK, OUTPUT); //make P0 output
	pinMode(SRCLK, OUTPUT); //make P0 output

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

int main(void)
{
	int i;

	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	init();
	printf("Initialized!\n");

	while(1){

  		printf("First!\n");


		for(i=0;i<8;i++){
			SIPO(LED[i]);
			pulse(RCLK);
			delay(150);
			printf("i = %d\n",i);
		}

		delay(500);

  printf("Second!\n");


		for(i=0;i<3;i++){
			SIPO(0xff);
			pulse(RCLK);
			delay(100);
			SIPO(0x00);
			pulse(RCLK);
			delay(100);
		}
		delay(500);
//		digitalWrite(RCLK,0);

  printf("Third!\n");


		for(i=0;i<8;i++){
			SIPO(LED[8-i-1]);
			pulse(RCLK);
			delay(150);
		}
		delay(500);


  printf("Fourth!\n");


	    for(i=0;i<3;i++){
			SIPO(0xff);
			pulse(RCLK);
			delay(100);
			SIPO(0x00);
			pulse(RCLK);
			delay(100);
		}
		delay(500);
	}

	return 0;
}
