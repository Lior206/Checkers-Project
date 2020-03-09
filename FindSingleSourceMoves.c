#include "FindSingleSourceMoves.h"

//function to make a capture move
void capture(Board board, checkersPos src, checkersPos closePositionInDirection, checkersPos farPositionInDirection) {
	board[farPositionInDirection.row - FIRST_ROW][farPositionInDirection.col - FIRST_COL] = checkPos(src, board);
	board[closePositionInDirection.row - FIRST_ROW][closePositionInDirection.col - FIRST_COL] = EMPTY_POS;
	board[src.row - FIRST_ROW][src.col - FIRST_COL] = EMPTY_POS;
}

//function to make a move without capture
void moveWithoutCapture(Board board, checkersPos src, checkersPos closePositionInDirection, checkersPos farPositionInDirection) {
	board[closePositionInDirection.row - FIRST_ROW][closePositionInDirection.col - FIRST_COL] = checkPos(src, board);
	board[src.row - FIRST_ROW][src.col - FIRST_COL] = EMPTY_POS;
}

//implementaion of function to create empty tree
SingleSourceMovesTree* emptyTree()
{
	SingleSourceMovesTree* res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	checkAlloc(res, "faild to allocate SingleSourceMovesTree memmory");
	res->source = NULL;
	return res;
}

//implementaion of function to create TreeNode
SingleSourceMovesTreeNode* createTreeNode(Board board, checkersPos src, unsigned short totalCaptures)
{
	SingleSourceMovesTreeNode* res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAlloc(res, "faild to allocate SingleSourceMovesTreeNode memmory");
	copyBoards(res->board, board);

	res->pos = (checkersPos*)malloc(sizeof(checkersPos));
	checkAlloc(res, "faild to allocate checkersPos memmory");
	res->pos->row = src.row;
	res->pos->col = src.col;

	res->total_captures_so_far = totalCaptures;
	res->next_move[0] = NULL;
	res->next_move[1] = NULL;
	return res;
}

//implementaion of function to check dinamic allocation
void checkAlloc(void* pointer, char* str)
{
	if (!pointer)
	{
		printf(str);
		exit(-1);
	}
}

//implementaion of function to copy boards
void copyBoards(Board des, Board src)
{
	int i, j;
	for (i = START; i < BOARD_SIZE; i++)
		for (j = START; j < BOARD_SIZE; j++)
			des[i][j] = src[i][j];
}

//implementaion of function to convert number to char position
char convToLett(int num)
{
	return num + FIRST_ROW;
}

//implementaion of function to convert number to char position
char convToNum(int num)
{
	num++;
	return num + '0';
}


SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src) {

	Player player = checkPos(*src, board);
	if (player == EMPTY_POS)
		return NULL;
	else
	{
		SingleSourceMovesTree* res = emptyTree();
		res->source = RecFindSingleSourceMoves(player, *src, board, 0, NULL);
		return res;
	}

}

//recursive function to create tree
SingleSourceMovesTreeNode* RecFindSingleSourceMoves(Player player, checkersPos src, Board currentBoard,
	unsigned short totalCaptures, void(*prevTypeOfMove)(Board, checkersPos, checkersPos, checkersPos)) {

	//recursive return
	if (!validPos(src))
		return NULL;

	else {
		//create node for current situation
		SingleSourceMovesTreeNode* newNode = createTreeNode(currentBoard, src, totalCaptures);
		Board rightBoard;
		Board leftBoard;

		void(*rightTypeOfMove)(Board, checkersPos, checkersPos, checkersPos) = prevTypeOfMove;
		void(*leftTypeOfMove)(Board, checkersPos, checkersPos, checkersPos) = prevTypeOfMove;

		unsigned short leftCaptures = totalCaptures;
		unsigned short rightCaptures = totalCaptures;

		//check the next move for left and right side, update type of move and total captures
		checkersPos leftMove = FindnextMove(leftBoard, currentBoard, src, player, LEFT, &leftCaptures, &leftTypeOfMove);
		checkersPos rightMove = FindnextMove(rightBoard, currentBoard, src, player, RIGHT, &rightCaptures, &rightTypeOfMove);

		//recursive calls
		newNode->next_move[0] = RecFindSingleSourceMoves(player, leftMove, leftBoard, leftCaptures, leftTypeOfMove);
		newNode->next_move[1] = RecFindSingleSourceMoves(player, rightMove, rightBoard, rightCaptures, rightTypeOfMove);

		return newNode;
	}
}

