#include "FindAllPossiblePlayerMoves.h"

//implementaion of function
MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player)
{
	MultipleSourceMovesList *res = createEmptyMultipleSourceMovesList();
	MultipleSourceMovesListCell *node;
	checkersPos currentPosition;
	SingleSourceMovesTree* tree;

	int i, j;
	//loops for travel on the board
	for (i = START; i < BOARD_SIZE; i++)
		for (j = START; j < BOARD_SIZE; j++) {
			//get the position from i,j
			currentPosition.row = convToLett(i);
			currentPosition.col = convToNum(j);
			//if the position has the wanted player in it, create moves tree
			if (player == checkPos(currentPosition, board))
			{
				tree = FindSingleSourceMoves(board, &currentPosition);
				if (tree->source->next_move[0] != NULL || tree->source->next_move[1] != NULL) {
					//create a new node that contains the optimal move from the tree
					node = createMultipleSourceMovesListCell(FindSingleSourceOptimalMove(tree));
					insertToTail(res, node);
				}
				//free the tree
				freeTree(tree);
			}

		}

	return res;
}

//function to create empty list of lists
MultipleSourceMovesList *createEmptyMultipleSourceMovesList()
{
	MultipleSourceMovesList* res = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	checkAlloc(res, "faild to allocate MultipleSourceMovesList memmory");
	res->head = NULL;
	res->tail = NULL;
	return res;
}

//function to insert node to end of list
void insertToTail(MultipleSourceMovesList *lst, MultipleSourceMovesListCell *node)
{
	MultipleSourceMovesListCell *tmp;
	if (lst->head == NULL) {
		lst->head = node;
		lst->tail = node;
	}
	else {
		tmp = lst->tail;
		lst->tail = node;
		tmp->next = lst->tail;
	}
}

//function to create list node 
MultipleSourceMovesListCell* createMultipleSourceMovesListCell(SingleSourceMovesList* lst)
{

	MultipleSourceMovesListCell* res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	checkAlloc(res, "faild to allocate MultipleSourceMovesListCell memmory");

	res->single_source_moves_list = lst;
	res->next = NULL;

	return res;
}

//function to free tree
void freeTree(SingleSourceMovesTree* tree)
{
	recFreeTreeNodes(tree->source);
	free(tree);
}

//function to free treeNode
void recFreeTreeNodes(SingleSourceMovesTreeNode* node)
{
	if (node) {
		recFreeTreeNodes(node->next_move[0]);
		recFreeTreeNodes(node->next_move[1]);

		free(node->pos);
		free(node);
	}
}
