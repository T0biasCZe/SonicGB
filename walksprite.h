//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_W0_H
#define METASPRITE_W0_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define W0_TILE_ORIGIN 0
#define W0_TILE_H 16
#define W0_WIDTH 32
#define W0_HEIGHT 32
#define W0_TILE_COUNT 16
#define W0_PIVOT_X 16
#define W0_PIVOT_Y 16
#define W0_PIVOT_W 32
#define W0_PIVOT_H 32

BANKREF_EXTERN(W0)

extern const palette_color_t walk_palettes[8];
extern const uint8_t walk_tiles[16][208];
extern const uint8_t walk_tiles_red[16][96];

extern const metasprite_t* const walk_metasprites[16];
extern const metasprite_t* const walk_metasprites_red[16];
#endif