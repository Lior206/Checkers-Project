#include "FindSingleSourceOptimalMove.h"


//implementaion of function
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) {

	return RecFindSingleSourceOptimalMove(moves_tree->source);
}

//recursive function
SingleSourceMovesList* RecFindSingleSourceOptimalMove(SingleSourceMovesTreeNode* treeNode) {

	SingleSourceMovesList* res;
	SingleSourceMovesListCell* newListNode;

	if (treeNode == NULL) {
		res = createEmptySourceMovesList();
	}
	else {

		newListNode = createSingleSourceMovesListNode(treeNode);

		//choose the optimal list from the two of the next moves and free the other one
		res = FindTheOptimalList(RecFindSingleSourceOptimalMove(treeNode->next_move[0]),
			RecFindSingleSourceOptimalMove(treeNode->next_move[1]));

		//insert the current move to the wanted list
		insertNodeToHead(res, newListNode);
	}

	return res;
}

//function to create empty list
SingleSourceMovesList* createEmptySourceMovesList() {

	SingleSourceMovesList* res = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkAlloc(res, "faild to allocate SingleSourceMovesList memmory");
	res->head = NULL;
	res->tail = NULL;
	return res;
}

//function to create the list
SingleSourceMovesListCell* createSingleSourceMovesListNode(SingleSourceMovesTreeNode* treeNode) {

	SingleSourceMovesListCell* res = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkAlloc(res, "faild to allocate SingleSourceMovesListCell memmory");

	res->position = (checkersPos*)malloc(sizeof(checkersPos));
	checkAlloc(res->position, "faild to allocate checkersPos memmory");

	res->position->row = treeNode->pos->row;
	res->position->col = treeNode->pos->col;
	res->captures = treeNode->total_captures_so_far;
	res->next = NULL;

	return res;
}

//function to compare lists for the number of captures
SingleSourceMovesList* FindTheOptimalList(SingleSourceMovesList* lst1, SingleSourceMovesList* lst2) {

	// if one of the lists are empty, return the other one (if the two of them are empty return lst2)
	if (lst1->tail == NULL) {
		freeSingeSourceMovesList(lst1);
		return lst2;
	}
	else if (lst2->tail == NULL) {
		freeSingeSourceMovesList(lst2);
		return lst1;
	}

	else {
		//check which list is the optimal one, if the lists are equal, choose randomly
		if (lst1->tail->captures > lst2->tail->captures) {
			freeSingeSourceMovesList(lst2);
			return lst1;
		}
		else if (lst1->tail->captures < lst2->tail->captures) {
			freeSingeSourceMovesList(lst1);
			return lst2;
		}
		else {
			if (rand() % 2) {
				freeSingeSourceMovesList(lst2);
				return lst1;
			}
			else {
				freeSingeSourceMovesList(lst1);
				return lst2;
			}
		}
	}
}


//function to insert node to the head of the list
void insertNodeToHead(SingleSourceMovesList* lst, SingleSourceMovesListCell* node) {

	node->next = lst->head;
	lst->head = node;

	if (lst->tail == NULL)
		lst->tail = node;
}

//function to free list
void freeSingeSourceMovesList(SingleSourceMovesList* lst) {

	SingleSourceMovesListCell* currentNode = lst->head;
	SingleSourceMovesListCell* prevNode = NULL;

	while (currentNode) {
		freeSingleSourceMovesListNode(prevNode);
		prevNode = currentNode;
		currentNode = currentNode->next;
	}
	freeSingleSourceMovesListNode(prevNode);

	free(lst);
}

//function to free listNode
void freeSingleSourceMovesListNode(SingleSourceMovesListCell* node) {
	if (node == NULL)
		return;
	free(node->position);
	free(node);
}