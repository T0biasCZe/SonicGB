#include <gbdk/metasprites.h>
#include "walksprite.h"
#include <stdio.h>
#include "walksprite.h"
#include "sprites\standsprite.c"
#include "stdlib.h"
#include <gb\gbdecompress.h>
int squidwii;
typedef enum {stand,walk,run}animace_typ;
typedef enum {pravo,levo}animace_dir;

uint32_t framenum = 0;
int changed = 1;
int even_od = 0;
uint8_t framenumclip(uint8_t e){
	if(e == 16) return 0;
	else return e;
}
uint8_t animspeed;
uint8_t speed_x_abs;
//int firstranthisanim = 1;
animace_typ lastanim;
void animate(animace_typ animation,uint16_t x, uint16_t y, uint8_t vpravo, int16_t speed_x){
	speed_x_abs = abs(speed_x);
	if(speed_x_abs < 16){
		animspeed = 12;
	}
	else if(speed_x_abs < 30){
		animspeed = 10;
	}
	else animspeed = 6;
	hide_sprites_range(0,20); //vymazat vše staré
	
	
	if(animation == walk){
		if(lastanim == stand){
			set_sprite_data(240, 14, walk_tiles[0]);
			lastanim = walk;
			framenum=0;
			squidwii = 0;
			changed = 1;
		} 
		//vpravo = 0;
		//posunout a nahrát sprite od červené části bot
		
		//tohle nahradit gbcompressem
		//tohle nahradit gbcompressem
		//tohle nahradit gbcompressem
		//tohle nahradit gbcompressem
		//tohle nahradit gbcompressem
		
		
		if(vpravo == 1) move_metasprite(walk_metasprites_red[framenumclip(framenum)],217,0,x,y);
		else move_metasprite_vflip(walk_metasprites_red[framenumclip(framenum)],217,0,x,y);
		if(changed == 1){
				set_sprite_data(217, 6, walk_tiles_red[framenumclip(framenum)]);
				refresh_OAM();
		}
		//nahrát sonica
		if(even_od == 0){
			if(squidwii == (animspeed-1)) even_od = 1;
			if(vpravo == 1){
				move_metasprite(walk_metasprites[framenumclip(framenum)],240,6 ,x,y);
				for(uint8_t aaaaaaa = 0; aaaaaaa < 5; aaaaaaa++){
					set_sprite_prop(aaaaaaa, 0x01 |S_PRIORITY);
				}
			}
			else{
				move_metasprite_vflip(walk_metasprites[framenumclip(framenum)],240,6 ,x,y);
				for(uint8_t aaaaaaa = 0; aaaaaaa < 5; aaaaaaa++){
					set_sprite_prop(aaaaaaa, 0x01 |S_PRIORITY|S_FLIPX);
				}
			}
			if(changed == 1){
				set_sprite_data(224, 14, walk_tiles[framenumclip(framenum+1)]);
				changed = 0;
			}
			//nastavit paletu a prioritu pro červenou u bot
			refresh_OAM();
		}
		else{
			if(squidwii == (animspeed-1)) even_od = 0;
			if(vpravo == 1) move_metasprite(walk_metasprites[framenumclip(framenum)],224,6,x,y);
			else move_metasprite_vflip(walk_metasprites[framenumclip(framenum)],224,6,x,y);
			if(changed == 1){
				set_sprite_data(240, 14, walk_tiles[framenumclip(framenum+1)]);
				changed = 0;
			}
			refresh_OAM();
		}
		squidwii++;
		if(squidwii > animspeed-1){
			framenum+=1;
			squidwii = 0;
			changed = 1;
		}
		if(framenum == 15) framenum = 0;
		//printf("%d ",framenum);
	}
	if(animation == stand){
		lastanim = stand;
		if(vpravo == 1){
			move_metasprite(stand_metasprite0,240,2,x,y);
			move_metasprite(stand_metasprite0_red,217,0,x,y);
			set_sprite_prop(0, 0x01 |S_PRIORITY);
			set_sprite_prop(1, 0x01 |S_PRIORITY);
		}
		else{
			move_metasprite_vflip(stand_metasprite0,240,2,x,y);
			move_metasprite_vflip(stand_metasprite0_red,217,0,x,y);
			//set_sprite_prop(0, 0x01 |S_PRIORITY |S_FLIPX);
			//set_sprite_prop(1, 0x01 |S_PRIORITY |S_FLIPX);
			set_sprite_prop(0, 0x01 |S_PRIORITY | S_FLIPX);
			set_sprite_prop(1, 0x01 |S_PRIORITY | S_FLIPX);
		}
		
		//set_sprite_data(240, 9, stand_tiles);
		//set_sprite_data(217, 2, stand_tiles_red);
		gb_decompress_sprite_data(240,stand_tiles);
		gb_decompress_sprite_data(217,stand_tiles_red);
		refresh_OAM();
	}
}