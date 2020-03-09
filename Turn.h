#pragma once
#include "FindAllPossiblePlayerMoves.h"

//declaration of functions
void Turn(Board board, Player player, Bool* gameState);
SingleSourceMovesList* FindBestMove(MultipleSourceMovesList *lst);
void freeMultipleSourceMovesList(MultipleSourceMovesList* lst);
void putPlayerInPosition(Board board, checkersPos position, Player player);
checkersPos FindMiddlePosition(checkersPos* prev, checkersPos* curr);
void putPlayerInPosition(Board board, checkersPos position, Player player);
Bool checkGame(Board board);

//state of game values
#define GAME_ON 1
#define GAME_OFF 0
#define TRUE 1
#define FALSE 0
