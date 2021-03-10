// Alyssa Feagans
// 3/9/21
// 3D Tic-Tac-Toe terminal game
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>

#define NUM_BOARDS 9
#define BOARD_SIZE 9

// Game board states
#define X 9
#define O 1
#define TIE INT_MAX
#define INCOMPLETE INT_MIN // Game still in progress

// Waits for user to hit enter so tutorial doesnt give a huge wall of text at once.
void checkpoint(void)
{
	printf("\nPress enter to continue\n\n");
	int enter = 0;
	while (enter != '\r' && enter != '\n') { enter = getchar(); }
}

// Fill game board with all INT_MIN = empty.
void empty_board(char board[NUM_BOARDS][BOARD_SIZE], int board_states[NUM_BOARDS])
{
	for (int i = 0; i < NUM_BOARDS; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = '\0';
		}
		board_states[i] = INCOMPLETE;
	}
}

// Prints out blank board with positions filled in.
void print_ref_board()
{
	printf("  Board 0 \t  Board 1 \t  Board 2 \n");
	printf(" 0 | 1 | 2 \t 0 | 1 | 2 \t 0 | 1 | 2 \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" 3 | 4 | 5 \t 3 | 4 | 5 \t 3 | 4 | 5 \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" 6 | 7 | 8 \t 6 | 7 | 8 \t 6 | 7 | 8 \n\n\n\n");

	printf("  Board 3 \t  Board 4 \t  Board 5 \n");
	printf(" 0 | 1 | 2 \t 0 | 1 | 2 \t 0 | 1 | 2 \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" 3 | 4 | 5 \t 3 | 4 | 5 \t 3 | 4 | 5 \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" 6 | 7 | 8 \t 6 | 7 | 8 \t 6 | 7 | 8 \n\n\n\n");

	printf("  Board 6 \t  Board 7 \t  Board 8 \n");
	printf(" 0 | 1 | 2 \t 0 | 1 | 2 \t 0 | 1 | 2 \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" 3 | 4 | 5 \t 3 | 4 | 5 \t 3 | 4 | 5 \n");
	printf("-----------\t-----------\t-----------\n");
	printf(" 6 | 7 | 8 \t 6 | 7 | 8 \t 6 | 7 | 8 \n\n\n\n");
}

// Prints game board out with board headers and lists each board's state.
void print_boards(char board[NUM_BOARDS][BOARD_SIZE], int board_states[NUM_BOARDS])
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
			printf(" %c | %c | %c \t", board[j][0], board[j][1], board[j][2]);
		printf("\n");
		printf("-----------\t-----------\t-----------\n");

		// 2nd row of boards
		for (int j = cur_board; j < cur_board + 3; j++)
			printf(" %c | %c | %c \t", board[j][3], board[j][4], board[j][5]);

		printf("\n");
		printf("-----------\t-----------\t-----------\n");

		// 3rd row of boards
		for (int j = cur_board; j < cur_board + 3; j++)
			printf(" %c | %c | %c \t", board[j][6], board[j][7], board[j][8]);

		printf("\n");
		// Print each board's state if not in progress.
		char board_state1[10], board_state2[10], board_state3[10];

		for (int j = cur_board; j < cur_board + 3; j++)
		{
			if (board_states[j] == X)
			{
				if (j == cur_board)
					strcpy(board_state1, "X WON");

				else if (j == cur_board + 1)
					strcpy(board_state2, "X WON");

				else if (j == max_board)
					strcpy(board_state3, "X WON");
			}

			else if (board_states[j] == O)
			{
				if (j == cur_board)
					strcpy(board_state1, "O WON");

				else if (j == cur_board + 1)
					strcpy(board_state2, "O WON");

				else if (j == max_board)
					strcpy(board_state3, "O WON");
			}

			else if (board_states[j] == TIE)
			{
				if (j == cur_board)
					strcpy(board_state1, " TIE ");

				else if (j == cur_board + 1)
					strcpy(board_state2, " TIE ");

				else if (j == max_board)
					strcpy(board_state3, " TIE ");
			}

			// If board still in progress, char will be empty.
			else if (board_states[j] == INCOMPLETE)
			{
				if (j == cur_board)
					strcpy(board_state1, "");

				else if (j == cur_board + 1)
					strcpy(board_state2, "");

				else if (j == max_board)
					strcpy(board_state3, "");
			}
		}

		// Print line showing each board's current state.
		printf("   %s  \t   %s      \t   %s\n\n\n", board_state1, board_state2, board_state3);
		printf("\n\n");

		// Next 3 boards
		cur_board += 3;
		max_board += 3;
	}
}

