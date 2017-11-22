// Reversi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Function Declarations
void printBoard(char board[][8]);
bool isValidMove(int x, int y, char board[][8]);
bool checkForAdjacentPiece(int x, int y, char board[][8]);
bool checkForClosingPiece(int x, int y, char board[][8]);

// Constants
bool whiteTurn = true;

using namespace std;

int main()
{
	char board[8][8];
	bool endGame = false;
	bool validMove = true;

	// Initialize board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = '-';
		}
	}

	board[3][3] = 'O';
	board[4][4] = 'O';

	board[3][4] = 'X';
	board[4][3] = 'X';

	printBoard(board);

	string coordinate;
	int x, y;

	while (!endGame)
	{
		cout << "Where would you like to place your piece? ";

		while (coordinate.length() != 2 || !validMove)
		{
			cin >> coordinate;

			x = coordinate[0] - 48;
			y = coordinate[1] - 48;

			validMove = isValidMove(x, y, board);

			if (!validMove)
			{
				cout << "Not a valid move!" << endl;
				cout << "Where would you like to place your piece? ";
			}
		}

		if (whiteTurn)
		{
			board[x][y] = 'O';
			whiteTurn = false;
		}
		else
		{
			board[x][y] = 'X';
			whiteTurn = true;
		}

		printBoard(board);

		coordinate = "";
		validMove = true;
	}

    return 0;
}

void printBoard(char board[][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j];
		}

		cout << endl;
	}
}

bool isValidMove(int x, int y, char board[][8])
{
	if (board[x][y] != '-')
	{
		return false;
	}

	if (checkForAdjacentPiece(x, y, board))
	{
		if (checkForClosingPiece(x, y, board))
		{
			// FlipPieces
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool checkForAdjacentPiece(int x, int y, char board[][8])
{
	char opponentPiece;

	if (whiteTurn)
	{
		opponentPiece = 'X';
	}
	else
	{
		opponentPiece = 'O';
	}

	if (y > 0)
	{
		if (board[x][y - 1] == opponentPiece)
		{
			return true;
		}
	}

	if (x > 0 && y > 0)
	{
		if (board[x - 1][y - 1] == opponentPiece)
		{
			return true;
		}
	}

	if (x > 0)
	{
		if (board[x - 1][y] == opponentPiece)
		{
			return true;
		}
	}

	if (x > 0 && y < 8)
	{
		if (board[x - 1][y + 1] == opponentPiece)
		{
			return true;
		}
	}

	if (y < 8)
	{
		if (board[x][y + 1] == opponentPiece)
		{
			return true;
		}
	}

	if (x < 8 && y < 8)
	{
		if (board[x + 1][y + 1] == opponentPiece)
		{
			return true;
		}
	}

	if (x < 8)
	{
		if (board[x + 1][y] == opponentPiece)
		{
			return true;
		}
	}

	if (x > 0 && y < 8)
	{
		if (board[x - 1][y + 1] == opponentPiece)
		{
			return true;
		}
	}

	return false;
}

bool checkForClosingPiece(int x, int y, char board[][8])
{
	char targetPiece;

	if (whiteTurn)
	{
		targetPiece = 'O';
	}
	else
	{
		targetPiece = 'X';
	}

	// Check for diagonals
	for (int i = x + 2; i < 8; i++)
	{
		for (int j = y + 2; j < 8; j++)
		{
			if (board[i][j] == targetPiece)
			{
				cout << "Return 1" << endl;
				return true;
			}
		}
	}

	for (int i = x - 2; i >= 0; i--)
	{
		for (int j = y - 2; j >= 0; j--)
		{
			if (board[i][j] == targetPiece)
			{
				cout << "Return 2" << endl;
				return true;
			}
		}
	}

	for (int i = x + 2; i < 8; i++)
	{
		for (int j = y - 2; j >= 0; j--)
		{
			if (board[i][j] == targetPiece)
			{
				cout << "Return 3" << endl;
				return true;
			}
		}
	}

	for (int i = x - 2; i >= 0; i--)
	{
		for (int j = y + 2; j < 8; j++)
		{
			if (board[i][j] == targetPiece)
			{
				cout << "Return 4" << endl;
				return true;
			}
		}
	}

	// Check horizontal
	for (int j = y - 2; j >= 0; j--)
	{
		if (board[x][j] == targetPiece)
		{
			cout << "Return 5" << endl;
			return true;
		}
	}

	for (int j = y + 2; j < 8; j++)
	{
		if (board[x][j] == targetPiece)
		{
			cout << "Return 6" << endl;
			return true;
		}
	}

	// Check vertical
	for (int i = x - 2; i >= 0; i--)
	{
		if (board[i][y] == targetPiece)
		{
			cout << "Return 7" << endl;
			return true;
		}
	}

	for (int i = x + 2; i < 8; i++)
	{
		if (board[i][y] == targetPiece)
		{
			cout << "Return 8" << endl;
			return true;
		}
	}

	return false;
}