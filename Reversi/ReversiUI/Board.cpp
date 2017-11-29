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

namespace Board
{
	Board::Board(Library::Game & game) :
		DrawableGameComponent(game), mBoundsWhite(Rectangle::Empty), mBoundsBlack(Rectangle::Empty)
	{
	}

	void Board::Initialize()
	{
		mWhiteTurn = true;
		whiteScore = 2;
		blackScore = 2;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mBoard[i][j] = '-';
			}
		}

		mBoard[3][3] = 'W';
		mBoard[4][4] = 'W';

		mBoard[3][4] = 'B';
		mBoard[4][3] = 'B';

		ComPtr<ID3D11Resource> textureResource;
		wstring textureName = L"Content\\Textures\\whiteCoin.png";

		ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mWhiteTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");

		ComPtr<ID3D11Texture2D> texture;
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");

		mBoundsWhite = TextureHelper::GetTextureBounds(texture.Get());

		textureName = L"Content\\Textures\\blackCoin.png";
		ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mBlackTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");
		mBoundsBlack = TextureHelper::GetTextureBounds(texture.Get());
	}

	void Board::Update(const Library::GameTime & gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);


	}

	void Board::Draw(const Library::GameTime & gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);

		// Offsets for grid placement
		float xpos = 398.0f;// = //398.0f; // 605
		float ypos = 511.0f; // 510

		for (int row = 7; row >= 0; row--)
		{
			for (int col = 7; col >= 0; col--)
			{
				if (mBoard[row][col] == 'W')
				{
					SpriteManager::DrawTexture2D(mWhiteTexture.Get(), XMFLOAT2(xpos, ypos));

					xpos -= mBoundsWhite.Width + 5.5f;
				}
				else if (mBoard[row][col] == 'B')
				{
					SpriteManager::DrawTexture2D(mBlackTexture.Get(), XMFLOAT2(xpos, ypos));

					xpos -= mBoundsBlack.Width + 5.5f;
				}
			}

			// Reset offset for x position
			xpos = 398.0f; // 605
			ypos -= mBoundsWhite.Height + 5.5f;
		}
	}

	bool Board::isValidMove(int x, int y, char board[][8])
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

	bool Board::checkForAdjacentPiece(int x, int y, char board[][8])
	{
		char opponentPiece;

		if (mWhiteTurn)
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

	bool Board::checkForClosingPiece(int x, int y, char board[][8])
	{
		char targetPiece;
		char opponentPiece;
		bool closingPiece = false;
		bool pieceFound = false;

		if (mWhiteTurn)
		{
			targetPiece = 'O';
			opponentPiece = 'X';
		}
		else
		{
			targetPiece = 'X';
			opponentPiece = 'O';
		}

		// Check for diagonals
		if (board[x + 1][y + 1] == opponentPiece)
		{
			for (int i = x + 2; i < 8; i++)
			{
				for (int j = y + 2; j < 8; j++)
				{
					if (board[i][j] == targetPiece)
					{
						i--;
						j--;

						while (board[i][j] != targetPiece && (i > x && j > y))
						{
							board[i][j] = targetPiece;
							i--;
							j--;

							updateScore();
						}

						closingPiece = true;
						pieceFound = true;
						break;
						//return true;
					}
				}

				if (pieceFound)
				{
					break;
				}
			}
		}

		pieceFound = false;

		if (board[x - 1][y - 1] == opponentPiece)
		{
			for (int i = x - 2; i >= 0; i--)
			{
				for (int j = y - 2; j >= 0; j--)
				{
					if (board[i][j] == targetPiece)
					{
						i++;
						j++;

						while (board[i][j] != targetPiece && (i < x && j < y))
						{
							board[i][j] = targetPiece;
							i++;
							j++;

							updateScore();
						}

						closingPiece = true;
						pieceFound = true;
						break;
						//return true;
					}
				}

				if (pieceFound)
				{
					break;
				}
			}
		}

		pieceFound = false;

		if (board[x + 1][y - 1] == opponentPiece)
		{
			for (int i = x + 2; i < 8; i++)
			{
				for (int j = y - 2; j >= 0; j--)
				{
					if (board[i][j] == targetPiece)
					{
						i--;
						j++;

						while (board[i][j] != targetPiece && (i > x && j < y))
						{
							board[i][j] = targetPiece;
							i--;
							j++;

							updateScore();
						}

						closingPiece = true;
						pieceFound = true;
						break;
						//return true;
					}
				}

				if (pieceFound)
				{
					break;
				}
			}
		}

		pieceFound = false;

		if (board[x - 1][y + 1] == opponentPiece)
		{
			for (int i = x - 2; i >= 0; i--)
			{
				for (int j = y + 2; j < 8; j++)
				{
					if (board[i][j] == targetPiece)
					{
						i++;
						j--;

						while (board[i][j] != targetPiece && (i < x && j > y))
						{
							board[i][j] = targetPiece;
							i++;
							j--;

							updateScore();
						}

						closingPiece = true;
						pieceFound = true;
						break;
						//return true;
					}
				}

				if (pieceFound)
				{
					break;
				}
			}
		}

		// Check horizontal
		if (board[x][y - 1] == opponentPiece)
		{
			for (int j = y - 2; j >= 0; j--)
			{
				if (board[x][j] == targetPiece)
				{
					j++;

					while (board[x][j] != targetPiece && j < y)
					{
						board[x][j] = targetPiece;
						j++;

						updateScore();
					}

					closingPiece = true;
					break;
					//return true;
				}
			}
		}

		if (board[x][y + 1] == opponentPiece)
		{
			for (int j = y + 2; j < 8; j++)
			{
				if (board[x][j] == targetPiece)
				{
					j--;

					while (board[x][j] != targetPiece && j > y)
					{
						board[x][j] = targetPiece;
						j--;

						updateScore();
					}

					closingPiece = true;
					break;
					//return true;
				}
			}
		}

		// Check vertical
		if (board[x - 1][y] == opponentPiece)
		{
			for (int i = x - 2; i >= 0; i--)
			{
				if (board[i][y] == targetPiece)
				{
					i++;

					while (board[i][y] != targetPiece && i < x)
					{
						board[i][y] = targetPiece;
						i++;

						updateScore();
					}

					closingPiece = true;
					break;
					//return true;
				}
			}
		}


		if (board[x + 1][y] == opponentPiece)
		{
			for (int i = x + 2; i < 8; i++)
			{
				if (board[i][y] == targetPiece)
				{
					i--;

					while (board[i][y] != targetPiece &&  i > x)
					{
						board[i][y] = targetPiece;
						i--;

						updateScore();
					}

					closingPiece = true;
					break;
					//return true;
				}
			}
		}

		//return false;
		return closingPiece;
	}

	void Board::updateScore()
	{
		if (mWhiteTurn)
		{
			whiteScore++;
			blackScore--;
		}
		else
		{
			blackScore++;
			whiteScore--;
		}
	}
}