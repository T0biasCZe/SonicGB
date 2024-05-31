#include <gbdk/metasprites.h>
#include "walksprite.h"
#include <stdio.h>
#include "walksprite.h"
#include "sprites\standsprite.c"
#include "stdlib.h"
#include <gb\gbdecompress.h>
typedef enum {stand,walk,roll}animace_typ;
typedef enum {pravo,levo}animace_dir;

uint32_t framenum = 0;
uint8_t framenumclip(uint8_t e){
	if(e == 16) return 0;
	else return e;
}
uint8_t animspeed;
//uint8_t speed_x_abs;
//int firstranthisanim = 1;
animace_typ lastanim = walk;
uint8_t spriteframe;
uint8_t changed = 1;
uint8_t durationofspriteframe;
uint8_t readaddress;
uint8_t oktorefreshOAM = 1;
uint8_t spriteatribut;
#define walkframes 16
void animate(animace_typ animation,uint16_t x, uint16_t y, uint8_t vpravo, int16_t speed_x){
	//DISABLE_VBL_TRANSFER;
	//oktorefreshOAM = 0;
	speed_x = abs(speed_x);
	if(speed_x < 16){
		animspeed = 12;
	}
	else if(speed_x < 30){
		animspeed = 10;
	}
	else animspeed = 6;
	hide_sprites_range(0,39); //vymazat vše staré
	if(animation == (animace_typ) walk){
		lastanim = walk;
		if(vpravo){
			move_metasprite(walk_metasprites[spriteframe],readaddress,6 ,x,y);
			for(uint8_t aaaaaaa = 0; aaaaaaa < 5; aaaaaaa++){
				set_sprite_prop(aaaaaaa, 0x01 |S_PRIORITY);
			}
			move_metasprite(walk_metasprites_red[spriteframe],217,0,x,y);
		}
		else{
			move_metasprite_vflip(walk_metasprites[spriteframe],readaddress,6 ,x,y);
			for(uint8_t aaaaaaa = 0; aaaaaaa < 5; aaaaaaa++){
				set_sprite_prop(aaaaaaa, 0x01 |S_PRIORITY|S_FLIPX);
			}
			move_metasprite_vflip(walk_metasprites_red[spriteframe],217,0,x,y);
		}
		
		
		durationofspriteframe++;
		if(durationofspriteframe >= animspeed){
			spriteframe++;
			changed = 1;
			durationofspriteframe = 0;
			if(spriteframe >= walkframes) spriteframe = 0;
		}
		
		
		if(changed){
			changed = 0;
			set_sprite_data(217, 6, walk_tiles_red[spriteframe]);
			if((spriteframe % 2) == 0){
				set_sprite_data(240, 14, walk_tiles[framenumclip(spriteframe)]);
				//readaddress = 224;
				readaddress = 240;
			}
			else {
				set_sprite_data(224, 14, walk_tiles[framenumclip(spriteframe)]);
				//readaddress = 240;
				readaddress = 224;
			}
		}
	}
	if(animation == stand){
		if(lastanim == (animace_typ) walk){
			lastanim = ((animace_typ) stand);
			gb_decompress_sprite_data(240,stand_tiles);
			gb_decompress_sprite_data(217,stand_tiles_red);
			set_sprite_data(224, 14, walk_tiles[0]);
			//this code was originally outside this if, but it was moved inside because i figured out the values are gonna not change while this mode is being rendered
			if(vpravo){
				spriteatribut = 0x01 |S_PRIORITY;
			}
			else{
				spriteatribut = 0x01 |S_PRIORITY | S_FLIPX;
			}
			set_sprite_prop(0, spriteatribut);
			set_sprite_prop(1, spriteatribut);
			spriteframe = 0;
			durationofspriteframe = 0;
			changed = 1;
		};
		if(vpravo){
			move_metasprite(stand_metasprite0,240,2,x,y);
			move_metasprite(stand_metasprite0_red,217,0,x,y);
		}
		else{
			move_metasprite_vflip(stand_metasprite0,240,2,x,y);
			move_metasprite_vflip(stand_metasprite0_red,217,0,x,y);
		}
	}
}