#include "Sprites\pole\egg.c"
#include "Sprites\pole\egg_rotated.c"
#include "Sprites\pole\egg_rotated_mirrored.c"
#include "Sprites\pole\empty.c"
#include "Sprites\pole\empty_rotated.c"
#include "Sprites\pole\empty_rotated_mirrored.c"
#include "Sprites\pole\sonic_rotated.c"
#include "Sprites\pole\sonic_rotated_mirrored.c"
#include "Sprites\pole\sonicfinished.c"
#include "Sprites\pole\pole.c"
#include <gb/cgb.h>
#include <stdio.h>
#include <gb/gb.h>


//egg > egg_rotated > pole > empty_rotated > empty > empty_rotated_mirrored > pole > egg_rotated_mirrored > (tohle 4x)
//sonicfinished > sonic_rotated > pole > empty_rotated > empty > empty_rotated_mirrored > pole > sonic_rotated_mirrored > (tohle 4x)
//1 > 2 > 6 > 3 > 9 > 7 > 6 > 10 > 
//4 > 6 > 3 > 9 > 7 > 6 > 8 > 5 >
//typedef enum{0egg,1egg_rotated,2empty_rotated,3sonic_rotated,4sonicfinished,5pole,6empty_rotated_mirrored,7sonic_rotated_mirrored,8empty,9egg_rotated_mirrored}sign_framy_animace;
//typedef enum{egg,egg_rotated,empty_rotated,sonic_rotated,sonicfinished,pole,empty_rotated_mirrored,sonic_rotated_mirrored,empty,egg_rotated_mirrored}sign_framy_animace;


const palette_color_t egg_palette[4] = {
	RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0), RGB(31, 0, 0)
};
const palette_color_t egg_rotated_palette[4] = {
	RGB(31, 0, 0), RGB(10, 10, 10), RGB(0, 0, 0), RGB(0, 0, 31)
};
const palette_color_t sonicfinished_palette[4] = {
	RGB(31, 31, 31), RGB(10, 10, 10), RGB(0, 0, 0), RGB(0, 10, 31)
};

const palette_color_t sonic_rotated_palette[4] = {
	RGB(0, 10, 31), RGB(10, 10, 10), RGB(0, 0, 0), RGB(0, 0, 31)
};

uint8_t cedule_frames_data_eggman[] = {0,1,5,2,8,6,5,9};
uint8_t cedule_frames_data_sonic[] = {4,3,5,2,8,6,5,7};
void *cedule_frames_palette[] = {egg_palette,egg_rotated_palette,sonic_rotated_palette,sonic_rotated_palette,sonicfinished_palette,sonic_rotated_palette,sonic_rotated_palette,sonic_rotated_palette,egg_palette,egg_rotated_palette};
void *cedule_frames_PLN0[] = {eggPLN0,egg_rotatedPLN0,empty_rotatedPLN0,sonic_rotatedPLN0,sonicfinishedPLN0,polePLN0,empty_rotated_mirroredPLN0,sonic_rotated_mirroredPLN0,emptyPLN0,egg_rotated_mirroredPLN0};
void *cedule_frames_PLN1[] = {eggPLN1,egg_rotatedPLN1,empty_rotatedPLN1,sonic_rotatedPLN1,sonicfinishedPLN1,polePLN1,empty_rotated_mirroredPLN1,sonic_rotated_mirroredPLN1,emptyPLN1,egg_rotated_mirroredPLN1};
void cedule(uint8_t veemo,uint8_t x, uint8_t y){ //	== != = === <= >= > < => -> <-
	set_bkg_palette(1,1,cedule_frames_palette[veemo]);
	VBK_REG=1;
	set_bkg_tiles(x,y,3,3,cedule_frames_PLN1[veemo]);
	VBK_REG=0;
	set_bkg_tiles(x,y,3,3,cedule_frames_PLN0[veemo]);
}
//jeden frame je 16.746098797598020710762747475922ms
void ceduleeeeeeeee(uint8_t x_signn, uint8_t y_signn){
	HIDE_WIN;
	uint16_t delayval = 83;
	for(uint8_t opakuj = 0; opakuj < 24; opakuj++){
		cedule(cedule_frames_data_eggman[opakuj%8],x_signn,y_signn);
		delay(delayval);
		delayval += 4;
	}
	for(uint8_t opakuj = 0; opakuj < 16; opakuj++){
		cedule(cedule_frames_data_sonic[opakuj%8],x_signn,y_signn);
		delayval+=8;
		delay(delayval);
	}
	cedule(4,x_signn,y_signn);
	delay(20000);
}