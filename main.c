#include <gb/cgb.h>
#include <stdio.h>
#include <gbdk/console.h>
#include <gb\gbdecompress.h>
#include <time.h>
#include <rand.h>

#include "fps.h" //fps calculator
#include "input.h" //input calculator. run inputcalc() every frame
#include "walksprite.h" //walking sprite 
#include "animation.h"
#include "sprites\greenhill1_map_compressed.h"
#include "sprites\grafika_compressed.h"
#include "ring.h" //file with array that stores positions for rings
#include "badniks.h" //file with array that stores info about badniks
#include "sprites\ring_sprite.h"
#include "sprites\waterfall.h"
#include "variables.c"
//#include "ringnumbershow.c"
#include "cedule.h"
#include "sprites\finish_poles.h"
#include "dead.h"
#include "printcode.h"
#include "sprites\badniks_sprites.h" //includes the sprites of moto bug and roboryba

uint8_t ringnumberanimationframe[6] = {0,1,2,3,2,1};
const palette_color_t bkg_p[4] = {RGB(31, 31, 31), RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0)};
uint16_t gettilenumber(int16_t iks, int16_t ipsilon){
	if(ipsilon > 0) return ipsilon*130+iks;
	else return 0;
}
//hide the window, triggers at the scanline LYC
void an_lcd_interrupt_func(){
	HIDE_WIN;
}
/*void refreshoam_interrupt(){
	if(oktorefreshOAM){
		refresh_OAM();
	}
}*/

