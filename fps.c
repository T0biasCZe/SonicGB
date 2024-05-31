#include <time.h>
#include <gb/gb.h>
//unsigned int fpss = 0;
//unsigned int lasttime = 0;
//unsigned int iterations = 0;
//uint32_t e = 0;
//uint8_t speedyspeedboy = 30;
/*void speed(int fps_delayer){
	if(fps_delayer < 29) speedyspeedboy--;
	else if(fps_delayer > 31) speedyspeedboy++;
}*/
//unsigned int frame = 0;
unsigned int lastframe = 0;
unsigned char iterations2;
unsigned char fpss2;
//unsigned char fpssdelay;
void fps(){
	iterations2++;
	if(lastframe < time(NULL)){
		lastframe = time(NULL);
		fpss2 = iterations2;
		//fpssdelay = iterations2;
		//iterations2 = 0;
		//speed(fpssdelay);
		iterations2 = 0;
	}
}
/*uint8_t getdel(){
	return speedyspeedboy;
}*/