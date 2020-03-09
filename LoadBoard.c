#include "LoadBoard.h"
//function to copy board for the file content
void LoadBoard(char* filename, Board board) {

	BYTE buffer[2]; //buffer array
	int i; //index
		   //open file for reading
	FILE* f = fopen(filename, "rb");
	checkAlloc(f, "could not open file for read");
	//loop for writing to the board
	for (i = START; i < BOARD_SIZE; i++) {
		//read values from file into buffer
		fread(buffer, sizeof(BYTE), 2, f);
		insertBufferToRow(buffer, board, i);
	}

	fclose(f);
}

//function to insert buffer data to the board for each row number
void insertBufferToRow(BYTE* buffer, Board board, int rowNum) {

	int byteIndex, i;
	BYTE cell;
	//loop to insert values to the board
	for (i = START; i < BOARD_SIZE; i++) {
		byteIndex = i / 4;
		cell = (buffer[byteIndex] << (2 * (i % 4)));
		cell = cell >> 6;
		//distribute to cases
		if (cell == PLAYER1_BIN)
			board[rowNum][i] = PLAYER1;
		else if (cell == PLAYER2_BIN)
			board[rowNum][i] = PLAYER2;
		else
			board[rowNum][i] = EMPTY_POS;
	}
}
