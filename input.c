#include <gb/gb.h>
_Bool B_A;
_Bool B_B;
_Bool B_UP;
_Bool B_DOWN;
/*uint8_t B_LEFT;
uint8_t B_RIGHT;*/
int8_t leftright;
_Bool azpf = 0;
_Bool PREV_B = 0;
void inputcalc(){
	if(joypad() & J_A){
		if(azpf == 1){
			B_A = 0;
		}
		else{
			B_A = 1;
			azpf = 1;
		}	
	}
	else{
		azpf = 0;
		B_A = 0;
	};
	/*if(joypad() & J_LEFT) B_LEFT = 1;
	else B_LEFT = 0;
	if(joypad() & J_RIGHT) B_RIGHT = 1;
	else B_RIGHT = 0;
	if(joypad() & J_UP) B_UP = 1;
	else B_UP = 0;
	if(joypad() & J_DOWN) B_DOWN = 1;
	else B_DOWN = 0;*/
	if(joypad() & J_LEFT) leftright = -1;
	else if(joypad() & J_RIGHT) leftright = 1;
	else leftright = 0;
	if(joypad() & J_UP) B_UP = 1;
	else B_UP = 0;
	if(joypad() & J_DOWN) B_DOWN = 1;
	else B_DOWN = 0;
	
	//printf("%d",azpf);
}