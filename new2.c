if(animation == (animace_typ) walk){
		durationofspriteframe++;
		if(durationofspriteframe >= animspeed){
			spriteframe++;
			changed = 1;
			durationofspriteframe = 0;
			if(spriteframe >= walkframes) spriteframe = 0;
		}
		
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