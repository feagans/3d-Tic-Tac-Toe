// Alyssa Feagans
// 3/9/21
// 3D Tic-Tac-Toe
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

// Explain the game and show examples.
void tutorial()
{
	printf("\nLoading game tutorial...\n\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("Basic Tic-Tac-Toe\n");
	printf("-------------------------------------------------------------------------------\n\n");
	printf("Most people know how to play the classic game of Tic-Tac-Toe.\n");
	printf("It is a two-player game.\n");
	printf("The first player is known as X and the second player is O.\n");
	printf("Players alternate placing Xs and Os on a 3x3 game board\n");
	printf("until a player gets 3 in a row, column, or diagonal.\n");
	printf("X always goes first.\n\n");
	printf(" X | O | O \n");
	printf(" O | X | O \n");
	printf(" O | O | X \n");
	printf("\nPlayer X won game\n\n");
	printf("If neither players are able to get 3 in these patterns and the board fills up,\n");
	printf("it is a draw and neither players win.\n");
	printf("This is known as a scratch or cat's game or cat's scratch.\n\n");
	printf(" X | O | X \n");
	printf(" X | 0 | O \n");
	printf(" O | X | X \n");
	printf("\nCat's scratch game\n");

	printf("-------------------------------------------------------------------------------\n");
	printf("3D Tic-Tac-Toe\n");
	printf("-------------------------------------------------------------------------------\n\n");
	printf("3D Tic-Tac-Toe consists of 9 normal Tic-Tac-Toe games played simultaneously.\n");
	printf("Where you place your marker on each board determines what board your\n");
	printf("oppenent will play on next turn.\n\n");

	printf("For example, if player X places their marker on position 4\n");
	printf("then player 0 will be forced to play on board 4\n");
	printf("(assuming board 4 is not yet full and that game is unfinished).\n\n");

	printf(" 0 | 1 | 2 \n");
	printf(" 3 | 4 | 5 \n");
	printf(" 6 | 7 | 8 \n\n");


	printf("If the board that is currently being played on's position\n");
	printf("is marked, opponent will continue to play on that board as normal.\n\n");


	printf("In the case where a player places marker on a position where that board is\n");
	printf("full or has already been won:\n\n");
	printf("  Board 0 \t  Board 1 \t  Board 2 \n");
	printf("   |   | X \t   |   |   \t   |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf("   |   |   \t   |   |   \t O |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf("   |   |   \t   |   |   \t O |   |   \n\n\n\n");

	printf("  Board 3 \t  Board 4 \t  Board 5 \n");
	printf("   |   | X \t O |   |   \t   |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" O | X |   \t X |   |   \t   |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" X |   |   \t   |   |   \t   |   |   \n");
	printf("   X WON  \t          \t          \n\n\n");

	printf("  Board 6 \t  Board 7 \t  Board 8 \n");
	printf("   |   |   \t   |   |   \t   |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf("   | O |   \t X |   |   \t   |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf("   |   |   \t   |   |   \t   |   |   \n\n\n\n");

	printf("Board 3 has been won by player X.\n");
	printf("Player X places marker on Board 7 in position 3.\n");
	printf("This would normally force player O to play on board 3.\n");
	printf("However, since this board has been won, player O may pick any\n");
	printf("board to play on. This is a bad move by player X since player O\n");
	printf("can choose to play on board 2 in position 0 and win that board.\n");


	printf("-------------------------------------------------------------------------------\n");
	printf("How to win the game:\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("To win the game, a player must win 3 boards in a row, column, or diagonal.\n");
	printf("If neither players have 3 wins in these patterns,\n");
	printf("the entire game is a cat's scratch no matter who won more boards.\n\n");

	printf("  Board 0 \t  Board 1 \t  Board 2 \n");
	printf("   |   | X \t O | X |   \t O |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf("   |   | X \t   |   |   \t O |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf("   |   | X \t   |   |   \t O |   |   \n");
	printf("   X WON  \t          \t   O WON    \n\n\n");

	printf("  Board 3 \t  Board 4 \t  Board 5 \n");
	printf("   |   | X \t O |   |   \t   |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" O | X |   \t X |   |   \t   |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" X |   |   \t O |   |   \t   |   |   \n");
	printf("   X WON  \t          \t          \n\n\n");

	printf("  Board 6 \t  Board 7 \t  Board 8 \n");
	printf("   | O |   \t   |   |   \t   |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf("   | O |   \t X |   |   \t   |   |   \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" X | X | X \t O |   |   \t O |   |   \n");
	printf("   X WON   \t          \t             \n\n\n");

	printf("X has won boards 0 & 3 & 6.\n");
	printf("These wins are in a column, thus X wins the entire game.\n\n");

	printf("Ready to play?\n\n");
}

// Prints out all board values for debugging.
void printBoardValues(int board[NUM_BOARDS][BOARD_SIZE])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			printf("BOARD [%d][%d] = %d\n", i, j, board[i][j]);
}

int main(void)
{
	// Create board will be initialized with trash values.
	int board[NUM_BOARDS][BOARD_SIZE];
	int user_selection = 0;
	bool menu = true;

	printf("\nHello! Welcome to 3D Tic-Tac-Toe.\n");
	printf("A classic Tic-Tac-Toe game with a twist!\n");
	printf("Created by Alyssa Feagans.\n\n");

	while(menu)
	{
		// Main Menu
		printf("Menu Selection\n");
		printf("----------------------------------------\n");
		printf("0: View a tutorial on how to play\n");
		printf("1: Continue game in progress\n");
		printf("2: Start a new game\n");
		printf("3: Quit game\n");
		printf("----------------------------------------\n");

		printf("\nPlease select an option from the menu by typing the corresponding number.\n");
		scanf("%d", &user_selection);

		// Show tutorial
		if (user_selection == 0)
		{
			tutorial();
			continue;
		}

		// Continue saved game
		else if (user_selection == 1)
		{
			printf("Loading saved game...\n");
		}
		// Start new game
		else if (user_selection == 2)
			printf("Starting a new game...\n");

		// Exit program
		else if (user_selection == 3)
		{
			// eventually will save game data if in progress
			printf("Exiting game. Thanks for playing! :)\n");
			exit(0);
		}

		// User selection not valid.
		else
			printf("Please enter a valid menu selection number.\n");
	}

	fillBoards(board);
	printBoards(board);
	return 1;
}
