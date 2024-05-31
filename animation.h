extern typedef enum {stand,walk,roll}animace_typ;
extern typedef enum {pravo,levo}animace_dir;

extern void animate(animace_typ animation,uint16_t x, uint16_t y, uint8_t vpravo, int16_t speed_x);