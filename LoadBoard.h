#pragma once
#include "StoreBoard.h"

//declaration of functions
void LoadBoard(char* filename, Board board);
void insertBufferToRow(BYTE* buffer, Board board, int rowNum);