uint32_t framenumber = 0;
void main(){
	//vwf_load_font(0, vwf_font,0);
	//vwf_activate_font(0);
	gb_decompress(greenmapPLN0_compressed,greenmapPLN0);
	gb_decompress(greenmapPLN1_compressed,greenmapPLN1);
	gb_decompress_bkg_data(0,TileLabel);
	set_sprite_palette(0,2,walk_palettes);
	STAT_REG|=0x40;
	LYC_REG = 8; //LCD interrupt 15th scan line
	disable_interrupts();
	add_LCD(an_lcd_interrupt_func);
	//add_VBL(refreshoam_interrupt);
	enable_interrupts();
	set_interrupts(LCD_IFLAG|VBL_IFLAG);
	SPRITES_8x8;
	gb_decompress_bkg_data(0,TileLabel);
	
	cpu_fast();
	
	set_bkg_palette(0,8,green_palette);	
	//show the test backgroud/sprites
	SHOW_BKG; 
	SHOW_SPRITES;
	VBK_REG=1;
	for(uint8_t xxxx = 0; xxxx < 20; xxxx++){
		//set_win_tile_xy(xxxx,1,2);
		set_win_tile_xy(xxxx,0,5);
	}
	set_bkg_submap(lastscrollwritepos,0,32,18,greenmapPLN1,130);
	VBK_REG=0;
	set_bkg_submap(lastscrollwritepos,0,32,18,greenmapPLN0,130);
	set_sprite_data(10,1,ringsprite[0]);
	set_sprite_palette(7,1,ringsprite_palette);
	set_sprite_palette(6,1,badnik1_palettes);
	set_sprite_data(192,4,moto_red_tiles);
	set_sprite_data(196,4,ryba_tiles);
	for(int ringspawn = 30; ringspawn < 40; ringspawn++){
		set_sprite_tile(ringspawn,10);
		set_sprite_prop(ringspawn,0x07);
	}
	printmap(0, 0, 1, 20,200);
	while(1){
		wait_vbl_done();
		fps();
		frames++;
		if(frames >=60){
			frames = 0;
			seconds++;
		}
		if(seconds >= 60){
			seconds = 0;
			minutes++;
		}
		if(lasttime != time(NULL) || ring_count != lastringcount){
			if(seconds < 9) sprintf(text_time,"%d:0%d %d %d",minutes,seconds,ring_count,fpss2);
			else sprintf(text_time,"%d:%d %d %d",minutes,seconds,ring_count,fpss2);
			printtext(text_time,200);
			lastringcount = ring_count;
		}
		SHOW_WIN;
		lasttime = time(NULL);
		inputcalc();
		if(fake_right == 1) leftright = 1;
		//tilegetty
		tilex = x/8;
		tiley = y/8;
		tileleft	= greenmapPLN0[gettilenumber(tilex-1,tiley)];
		tileright	= greenmapPLN0[gettilenumber(tilex+1,tiley)];
		tileup		= greenmapPLN0[gettilenumber(tilex,tiley-1)];
		tiledown	= greenmapPLN0[gettilenumber(tilex,tiley+1)];
		tilecenter	= greenmapPLN0[gettilenumber(tilex,tiley)];
		//sprintf(text_time,"%d %d %d %d %d  ",tiledown,tilex,tiley,gettilenumber(tilex,tiley),greenmapPLN0[1820]);
		//printtext(text_time,200);
		/*if(sys_time % 4== 0){
		1	sprintf(text_time,"%d %d",tilecenter,tiledown);
			vwf_draw_text(0,0,200,text_time);
		}*/
		


		//tilegetty end
		if(tiledown != 0) jumpavailable = 1;
		switch(tiledown){
			case 1:
				//jumpavailable = 1;
				speedy = 0;
				displayval = 1;
				break;
			case 2:
				speedy = 0;
				displayval = 1;
				//jumpavailable = 1;
				if((y % 8) != 0){
					if(y%8 <=5) y = y-(y%8);
					else (8-(y%8))+y;
				}
				break;
			case 5:
				speedy = 0;
				displayval = (((8-(x) % 8))>>1)+4; //replaced calcx/16 with x to skip unnecesary division
				break;
			case 6:
				speedy = 0;
				displayval = ((8-(x) % 8))>>1; //same as above
				break;
			case 7:
				speedy = 0;
				displayval = 3;
				break;
			case 8:
				jumpavailable = 1;
				speedy = 0;
				displayval = 1;
				break;
			case 12:
				jumpavailable = 1;
				speedy = 0;
				displayval = 2;
				break;
			case 15:
				jumpavailable = 1;
				speedy = 0;
				displayval = 4;
				break;
			
			default: //původně case 0, změneno na default kvuli bugu
				if(speedy < 16){
					speedy++;
					displayval = 0;
				}
				break;
		}
		if(tilecenter == 16) dead();
		if(tilecenter == 6 || tilecenter == 5 || tilecenter == 13 || tilecenter == 14 || tilecenter == 7 || tilecenter == 2 || tilecenter == 1) y-=8;
		if(B_A && jumpavailable == 1){
			jumpaccel = 16;
			jumpavailable = 0;
		}
		//jumpaccel_lower = !jumpaccel_lower;
		if(ringframe % 2 && jumpaccel > 0) jumpaccel--;
		y = y - (jumpaccel/4);
		if(jumpaccel > 0) speedy = 0;
		calcx+=speedx;
		y+=(speedy/4);
		switch(leftright){
			case -1:
				if(speedx > -40){
					if(speedx > 0) speedx-=1;
					speedx-=1;
					direction = 0;
				}
				break;
			case 1:
				if(speedx < 40){
					if(speedx < 0) speedx+=1;
					speedx+=1;
					direction = 1;
				}
				break;
			case 0: 
				if(speedx>0) speedx-=2;
				if(speedx<0) speedx+=2;
				break;
		}
		
		backwards_pixels -= speedx;
		if(backwards_pixels<0) backwards_pixels = 0;
		if(backwards_pixels > 104*16){
			while(backwards_pixels > 104*16){
				calcx+=16;
				backwards_pixels-=16;
			}
		}
		x = calcx/16;
		
		waterfall_frame++;
		if(waterfall_frame & 4){
			waterfall_frame = 0;
			waterfall_frame2++;
			if(waterfall_frame2 & 8) waterfall_frame2 = 0;
			set_bkg_data(13,2,waterfall[waterfall_frame2]);
		}
		
		//ANIMATION LOGIC. IF SONIC IS MOVING (SPEED != 0) IT WILL SHOW WALK ANIMATION, ELSE IT WILL SHOW THE STAND ANIMATION
		if(!speedx) animate(stand,24+display_x,y+displayval+8,direction,speedx);
		else animate(walk,24+display_x,y+displayval+8,direction,speedx);
		
		//RESET THE USED RINGS POSITIONS ARRAY TO 0
		//memset(ringsprite_used, 0, 10); //memset needs string.h which is too big, so for() is smaller
		
		for(uint8_t i = 0; i < 10; i++) ringsprite_used[i] = 0; //reset the array each frame
		for(uint8_t i = 0; i < number_of_rings; i++){
			if((x-X_RING_OFFSET < (ring_data[i].x)) && ((ring_data[i].x) < (x+160-X_RING_OFFSET)) && ring_data[i].available & 1){
				move_sprite(ring_data[i].sprite_location,(ring_data[i].x)-x+X_RING_OFFSET,ring_data[i].y+16);
				ringsprite_used[ring_data[i].sprite_location-ringindexsubtract] = 1;
				if(x-16 <(ring_data[i].x) && (ring_data[i].x) < x+2){ 
					if(y/32 == ring_data[i].y/32){
						ring_data[i].available = 0;
						ring_count++;
					}
				}
			}
			else if(!(ringsprite_used[ring_data[i].sprite_location-ringindexsubtract])){
				move_sprite(ring_data[i].sprite_location,200,200);
			}
		}
		
		//badnik logic
		for(uint8_t i = 0; i < numberofbadniks; i++){
			if(badnikData[i].dead & 1) continue; //pokud je badnik mrtvý (bdead slot == 1) tak přeskoč badnika
			switch(badnikData[i].type){
				case bmotobug:
					if(badnikData[i].direction) badnikData[i].current_x++;
					else badnikData[i].current_x--;
					if(badnikData[i].current_x < badnikData[i].max_x_left) badnikData[i].direction = 1;
					if(badnikData[i].current_x > badnikData[i].max_x_right) badnikData[i].direction = 0;
					/*if(x-8 < badnikData[i].current_x && badnikData[i].current_x < x+8 && !jumpavailable && y-8 < badnikData[i].current_y && badnikData[i].current_y < y+8){
						ring_count+=5;
						badnikData[i].dead = 1;
						jumpavailable = 1;
					}*/
					break;
				case bfish:
					if(badnikData[i].direction) badnikData[i].current_y--;
					else badnikData[i].current_y++;
					if(badnikData[i].current_y < badnikData[i].max_y_top) badnikData[i].direction = 0;
					if(badnikData[i].current_y > badnikData[i].max_y_bottom) badnikData[i].direction = 1;
					/*if(x-8 < badnikData[i].current_x && badnikData[i].current_x < x+8 && !jumpavailable && y-8 < badnikData[i].current_y && badnikData[i].current_y < y+8){
						ring_count+=5;
						badnikData[i].dead = 1;
						jumpavailable = 1;
					}*/
					break;
				case woomy:
					//do some future code for woomy (woomy is just placeholder so optimizer doesnt replace this with if else)
					printf("toot toot sonic WOOMY");
					break;
				
			}
			if(x-12 < badnikData[i].current_x && badnikData[i].current_x < x+12 && y-16 < badnikData[i].current_y && badnikData[i].current_y < y+12){
				if(!jumpavailable){
					ring_count+=5;
					badnikData[i].dead = 1;
					jumpavailable = 1; 
				}
				else ring_count--;
			}
			int16_t badnik_displayx = badnikData[i].current_x - x + 16;
			uint8_t badnik_displayy = badnikData[i].current_y + 16;
			if(0 < badnik_displayx && badnik_displayx < 160) move_metasprite(badnik_metasprite,badnikData[i].tile,badnikData[i].slot,badnik_displayx,badnik_displayy);
			for(uint8_t sprite = 20; sprite < 29; sprite++){
				set_sprite_prop(sprite, 0b00000110);
			}
		}
		//load the
		uint8_t tempnumber = ringnumberanimationframe[ringframe/16];
		set_sprite_data(10,1,ringsprite[tempnumber]);
		ringframe++;
		if(ringframe == 96) ringframe = 0;
		
		if(tilex>lastx && x < sign_position-56){
			lastx = tilex;
			VBK_REG=1;
			set_bkg_submap(lastscrollwritepos+20,0,1,18,greenmapPLN1,130);
			VBK_REG=0;
			set_bkg_submap(lastscrollwritepos+20,0,1,18,greenmapPLN0,130);
			lastscrollwritepos++;
		}
		
		if(x > (sign_position-160+16)/* && loadd == 0*/){
				gb_decompress_bkg_data(30,pole_data);
				/*loadd++;*/
				cedule(0,16,10);
		}
		if(x < (sign_position-56)){
			scroll_bkg(x-scrollpositionlast,0);
			//scrollpositionlast = x;
		}
		else{
			display_x += (x-scrollpositionlast);
			//scrollpositionlast = x;
		} 
		scrollpositionlast = x; //moved from above to save ROM. the line was executed in both cases
		if(x > (sign_position)){
			finish_frames_deddeded++;
			if(finish_frames_deddeded > 15){
				animate(stand,24+display_x,y+displayval+8,direction,speedx);
				ceduleeeeeeeee(16,10);
			}
			fake_right = 1;
		}
		
	}
}