// Checks if move is valid. Returns true if valid, false otherwise.
bool valid_move(int move, char board[NUM_BOARDS][BOARD_SIZE], int states[NUM_BOARDS])
{
	int curr_board;
	// Move must be betweem 00 and 88 to be valid.
	if (move < 0 || move > 88)
	{
		printf("Move is not valid position on board.\n");
		return false;
	}

	// To get board from move: (move / 10) % 10
	int dest_board = (move / 10) % 10;

	// To get position: move % 10
	int dest_pos = move % 10;

	// Check if attempting to go to a board that is already finished.
	if (states[dest_board] != INCOMPLETE)
	{
		printf("This board is not playable.\n");
		return false;
	}

	// Check if position already has a marker.
	if (board[dest_board][dest_pos] != '\0')
	{
		printf("This position is not empty.\n");
		return false;
	}
	return true;
}

// Fill board with random values 1 or 0 for testing purposes
int fillBoards(char board[NUM_BOARDS][BOARD_SIZE])
{
	srand(time(NULL));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			// Generate random number 1 to 100
			int num = rand() % 100 + 1;
			// Place an 'O'
			if (num <= 50)
			 	board[i][j] = 'O';

			// Place an 'X'
			else
				board[i][j] = 'X';
		}
	}
}

// Prints out all board values for debugging.
void printBoardValues(char board[NUM_BOARDS][BOARD_SIZE])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			printf("BOARD [%d][%d] = %d\n", i, j, board[i][j]);
}

// Explain the game and show examples.
void tutorial(void)
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

	// For some reason, I the first press enter to continue does not work need an extra.
	int enter = 0;
	while (enter != '\r' && enter != '\n') { enter = getchar(); }

	checkpoint();

	printf(" X | O | O \n");
	printf(" O | X | O \n");
	printf(" O | O | X \n");
	printf("\nPlayer X won game\n\n");

	checkpoint();

	printf("If neither players are able to get 3 in these patterns and the board fills up,\n");
	printf("it is a draw and neither players win.\n");
	printf("This is known as a scratch or cat's game or cat's scratch.\n\n");
	printf(" X | O | X \n");
	printf(" X | O | O \n");
	printf(" O | X | X \n");
	printf("\nCat's scratch game\n");

	checkpoint();

	printf("-------------------------------------------------------------------------------\n");
	printf("3D Tic-Tac-Toe\n");
	printf("-------------------------------------------------------------------------------\n\n");
	printf("3D Tic-Tac-Toe consists of 9 normal Tic-Tac-Toe games played simultaneously.\n");
	printf("Where you place your marker on each board determines what board your\n");
	printf("oppenent will play on next turn.\n\n");

	checkpoint();

	printf("For example, if player X places their marker on position 4\n");
	printf("then player O will be forced to play on board 4\n");
	printf("(assuming board 4 is not yet full and that game is unfinished).\n\n");

	printf(" 0 | 1 | 2 \n");
	printf("-----------\n");
	printf(" 3 | 4 | 5 \n");
	printf("-----------\n");
	printf(" 6 | 7 | 8 \n\n");

	checkpoint();

	printf("If a player marks the position of the board that is currently being played on,\n");
	printf("the opponent will continue to play on that board as normal.\n\n");

	checkpoint();

	printf("If a player places marker on a position where that board is\n");
	printf("full or has already been won, opponent can choose what board to go to.\n\n");

	checkpoint();

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

	checkpoint();

	printf("-------------------------------------------------------------------------------\n");
	printf("How to win the game:\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("To win the game, a player must win 3 boards in a row, column, or diagonal.\n");
	printf("If neither players have 3 wins in these patterns after filling up all boards,\n");
	printf("the game is a cat's scratch no matter who won more boards.\n\n");

	checkpoint();

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

	checkpoint();

	printf("Ready to play?\n\n");

	checkpoint();
}

