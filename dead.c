#include <gb/cgb.h>
#include <gb/gb.h>
#include <stdio.h>
const palette_color_t redtext[4] = {RGB(31, 0, 0), RGB(31, 0, 0), RGB(31, 0, 0), RGB(0, 0, 0)};
void dead(){
			set_bkg_palette(0,1,redtext);
			//vwf_set_destination(VWF_RENDER_BKG);
			VBK_REG=1;
			for(uint8_t yyyy = 0; yyyy < 32; yyyy++){
				for(uint8_t xxxx = 0; xxxx < 32; xxxx++){
					set_bkg_tile_xy(xxxx,yyyy,0);
				}
			}
			VBK_REG=0;
			for(uint8_t yyyy = 0; yyyy < 32; yyyy++){
				for(uint8_t xxxx = 0; xxxx < 32; xxxx++){
					set_bkg_tile_xy(xxxx,yyyy,0);
				}
			}
			printf("    YOU ARE DED\n\  NO BIG SURPRISE");
			//vwf_draw_text(0, 9, 200,"  YOU ARE DED\n NO BIG SUPRISE");
			//gotoxy(0,9);
			//move_bkg(-40,12);
			move_bkg(-4,12+(9*8));
			//printf("YOU ARE DED");
			HIDE_SPRITES;
			while(1);
}