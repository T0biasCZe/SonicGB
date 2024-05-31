#include <gb/cgb.h>
#include <gb/gb.h>
#define number_of_rings 15
struct Ring{
    uint16_t x;
    uint8_t y;
	_Bool available;
	uint8_t sprite_location; 
};
struct Ring ring_data[] = {
    {.x = 280, .y = 32, .available = 1, .sprite_location = 30},
	{.x = 288, .y = 32, .available = 1, .sprite_location = 31},
	{.x = 296, .y = 32, .available = 1, .sprite_location = 32},
	{.x = 304, .y = 32, .available = 1, .sprite_location = 33},
	{.x = 312, .y = 32, .available = 1, .sprite_location = 34},
	//most
	{.x = 488, .y = 80, .available = 1, .sprite_location = 30},
	{.x = 496, .y = 80, .available = 1, .sprite_location = 31},
	{.x = 504, .y = 80, .available = 1, .sprite_location = 32},
	{.x = 512, .y = 80, .available = 1, .sprite_location = 33},
	{.x = 520, .y = 80, .available = 1, .sprite_location = 34},
	{.x = 528, .y = 80, .available = 1, .sprite_location = 35},
	{.x = 496, .y = 72, .available = 1, .sprite_location = 36},
	{.x = 520, .y = 72, .available = 1, .sprite_location = 37},
	{.x = 504, .y = 64, .available = 1, .sprite_location = 38},
	{.x = 512, .y = 64, .available = 1, .sprite_location = 39}
};
