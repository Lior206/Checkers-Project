#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//describe checkerPos content
#define EMPTY_POS ' '
#define PLAYER1 'T'
#define PLAYER2 'B'

//describe importent values in the program
#define BOARD_SIZE 8
#define START 0

//describe dierections of movement
#define RIGHT 1
#define LEFT 0

//describe positions on the board
#define FIRST_ROW 'A'
#define LAST_ROW 'H'
#define FIRST_COL '1'
#define LAST_COL '8'

#define TRUE 1
#define FALSE 0

#define INVALID_ROW '0'
#define INVALID_COL '0'

//checkers struct
typedef struct _checkersPos {
	char row, col;
}checkersPos;

//Board array type
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

//Player type varible
typedef unsigned char Player;

typedef int Bool;

//TreeNode struct
typedef struct _SingleSourceMovesTreeNode {
	Board board;
	checkersPos *pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode *next_move[2];
}SingleSourceMovesTreeNode;

//Tree struct
typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;


//declaration of functions
SingleSourceMovesTree* emptyTree();
SingleSourceMovesTreeNode* createTreeNode(Board board, checkersPos src, unsigned short totalCaptures);
void checkAlloc(void* pointer, char* str);
void copyBoards(Board des, Board src);
char convToLett(int num);
char convToNum(int num);
SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);
SingleSourceMovesTreeNode* RecFindSingleSourceMoves(Player player, checkersPos src, Board currentBoard, unsigned short totalCaptures, void(*prevTypeOfMove)(Board, checkersPos, checkersPos, checkersPos));
checkersPos FindnextMove(Board newBoard, Board originalBoard, checkersPos src, Player player, unsigned short direction, unsigned short *totalCaptures, void(**prevTypeOfMove)(Board, checkersPos, checkersPos, checkersPos));
void updateBoard(Player player, Board newBoard, Board originalBoard, checkersPos src, checkersPos closePositionInDirection, checkersPos farPositionInDirection, void(*TypeOfMove)(Board, checkersPos, checkersPos, checkersPos));
Player checkPos(checkersPos src, Board board);
checkersPos getNextPositionInDirection(checkersPos src, Player player, unsigned short direction);
Bool validPos(checkersPos pos);