// Print head ASCII art.
void print_heads(void)
{
	// Quarter ASCII art by Joan G. Stark and edited.
	printf("\n");
	printf("\n");
	printf("        _.-'~~`~~'-._\n");
	printf("     .'`  B   E   R  `'.\n");
	printf("   / I               T  `\n");
	printf("  /`       .-'~''-.      `;\n");
	printf(" ; L      / `-    ]      Y |\n");
	printf(";        />  `.  -.|       ;\n");
	printf("|       /_     '-.__)      |\n");
	printf("|        |-  _.' l |       |\n");
	printf(";        `~~;     ll       ;\n");
	printf(";  INGODWE /      Il)P     ;\n");
	printf(" -   TRUST '.___.-'`''    /\n");
	printf("  `                      /`\n");
	printf("    ' ._   1 9 9 7   _.'\n");
	printf("    	`'-..,,,..-'`\n");
	printf("\n");
	printf("\n");
}

// Returns true if user selected correct side of coin it randomly lands on.
bool coin_flip(int user_selection)
{
	int coin;
	srand(time(NULL));
	rand();
	int rando = rand() % 100 + 1;

	// Coin is heads
	if (rando <= 49)
	{
		coin = 0;
		printf("\n\nCoin is HEADS\n");
		print_heads();
	}

	// Coin is tails
	else
	{
		coin = 1;
		printf("\nCoin is TAILS\n");
	}

	// Return true if correctly guessed, false if not.
	return (coin == user_selection);
}

// Start a new game with empty board.
// Returns board
void start_game(char board[NUM_BOARDS][BOARD_SIZE])
{
	int user_selection = 0;
	bool coin = true;
	bool playerX = false;
	bool winner = false;
	int states[NUM_BOARDS];
	int turn = 1;
	char marker;
	printf("Starting a new game...\n\n");
	empty_board(board, states);
	while(coin)
	{
		printf("Pick heads or tails for coin flip that decides who will go first.\n");
		printf("0: Heads\n");
		printf("1: Tails\n");
		scanf("%d", &user_selection);
		sleep(2);

		if (user_selection == 0 || user_selection == 1)
		{
			if (coin_flip(user_selection))
			{
				playerX = true;
				marker = 'X';
				printf("\nYou go first. You are player X.\n\n");
			}

			else
			{
				playerX = false;
				marker = 'O';
				printf("\nYou go second. You are player O.\n\n");
				break;
			}
			coin = false;
		}
	}

	// Continue until there is a winner or a tie.
	while(!winner)
	{

		// If user is player X just started the game they can pick any position on any board.
		if (playerX && turn == 1)
		{
			print_boards(board, states);
			printf("What board and position would you like to place an X?\n");
			printf("Ex: board 4 position 6 you would enter 46\n");
			scanf("%d", &user_selection);

			// Make sure this is valid move, if it is, add to board.
			if (valid_move(user_selection, board, states))
				board[(user_selection / 10) % 10][user_selection % 10] = marker;
			else
				continue;
		}

		// Alternate turns between player and bot.
		// PlayerX goes before bot
		else if (playerX)

		// Bot will make move. Check if turn == 1.

		// PlayerO goes after bot
		if (!playerX)

		// Add to turn counter. A turn is full rotation back to player.
		turn++;
		continue;

	}
}

int main(void)
{
	// Create board will be initialized with trash values.
	char board[NUM_BOARDS][BOARD_SIZE];
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
		printf("1: Load a saved game\n");
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
		{
			start_game(board);
		}

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
	return 1;
}
