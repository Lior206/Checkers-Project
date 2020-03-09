#include "playGame.h"

//function to run the game 
void playGame(Board board, Player startingPlayer)
{
	Bool gameState = GAME_ON;
	Player currPlayer = startingPlayer;

	printBoard(board);
	//loop to run the game
	while (gameState) {
		//calling the Turn function
		Turn(board, currPlayer, &gameState);
		printBoard(board);
		//condition to switch between players
		if (currPlayer == PLAYER1)
			currPlayer = PLAYER2;
		else
			currPlayer = PLAYER1;
	}
}

//function to print the board
void printBoard(Board board) {

	int i;

	for (i = START; i < BOARD_SIZE * 2 + 3; i++) {
		if (i == 1)
			printLineOfCols();
		else if (i % 2 == 0)
			printBetweenLines();
		else
			printLine(board, i / 2 - 1);

	}
	printf("\n");


}

//function to print between lines
void printBetweenLines() {
	int i;

	for (i = START; i < BOARD_SIZE * 2 + 3; i++) {
		if (i % 2 == 0)
			printf("+");
		else
			printf("-");
	}
	printf("\n");
}

//function to print line of cols
void printLineOfCols() {
	int i;
	char col;
	printf("+ ");

	for (i = START, col = FIRST_COL; i < BOARD_SIZE * 2 + 1; i++) {
		if (i % 2 == 0)
			printf("|");
		else {
			printf("%c", col);
			col++;
		}
	}

	printf("\n");
}

//function to print the content of a row
void printLine(Board board, int row) {
	int i;
	int col;

	printf("|%c|", convToLett(row));
	for (col = START, i = START; i < BOARD_SIZE * 2; i++) {
		if (i % 2 == 0) {
			printf("%c", board[row][col]);
			col++;
		}
		else
			printf("|");
	}

	printf("\n");
}
