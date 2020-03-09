#include "StoreBoard.h"
//function to storge bits in the file 
void StoreBoard(Board board, char* filename) {

	int i, j; //indexes
	BYTE byte = 0; //buffer
	checkersPos cell;
	//open file for writing
	FILE* f = fopen(filename, "wb");
	checkAlloc(f, "faild to open file");

	//loops to run on the board
	for (i = START; i < BOARD_SIZE; i++) {
		for (j = START; j < BOARD_SIZE; j++) {
			cell.row = convToLett(i);
			cell.col = convToNum(j);
			//write binary value into buffer
			updateByte(&byte, j, checkPos(cell, board));
			if (j == 3) {
				//write the buffer into the file
				fwrite(&byte, sizeof(BYTE), 1, f);
				byte = 0;
			}
		}
		//write the buffer into the file
		fwrite(&byte, sizeof(BYTE), 1, f);
		byte = 0;
	}
	//close the file
	fclose(f);
}

//function to update the bye buffer
void updateByte(BYTE* desByte, int pos, Player cell) {

	BYTE srcByte;
	//distribute to cases
	if (cell == PLAYER1)
		srcByte = PLAYER1_BIN;
	else if (cell == PLAYER2)
		srcByte = PLAYER2_BIN;
	else
		srcByte = EMPTY_CELL_BIN;

	srcByte = srcByte << (6 - 2 * (pos % 4));
	//write to the buffer by pointer
	(*desByte) |= srcByte;
}