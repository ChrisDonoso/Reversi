#include "stdafx.h"
#include "Board.h"

/*
Board should have:
An array mBoard (char array - '-' stands for empty, 'B' stands for black piece, 'W' stand for white piece')
bool mWhitePlayer
mWhiteScore
mBlackScore
*/

using namespace DirectX;
using namespace Library;
using namespace std;
using namespace Microsoft::WRL;

namespace Reversi
{
	Board::Board()
	{

	}

	void Board::Initialize()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mBoard[i][j] = '-';
			}
		}

		mBoard[3][3] = 'B';
		mBoard[4][4] = 'B';

		mBoard[3][4] = 'W';
		mBoard[4][3] = 'W';

		mWhiteScore = 2;
		mBlackScore = 2;

		mGameOver = false;
		mWhiteCanMove = true;
		mBlackCanMove = true;
	}

	bool Board::IsValidMove(int x, int y)
	{
		if (mBoard[y][x] != '-')
		{
			return false;
		}

		if (CheckForAdjacentPiece(x, y))
		{
			if (FlipPieces(x, y, true, false))
			{
				if (mWhitePlayerTurn)
				{
					mBoard[y][x] = 'W';
				}
				else
				{
					mBoard[y][x] = 'B';
				}
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

	void Board::CheckForAvailableMoves()
	{
		mNumAvailableMoves = 0;

		mMoves.clear();

		for (int row = 0; row < 8; row++)
		{
			for (int col = 0; col < 8; col++)
			{
				if (mBoard[col][row] == '-')
				{
					if (FlipPieces(row, col, false, false))
					{
						mAvailableMoves[col][row] = 1;
						mNumAvailableMoves++;
						mMoves.emplace_back(Point(row, col));
					}
					else
					{
						mAvailableMoves[col][row] = 0;
					}
				}
			}
		}
	}

	std::list<Library::Point> Board::GetMoves()
	{
		return mMoves;
	}

	int Board::NumberOfAvailableMoves()
	{
		return mNumAvailableMoves;
	}

	bool Board::CheckForAdjacentPiece(int x, int y)
	{
		char opponentPiece;

		if (mWhitePlayerTurn)
		{
			opponentPiece = 'B';
		}
		else
		{
			opponentPiece = 'W';
		}

		// Checks for piece to the left
		if (x > 0)
		{
			if (mBoard[y][x - 1] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece to the upper left
		if (x > 0 && y > 0)
		{
			if (mBoard[y - 1][x - 1] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece above
		if (y > 0)
		{
			if (mBoard[y - 1][x] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece to the upper right
		if (x < 7 && y > 0)
		{
			if (mBoard[y - 1][x + 1] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece to the right
		if (x < 7)
		{
			if (mBoard[y][x + 1] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece to the bottom right
		if (x < 7 && y < 7)
		{
			if (mBoard[y + 1][x + 1] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece below
		if (y < 7)
		{
			if (mBoard[y + 1][x] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece to the bottom left
		if (x > 0 && y < 7)
		{
			if (mBoard[y + 1][x - 1] == opponentPiece)
			{
				return true;
			}
		}

		return false;
	}

	bool Board::FlipPieces(int x, int y, bool flip, bool changePlayerTurn)
	{
		char targetPiece;
		char opponentPiece;
		bool closingPiece = false;
		bool pieceFound = false;
		int k = 0;

		if (mWhitePlayerTurn)
		{
			targetPiece = 'W';
			opponentPiece = 'B';
		}
		else
		{
			targetPiece = 'B';
			opponentPiece = 'W';
		}

		/// Check for diagonals

		// Lower-Right Diagonal
		if (y < 7 && x < 7)
		{
			if (mBoard[y + 1][x + 1] == opponentPiece)
			{
				k = y + 2;

				for (int i = x + 2; i < 8; i++)
				{
					if (mBoard[k][i] == '-')
					{
						break;
					}

					if (mBoard[k][i] == targetPiece)
					{
						i--;
						k--;

						if (flip)
						{
							while (mBoard[k][i] != targetPiece && (i > x && k > y))
							{
								mBoard[k][i] = targetPiece;
								i--;
								k--;

								UpdateScore();
							}
						}

						closingPiece = true;
						pieceFound = true;
					}

					if (pieceFound)
					{
						break;
					}

					k++;
				}
			}
		}

		pieceFound = false;

		// Upper-Left Diagonal
		if (y > 0 && x > 0)
		{
			if (mBoard[y - 1][x - 1] == opponentPiece)
			{
				k = y - 2;

				for (int i = x - 2; i >= 0; i--)
				{
					if (mBoard[k][i] == '-')
					{
						break;
					}

					if (mBoard[k][i] == targetPiece)
					{
						i++;
						k++;

						if (flip)
						{
							while (mBoard[k][i] != targetPiece && (i < x && k < y))
							{
								mBoard[k][i] = targetPiece;
								i++;
								k++;

								UpdateScore();
							}
						}

						closingPiece = true;
						pieceFound = true;
						break;
					}

					if (pieceFound)
					{
						break;
					}

					k--;
				}
			}
		}

		pieceFound = false;

		// Lower-Left Diagonal
		if (y < 7 && x > 0)
		{
			if (mBoard[y + 1][x - 1] == opponentPiece)
			{
				k = x - 2;

				for (int i = y + 2; i < 8; i++)
				{
					if (mBoard[i][k] == '-')
					{
						break;
					}

					if (mBoard[i][k] == targetPiece)
					{
						i--;
						k++;

						if (flip)
						{
							while (mBoard[i][k] != targetPiece && (i > y && k < x))
							{
								mBoard[i][k] = targetPiece;
								i--;
								k++;

								UpdateScore();
							}
						}

						closingPiece = true;
						pieceFound = true;
						break;
					}

					if (pieceFound)
					{
						break;
					}

					k--;
				}
			}
		}

		pieceFound = false;

		// Upper-Right Diagonal
		if (y > 0 && x < 7)
		{
			if (mBoard[y - 1][x + 1] == opponentPiece)
			{
				k = x + 2;

				for (int i = y - 2; i >= 0; i--)
				{
					if (mBoard[i][k] == '-')
					{
						break;
					}

					if (mBoard[i][k] == targetPiece)
					{
						i++;
						k--;

						if (flip)
						{
							while (mBoard[i][k] != targetPiece && (k > x && i < y))
							{
								mBoard[i][k] = targetPiece;
								i++;
								k--;

								UpdateScore();
							}
						}

						closingPiece = true;
						pieceFound = true;
						break;
					}

					if (pieceFound)
					{
						break;
					}

					k++;
				}
			}
		}

		// Check horizontal
		if (x > 0)
		{
			if (mBoard[y][x - 1] == opponentPiece)
			{
				for (int j = x - 2; j >= 0; j--)
				{
					if (mBoard[y][j] == '-')
					{
						break;
					}

					if (mBoard[y][j] == targetPiece)
					{
						j++;

						if (flip)
						{
							while (mBoard[y][j] != targetPiece && j < x)
							{
								mBoard[y][j] = targetPiece;
								j++;

								UpdateScore();
							}
						}

						closingPiece = true;
						break;
					}
				}
			}
		}

		if (x < 7)
		{
			if (mBoard[y][x + 1] == opponentPiece)
			{
				for (int j = x + 2; j < 8; j++)
				{
					if (mBoard[y][j] == '-')
					{
						break;
					}

					if (mBoard[y][j] == targetPiece)
					{
						j--;

						if (flip)
						{
							while (mBoard[y][j] != targetPiece && j > x)
							{
								mBoard[y][j] = targetPiece;
								j--;

								UpdateScore();
							}
						}

						closingPiece = true;
						break;
					}
				}
			}
		}

		// Check vertical
		if (y > 0)
		{
			if (mBoard[y - 1][x] == opponentPiece)
			{
				for (int i = y - 2; i >= 0; i--)
				{
					if (mBoard[i][x] == '-')
					{
						break;
					}

					if (mBoard[i][x] == targetPiece)
					{
						i++;

						if (flip)
						{
							while (mBoard[i][x] != targetPiece && i < y)
							{
								mBoard[i][x] = targetPiece;
								i++;

								UpdateScore();
							}
						}

						closingPiece = true;
						break;
					}
				}
			}
		}

		if (y < 7)
		{
			if (mBoard[y + 1][x] == opponentPiece)
			{
				for (int i = y + 2; i < 8; i++)
				{
					if (mBoard[i][x] == '-')
					{
						break;
					}

					if (mBoard[i][x] == targetPiece)
					{
						i--;

						if (flip)
						{
							while (mBoard[i][x] != targetPiece &&  i > y)
							{
								mBoard[i][x] = targetPiece;
								i--;

								UpdateScore();
							}
						}

						closingPiece = true;
						break;
					}
				}
			}
		}

		if (closingPiece && flip)
		{
			SetLastMoveMade(x, y);

			if (mWhitePlayerTurn)
			{
				mWhiteScore++;
			}
			else
			{
				mBlackScore++;
			}
		}

		if (changePlayerTurn)
		{
			mWhitePlayerTurn = !mWhitePlayerTurn;
		}

		return closingPiece;
	}

	void Board::UpdateScore()
	{
		if (mWhitePlayerTurn)
		{
			mWhiteScore++;
			mBlackScore--;
		}
		else
		{
			mBlackScore++;
			mWhiteScore--;
		}
	}

	int Board::GetWhiteScore()
	{
		return mWhiteScore;
	}

	int Board::GetBlackScore()
	{
		return mBlackScore;
	}

	bool Board::GetWhitePlayerTurn()
	{
		return mWhitePlayerTurn;
	}

	void Board::SetWhitePlayerTurn(bool flag)
	{
		mWhitePlayerTurn = flag;
	}

	bool Board::IsGameOver()
	{
		return mGameOver;
	}

	void Board::UpdateGameOver()
	{
		if (mNumAvailableMoves == 0)
		{
			if (mWhitePlayerTurn)
			{
				mWhiteCanMove = false;

			}
			else
			{
				mBlackCanMove = false;
			}

			if (mWhiteCanMove || mBlackCanMove)
			{
				mWhitePlayerTurn = !mWhitePlayerTurn;
			}
		}
		else
		{
			if (mWhitePlayerTurn)
			{
				mWhiteCanMove = true;

			}
			else
			{
				mBlackCanMove = true;
			}
		}

		if (!mWhiteCanMove && !mBlackCanMove)
		{
			mGameOver = true;
		}
	}

	void Board::SetLastMoveMade(int x, int y)
	{
		mLastMoveMade.first = x;
		mLastMoveMade.second = y;
	}

	std::pair<int, int> Board::GetLastMoveMade()
	{
		return mLastMoveMade;
	}

	char * Board::GetBoard()
	{
		return *mBoard;
	}

	int * Board::GetAvailableMoves()
	{
		return *mAvailableMoves;
	}

	void Board::SetAIMove(int x, int y)
	{
		if (mWhitePlayerTurn)
		{
			mBoard[y][x] = 'W';
		}
		else
		{
			mBoard[y][x] = 'B';
		}
	}
}