#define number_of_rings 15
extern struct Ring;
extern struct Ring{
    uint16_t x;
    uint8_t y;
	_Bool available;
	uint8_t sprite_location; 
};
extern struct Ring ring_data[];
