#pragma once
#include "Turn.h"

//binary values for each cell
#define EMPTY_CELL_BIN 0x00
#define PLAYER1_BIN 0x01
#define PLAYER2_BIN 0x02

typedef unsigned char BYTE;

//declaration of functions
void StoreBoard(Board board, char* filename);
void updateByte(BYTE* desByte, int pos, Player cell);
