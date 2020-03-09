#include "Turn.h"

//function of the turn of the current player
void Turn(Board board, Player player, Bool* gameState)
{
	//calling the function to find the list of turns
	MultipleSourceMovesList* movesList = FindAllPossiblePlayerMoves(board, player);

	//if the list is empty (the player is blocked) the game is over
	if (movesList->head == NULL)
		*gameState = GAME_OFF;
	else {
		//find the best list move from the list of turns
		SingleSourceMovesList* bestMove = FindBestMove(movesList);
		//pointers to run on the best list
		SingleSourceMovesListCell* currentNode = bestMove->head;
		SingleSourceMovesListCell* prevNode = NULL;

		//printing for user each turn
		if (player == PLAYER1)
			printf("player TOP_DOWN's turn\n");
		else
			printf("player BOTTOM_UP's turn\n");

		//loop to run on the best list
		while (currentNode) {
			//printing the first position
			printf("%c%c", currentNode->position->row, currentNode->position->col);
			if (currentNode != bestMove->tail)
				printf("->");
			//updating board
			putPlayerInPosition(board, *(currentNode->position), player);

			//distribute to cases
			if (prevNode)
				putPlayerInPosition(board, *(prevNode->position), EMPTY_POS);

			if (currentNode->captures > 0)
				putPlayerInPosition(board, FindMiddlePosition(prevNode->position, currentNode->position), EMPTY_POS);

			//keep run on the best list bye changing the pointers
			prevNode = currentNode;
			currentNode = currentNode->next;
		}
		printf("\n");
		//calling the function to check the situation of the game
		*gameState = checkGame(board);
	}
	printf("\n");
	//free all dynamic memory that allocated 
	freeMultipleSourceMovesList(movesList);
}

//function to find the best move in list
SingleSourceMovesList* FindBestMove(MultipleSourceMovesList *lst)
{
	//pointers to run on the list
	SingleSourceMovesList* res = lst->head->single_source_moves_list;
	MultipleSourceMovesListCell* node = lst->head;

	//loop to run on the list of turns
	while (node)
	{
		//distribute to cases
		if (res->tail->captures < node->single_source_moves_list->tail->captures)
			res = node->single_source_moves_list;
		else if (res->tail->captures == node->single_source_moves_list->tail->captures) {
			if (rand() % 2 == 0)//choose random list between lists with the same capture value
				res = node->single_source_moves_list;
		}
		node = node->next;
	}

	return res;
}

//function to check the situation of the board
Bool checkGame(Board board)
{
	//indexes and bool values
	int i, j;
	Bool found_1 = FALSE, found_2 = FALSE;

	//loops to run on the current board
	for (i = START; i < BOARD_SIZE; i++)
		for (j = START; j < BOARD_SIZE; j++)
		{
			//distribute to cases
			if (i == START && board[i][j] == PLAYER2)
				return GAME_OFF;
			else if (i == BOARD_SIZE - 1 && board[i][j] == PLAYER1)
				return GAME_OFF;
			else if (board[i][j] == PLAYER1)
				found_1 = TRUE;
			else if (board[i][j] == PLAYER2)
				found_2 = TRUE;
		}
	//condition to check if one of the pieces found
	if (found_1 && found_2)
		return GAME_ON;
	else
		return GAME_OFF;
}


//function to free the list of moves
void freeMultipleSourceMovesList(MultipleSourceMovesList* lst) {
	//pointers to run on the list of turns
	MultipleSourceMovesListCell* currentNode = lst->head;
	MultipleSourceMovesListCell* prevNode = NULL;

	//loop for free the each list inside list of turns
	while (currentNode) {
		if (prevNode) {
			freeSingeSourceMovesList(prevNode->single_source_moves_list);
			free(prevNode);
		}
		prevNode = currentNode;
		currentNode = currentNode->next;
	}

	//free the data that didnt freed on the loop
	freeSingeSourceMovesList(prevNode->single_source_moves_list);
	free(prevNode);
	free(lst);
}



//funtion to find the middle position between two cells
checkersPos FindMiddlePosition(checkersPos* prev, checkersPos* curr)
{
	checkersPos res;
	//distribute to cases
	if (prev->col < curr->col)
		res.col = prev->col + 1;
	else
		res.col = curr->col + 1;

	if (prev->row < curr->row)
		res.row = prev->row + 1;
	else
		res.row = curr->row + 1;

	return res;
}

//function for updating the board
void putPlayerInPosition(Board board, checkersPos position, Player player) {

	int row = (int)(position.row - FIRST_ROW);
	int col = (int)(position.col - FIRST_COL);

	board[row][col] = player;
}