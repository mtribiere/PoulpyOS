#pragma once

#define VGA_ADDRESS 0xb8000
#define ROWS_COUNT 25
#define COLS_COUNT 80

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#define LIGHT_MAGENTA 0x0D
#define YELLOW_ON_BLACK 0x0E
#define WHITE_ON_BLACK 0x0F

enum ColorPallette{

    WHITE = WHITE_ON_BLACK,
    MAGENTA = LIGHT_MAGENTA,
    YELLOW = YELLOW_ON_BLACK

};



void clearScreen();
void clearLastLine();

void pprint(const char *buf);
void pprintChar(char c);

void changeCurrentColor(enum ColorPallette c);

