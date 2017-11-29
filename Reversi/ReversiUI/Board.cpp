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

	bool Board::IsValidMove(int x, int y)
	{
		if (mBoard[x][y] != '-')
		{
			return false;
		}

		if (CheckForAdjacentPiece(x, y))
		{
			if (FlipPieces(x, y))
			{
				if (mWhitePlayerTurn)
				{
					mBoard[x][y] = 'W';
					mWhiteScore++;
				}
				else
				{
					mBoard[x][y] = 'B';
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

		if (y > 0)
		{
			if (mBoard[x][y - 1] == opponentPiece)
			{
				return true;
			}
		}

		if (x > 0 && y > 0)
		{
			if (mBoard[x - 1][y - 1] == opponentPiece)
			{
				return true;
			}
		}

		if (x > 0)
		{
			if (mBoard[x - 1][y] == opponentPiece)
			{
				return true;
			}
		}

		if (x > 0 && y < 8)
		{
			if (mBoard[x - 1][y + 1] == opponentPiece)
			{
				return true;
			}
		}

		if (y < 8)
		{
			if (mBoard[x][y + 1] == opponentPiece)
			{
				return true;
			}
		}

		if (x < 8 && y < 8)
		{
			if (mBoard[x + 1][y + 1] == opponentPiece)
			{
				return true;
			}
		}

		if (x < 8)
		{
			if (mBoard[x + 1][y] == opponentPiece)
			{
				return true;
			}
		}

		if (x > 0 && y < 8)
		{
			if (mBoard[x - 1][y + 1] == opponentPiece)
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
		if (mBoard[x + 1][y + 1] == opponentPiece)
		{
			for (int i = x + 2; i < 8; i++)
			{
				for (int j = y + 2; j < 8; j++)
				{
					if (mBoard[i][j] == targetPiece)
					{
						i--;
						j--;

						while (mBoard[i][j] != targetPiece && (i > x && j > y))
						{
							mBoard[i][j] = targetPiece;
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

		if (mBoard[x - 1][y - 1] == opponentPiece)
		{
			for (int i = x - 2; i >= 0; i--)
			{
				for (int j = y - 2; j >= 0; j--)
				{
					if (mBoard[i][j] == targetPiece)
					{
						i++;
						j++;

						while (mBoard[i][j] != targetPiece && (i < x && j < y))
						{
							mBoard[i][j] = targetPiece;
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

		if (mBoard[x + 1][y - 1] == opponentPiece)
		{
			for (int i = x + 2; i < 8; i++)
			{
				for (int j = y - 2; j >= 0; j--)
				{
					if (mBoard[i][j] == targetPiece)
					{
						i--;
						j++;

						while (mBoard[i][j] != targetPiece && (i > x && j < y))
						{
							mBoard[i][j] = targetPiece;
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

		if (mBoard[x - 1][y + 1] == opponentPiece)
		{
			for (int i = x - 2; i >= 0; i--)
			{
				for (int j = y + 2; j < 8; j++)
				{
					if (mBoard[i][j] == targetPiece)
					{
						i++;
						j--;

						while (mBoard[i][j] != targetPiece && (i < x && j > y))
						{
							mBoard[i][j] = targetPiece;
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
		if (mBoard[x][y - 1] == opponentPiece)
		{
			for (int j = y - 2; j >= 0; j--)
			{
				if (mBoard[x][j] == targetPiece)
				{
					j++;

					while (mBoard[x][j] != targetPiece && j < y)
					{
						mBoard[x][j] = targetPiece;
						j++;

						UpdateScore();
					}

					closingPiece = true;
					break;
					//return true;
				}
			}
		}

		if (mBoard[x][y + 1] == opponentPiece)
		{
			for (int j = y + 2; j < 8; j++)
			{
				if (mBoard[x][j] == targetPiece)
				{
					j--;

					while (mBoard[x][j] != targetPiece && j > y)
					{
						mBoard[x][j] = targetPiece;
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
		if (mBoard[x - 1][y] == opponentPiece)
		{
			for (int i = x - 2; i >= 0; i--)
			{
				if (mBoard[i][y] == targetPiece)
				{
					i++;

					while (mBoard[i][y] != targetPiece && i < x)
					{
						mBoard[i][y] = targetPiece;
						i++;

						UpdateScore();
					}

					closingPiece = true;
					break;
					//return true;
				}
			}
		}


		if (mBoard[x + 1][y] == opponentPiece)
		{
			for (int i = x + 2; i < 8; i++)
			{
				if (mBoard[i][y] == targetPiece)
				{
					i--;

					while (mBoard[i][y] != targetPiece &&  i > x)
					{
						mBoard[i][y] = targetPiece;
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