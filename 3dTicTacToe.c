// Alyssa Feagans
// 3/9/21
// 3D Tic-Tac-Toe
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_BOARDS 9
#define BOARD_SIZE 9

void printBoards(int board[NUM_BOARDS][BOARD_SIZE])
{
	int cur_board = 0;
	int max_board = 2;

	for (int i = 0; i < 3; i++)
	{
		// Print 3 boards together
		// Print board headers
		printf("  Board %d \t  Board %d \t  Board %d \n", cur_board, cur_board + 1, max_board);

		// 1st row of boards
		for (int j = cur_board; j < cur_board + 3; j++)
			printf(" %d | %d | %d \t", board[j][0], board[j][1], board[j][2]);

		printf("\n");

		// 2nd row of boards
		for (int j = cur_board; j < cur_board + 3; j++)
			printf(" %d | %d | %d \t", board[j][3], board[j][4], board[j][5]);

		printf("\n");

		// 3rd row of boards
		for (int j = cur_board; j < cur_board + 3; j++)
			printf(" %d | %d | %d \t", board[j][6], board[j][7], board[j][8]);

		printf("\n\n");
		// Next 3 boards
		cur_board += 3;
		max_board += 3;
	}
}

// Fill board with random values 1 or 0 for testing purposes
int fillBoards (int board[NUM_BOARDS][BOARD_SIZE])
{
	srand(time(0));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			// Generate random number 1 to 100
			int num = (rand() % 100) + 1;
			// Place an 'O'
			if (num <= 50)
			 	board[i][j] = 0;

			// Place an 'X'
			else
				board[i][j] = 1;

		}
	}
}

void printBoardValues(int board[NUM_BOARDS][BOARD_SIZE])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("BOARD [%d][%d] = %d\n", i, j, board[i][j]);
		}
	}
}

int main(void)
{
	// Create board will be initialized with trash values.
	int board[NUM_BOARDS][BOARD_SIZE];
	printf("\nHello! Welcome to 3D Tic-Tac-Toe\n");

	fillBoards(board);
	printBoards(board);
	return 1;
}
