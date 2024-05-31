#include <gb/cgb.h>
#include <gb/gb.h>
#define numberofbadniks 3
/*uint16_t badnikdata[][8] = {
	//dead,	max x left,	max x right,	y,	cur x,	direction (Lef/Rig),	type,	slot - motobug
	{0,		21,			42,			8,	42,		0,					0,		20},
	{0,		51,			76,			12,	76,		0,					0,		24},
	//dead,	max y top,	max y bottom,	x,	cur y,	direction (up/down),	type,	slot - roboryba
	{0,		9,			17,			64,	17,		0,					1,		24}
};*/
typedef enum BadnikType{bmotobug, bfish, woomy}BadnikType;
struct Badnik{
    _Bool dead;
    uint16_t max_x_left; //unused for fish
    uint16_t max_x_right; //unused for fish
	uint8_t max_y_top; //unused for motobug
	uint8_t max_y_bottom; //unused for motobug
	//uint16_t x; //unused for motobug
    //uint8_t y; //unused for fish
    uint16_t current_x;
	uint8_t current_y;
    BadnikType type;
    uint8_t slot;
	uint8_t tile;
	_Bool direction;
};
struct Badnik badnikData[] = {
    {.dead = 0, .max_x_left = 168, .max_x_right = 336, .current_y = 72, .current_x = 336, .direction = 0, .type = 0, .slot = 20, .tile = 192},
    {.dead = 0, .max_x_left = 408, .max_x_right = 608, .current_y = 96, .current_x = 608, .direction = 0, .type = 0, .slot = 20, .tile = 192},
	{.dead = 0, .max_y_top = 72, .max_y_bottom = 136, .current_x = 512, .current_y = 148, .direction = 0, .type = 1, .slot = 24, .tile = 196}
};
