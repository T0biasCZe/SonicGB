#define numberofbadniks 3
extern typedef enum BadnikType{bmotobug, bfish, woomy}BadnikType;
extern struct Badnik{
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
extern struct Badnik badnikData[];
