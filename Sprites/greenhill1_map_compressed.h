#include <gb/cgb.h>
#include <gb/gb.h>
//#include "colours.c"
extern const uint8_t map_width; //in TILES
extern const uint16_t sign_position; //in PIXELS
//array for the decompressed tiles
extern uint8_t greenmapPLN0[2340];
extern uint8_t greenmapPLN1[2340];
#define greenmap greenmapPLN0
extern const unsigned char greenmapPLN0_compressed[];
extern const unsigned char greenmapPLN1_compressed[];
extern const palette_color_t green_palette[32];


















