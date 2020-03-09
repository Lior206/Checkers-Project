#pragma once
#include "FindSingleSourceMoves.h"

// declaration of list
typedef struct struct_SingleSourceMovesListCell {

	checkersPos* position;
	unsigned short captures;
	struct struct_SingleSourceMovesListCell* next;

}SingleSourceMovesListCell;

typedef struct struct_SingleSourceMovesList {

	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;

}SingleSourceMovesList;


//declaration of function
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
SingleSourceMovesList* RecFindSingleSourceOptimalMove(SingleSourceMovesTreeNode* treeNode);
SingleSourceMovesList* createEmptySourceMovesList();
SingleSourceMovesListCell* createSingleSourceMovesListNode(SingleSourceMovesTreeNode* treeNode);
void insertNodeToHead(SingleSourceMovesList* lst, SingleSourceMovesListCell* node);
SingleSourceMovesList* FindTheOptimalList(SingleSourceMovesList* lst1, SingleSourceMovesList* lst2);
void freeSingeSourceMovesList(SingleSourceMovesList* lst);
void freeSingleSourceMovesListNode(SingleSourceMovesListCell* node);