//function to return the next position of player
checkersPos FindnextMove(Board newBoard, Board originalBoard, checkersPos src,
	Player player, unsigned short direction, unsigned short *totalCaptures, void(**prevTypeOfMove)(Board, checkersPos, checkersPos, checkersPos)) {

	checkersPos res;
	if (*prevTypeOfMove == moveWithoutCapture) {
		res.row = INVALID_ROW;
		res.col = INVALID_COL;
	}//already moved by one, cant move again
	else
	{
		/*check the two positions for current side
		example: for A1, 'T'and "LEFT"-  closePositionInDirection will be B2
		and farPositionInDirection will be C3 */
		checkersPos closePositionInDirection = getNextPositionInDirection(src, player, direction);
		checkersPos farPositionInDirection = getNextPositionInDirection(closePositionInDirection, player, direction);

		//distribute to situations for positions
		if (!validPos(closePositionInDirection)) {
			res.row = INVALID_ROW;
			res.col = INVALID_COL;
		}
		else if (checkPos(closePositionInDirection, originalBoard) != player && checkPos(closePositionInDirection, originalBoard) != EMPTY_POS) {

			if (validPos(closePositionInDirection)) {
				//situation of capture move
				if (checkPos(farPositionInDirection, originalBoard) == EMPTY_POS) {
					updateBoard(player, newBoard, originalBoard, src, closePositionInDirection, farPositionInDirection, capture);
					*prevTypeOfMove = capture;
					(*totalCaptures)++;
					res = farPositionInDirection;
				}
				else {
					res.row = INVALID_ROW;
					res.col = INVALID_COL;
				}
			}

			else {
				res.row = INVALID_ROW;
				res.col = INVALID_COL;
			}
		}
		else if (checkPos(closePositionInDirection, originalBoard) == EMPTY_POS && *prevTypeOfMove == NULL) {
			//situation of move without capture
			updateBoard(player, newBoard, originalBoard, src, closePositionInDirection, farPositionInDirection, moveWithoutCapture);
			*prevTypeOfMove = moveWithoutCapture;
			res = closePositionInDirection;
		}
		else {
			res.row = INVALID_ROW;
			res.col = INVALID_COL;
		}
	}

	return res;
}

//function to update the board for the current situation
void updateBoard(Player player, Board newBoard, Board originalBoard, checkersPos src,
	checkersPos closePositionInDirection, checkersPos farPositionInDirection, void(*TypeOfMove)(Board, checkersPos, checkersPos, checkersPos)) {

	copyBoards(newBoard, originalBoard);
	TypeOfMove(newBoard, src, closePositionInDirection, farPositionInDirection);
}

//funtion to return the checker position value in the board 
Player checkPos(checkersPos src, Board board) {
	int row = (int)(src.row - FIRST_ROW);
	int col = (int)(src.col - FIRST_COL);

	return board[row][col];
}

//funtion to return the next position for the current direction and player
checkersPos getNextPositionInDirection(checkersPos src, Player player, unsigned short direction) {

	checkersPos res;
	//invalid source position
	if (!validPos(src)) {
		res.row = INVALID_ROW;
		res.col = INVALID_COL;
	}

	//distribute to cases for the player and direction
	if (player == PLAYER1) {
		res.row = src.row + 1;
		if (direction == RIGHT)
			res.col = src.col - 1;
		else
			res.col = src.col + 1;
	}
	else {
		res.row = src.row - 1;
		if (direction == RIGHT)
			res.col = src.col + 1;
		else
			res.col = src.col - 1;
	}

	return res;
}

//checks if the position is valid
Bool validPos(checkersPos pos) {
	return (pos.row >= FIRST_ROW && pos.row <= LAST_ROW && pos.col >= FIRST_COL && pos.col <= LAST_COL);
}