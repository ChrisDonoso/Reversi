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
		//float xpos = 398.0f;// = //398.0f; // 605
		//float ypos = 511.0f; // 510

		float xpos = 610.0f;
		float ypos = 510.0f;

		for (int row = 7; row >= 0; row--)
		{
			for (int col = 7; col >= 0; col--)
			{
				if (mBoard[row][col] == 'W')
				{
					SpriteManager::DrawTexture2D(mWhiteTexture.Get(), XMFLOAT2(xpos, ypos));
				}
				else if (mBoard[row][col] == 'B')
				{
					SpriteManager::DrawTexture2D(mBlackTexture.Get(), XMFLOAT2(xpos, ypos));
				}
				
				xpos -= mBoundsBlack.Width + 5.0f;
			}

			// Reset offset for x position
			xpos = 610.0f; // 605
			ypos -= mBoundsWhite.Height + 5.0f;
		}
	}

	bool Board::IsValidMove(int x, int y)
	{
		if (mBoard[y][x] != '-')
		{
			return false;
		}

		if (CheckForAdjacentPiece(x, y))
		{
			if (FlipPieces(x, y))
			{
				if (mWhitePlayerTurn)
				{
					mBoard[y][x] = 'W';
					mWhiteScore++;
				}
				else
				{
					mBoard[y][x] = 'B';
					mBlackScore++;
				}
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
		if (y > 0)
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
		if (x > 0)
		{
			if (mBoard[y - 1][x] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece to the upper right
		if (x > 0 && y < 8)
		{
			if (mBoard[y - 1][x + 1] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece to the right
		if (y < 8)
		{
			if (mBoard[y][x + 1] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece to the bottom right
		if (x < 8 && y < 8)
		{
			if (mBoard[y + 1][x + 1] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece below
		if (x < 8)
		{
			if (mBoard[y + 1][x] == opponentPiece)
			{
				return true;
			}
		}

		// Checks for piece to the bottom left
		if (x > 0 && y < 8)
		{
			if (mBoard[y + 1][x - 1] == opponentPiece)
			{
				return true;
			}
		}

		return false;
	}

	bool Board::FlipPieces(int x, int y)
	{
		char targetPiece;
		char opponentPiece;
		bool closingPiece = false;
		bool pieceFound = false;

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

		// Check for diagonals
		// Lower-Right Diagonal
		if (mBoard[y + 1][x + 1] == opponentPiece)
		{
			for (int i = x + 2; i < 8; i++)
			{
				for (int j = y + 2; j < 8; j++)
				{
					if (mBoard[j][i] == targetPiece)
					{
						i--;
						j--;

						while (mBoard[j][i] != targetPiece && (i > x && j > y))
						{
							mBoard[j][i] = targetPiece;
							i--;
							j--;

							UpdateScore();
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

		// Upper-Left Diagonal
		if (mBoard[y - 1][x - 1] == opponentPiece)
		{
			for (int i = x - 2; i >= 0; i--)
			{
				for (int j = y - 2; j >= 0; j--)
				{
					if (mBoard[j][i] == targetPiece)
					{
						i++;
						j++;

						while (mBoard[j][i] != targetPiece && (i < x && j < y))
						{
							mBoard[j][i] = targetPiece;
							i++;
							j++;

							UpdateScore();
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

		// Lower-Left Diagonal
		if (mBoard[y + 1][x - 1] == opponentPiece)
		{
			for (int i = x + 2; i < 8; i++)
			{
				for (int j = y - 2; j >= 0; j--)
				{
					if (mBoard[j][i] == targetPiece)
					{
						i--;
						j++;

						while (mBoard[j][i] != targetPiece && (i > x && j < y))
						{
							mBoard[j][i] = targetPiece;
							i--;
							j++;

							UpdateScore();
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

		// Upper-Right Diagonal
		if (mBoard[y - 1][x + 1] == opponentPiece)
		{
			for (int i = y - 2; i >= 0; i--)
			{
				for (int j = x + 2; j < 8; j++)
				{
					if (mBoard[j][i] == targetPiece)
					{
						i++;
						j--;

						while (mBoard[j][i] != targetPiece && (i < x && j > y))
						{
							mBoard[j][i] = targetPiece;
							i++;
							j--;

							UpdateScore();
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
		if (mBoard[y][x - 1] == opponentPiece)
		{
			for (int j = x - 2; j >= 0; j--)
			{
				if (mBoard[y][j] == targetPiece)
				{
					j++;

					while (mBoard[y][j] != targetPiece && j < x)
					{
						mBoard[y][j] = targetPiece;
						j++;

						UpdateScore();
					}

					closingPiece = true;
					break;
					//return true;
				}
			}
		}

		if (mBoard[y][x + 1] == opponentPiece)
		{
			for (int j = x + 2; j < 8; j++)
			{
				if (mBoard[y][j] == targetPiece)
				{
					j--;

					while (mBoard[y][j] != targetPiece && j > x)
					{
						mBoard[y][j] = targetPiece;
						j--;

						UpdateScore();
					}

					closingPiece = true;
					break;
					//return true;
				}
			}
		}

		// Check vertical
		if (mBoard[y - 1][x] == opponentPiece)
		{
			for (int i = y - 2; i >= 0; i--)
			{
				if (mBoard[i][x] == targetPiece)
				{
					i++;

					while (mBoard[i][x] != targetPiece && i < y)
					{
						mBoard[i][x] = targetPiece;
						i++;

						UpdateScore();
					}

					closingPiece = true;
					break;
					//return true;
				}
			}
		}


		if (mBoard[y + 1][x] == opponentPiece)
		{
			for (int i = y + 2; i < 8; i++)
			{
				if (mBoard[i][x] == targetPiece)
				{
					i--;

					while (mBoard[i][x] != targetPiece &&  i > y)
					{
						mBoard[i][x] = targetPiece;
						i--;

						UpdateScore();
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
	bool Board::GetWhitePlayerTurn()
	{
		return mWhitePlayerTurn;
	}

	void Board::SetWhitePlayerTurn(bool flag)
	{
		mWhitePlayerTurn = flag;
	}
}