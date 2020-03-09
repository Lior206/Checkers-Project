#pragma once
#include "FindSingleSourceOptimalMove.h"


//listNode struct
typedef struct _multipleSourceMovesListCell {
	SingleSourceMovesList *single_source_moves_list;
	struct _multipleSourceMovesListCell *next;
}MultipleSourceMovesListCell;

//list struct
typedef struct _multipleSourceMovesList {
	MultipleSourceMovesListCell *head;
	MultipleSourceMovesListCell *tail;
}MultipleSourceMovesList;

//declaration of functions
MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player);
MultipleSourceMovesList *createEmptyMultipleSourceMovesList();
void insertToTail(MultipleSourceMovesList *lst, MultipleSourceMovesListCell *node);
MultipleSourceMovesListCell* createMultipleSourceMovesListCell(SingleSourceMovesList* lst);
void freeTree(SingleSourceMovesTree* tree);
void recFreeTreeNodes(SingleSourceMovesTreeNode* node);
