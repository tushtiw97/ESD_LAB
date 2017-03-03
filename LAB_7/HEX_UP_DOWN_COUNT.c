#include <stdio.h>
#include <LPC17xx.h>

#define FIRST_SEG 0xF87FFFFF
#define SECOND_SEG 0xF8FFFFFF
#define THIRD_SEG 0xF97FFFFF
#define FOURTH_SEG 0xF9FFFFFF
#define DISABLE_ALL 0xFA7FFFFF

//unsigned long seg_list[4] = {FIRST_SEG, SECOND_SEG, THIRD_SEG, FOURTH_SEG};
unsigned char seg_disp[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
							  0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
unsigned short int val_arr[4] = {0};

void delay(int);
void display();

int main(){
	unsigned int i=0x00, n, n1;
	SystemInit();
	SystemCoreClockUpdate();
	
	//For display
	LPC_PINCON->PINSEL &= 0xFF0000FF;
	LPC_GPIO0->FIODIRL |= 0x0FF0;
	
	//FOr segment selection
	LPC_PINCON->PINSEL3 &= 0xF87FFFFF;
	LPC_GPIO1->FIODIRU |= 0x0780;
	
	//Input
	LPC_PINCON->PINSEL4 &= 0xFDFFFFFFF;
	LPC_GPIO2->FIODIR1 |= 0x00;

	while(1){
		x = LPC_GPIO2->FIOPIN1 & 0x10;
		if (x != 0x10)
			i += 0x01;
		else
			i -= 0x01;
		
		n1 = i;
		for(n=0; n<4; n++){
			val_arr[3-n] = n1 & 0x000F;
			n1 = n1>>8;
		}
		display();
		delay(1000);
	}
	return 0;
}

void delay(int i){
	long j;
	for(j=0; j<i*1000; j++);
}

void display(){
	int n;
	for(n=0; n<4; n++){
		LPC_GPIO1->FIOPIN = n<<23;
		LPC_GPIO0->FIOPIN = seg_disp[val[n]]<<4;
		delay(1);
		LPC_GPIO0->FIOCLRL = 0x0FF0;
	}
}
