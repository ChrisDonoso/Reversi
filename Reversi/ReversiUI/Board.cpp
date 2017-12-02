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
	/*Board::Board(Library::Game & game) :
		DrawableGameComponent(game), mRenderStateHelper(game), mBoundsWhite(Rectangle::Empty), mBoundsBlack(Rectangle::Empty), mBoundsAvailable(Rectangle::Empty)
	{
	}*/

	Board::Board()
	{

	}

	void Board::Initialize()
	{
		//mBoard = new char*[8];

		//mBoard.resize(8);

		for (int i = 0; i < 8; i++)
		{
			//mBoard[i] = new char[8];
			//mBoard[i].resize(8);

			for (int j = 0; j < 8; j++)
			{
				mBoard[i][j] = '-';
			}
		}

		//mBoard[7][6] = '.';
		mBoard[3][3] = 'B';
		mBoard[4][4] = 'B';

		mBoard[3][4] = 'W';
		mBoard[4][3] = 'W';

		mWhiteScore = 2;
		mBlackScore = 2;

		mGameOver = false;
		mWhiteCanMove = true;
		mBlackCanMove = true;

		//ComPtr<ID3D11Resource> textureResource;
		//wstring textureName = L"Content\\Textures\\whiteCoin2.png";

		//ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mWhiteTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");

		//ComPtr<ID3D11Texture2D> texture;
		//ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");

		//mBoundsWhite = TextureHelper::GetTextureBounds(texture.Get());

		//textureName = L"Content\\Textures\\blackCoin2.png";
		//ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mBlackTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");
		//ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");
		//mBoundsBlack = TextureHelper::GetTextureBounds(texture.Get());

		//textureName = L"Content\\Textures\\AvailableTile.png";
		//ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mAvailableTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");
		//ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");
		//mBoundsAvailable = TextureHelper::GetTextureBounds(texture.Get());

		//mSpriteFont14 = make_unique<SpriteFont>(mGame->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");
	}

	//void Board::Update(const Library::GameTime & gameTime)
	//{
	//	UNREFERENCED_PARAMETER(gameTime);

	//	// Might need to enchance game over rules
	//	if (mNumAvailableMoves == 0)
	//	{
	//		if (mWhitePlayerTurn)
	//		{
	//			mWhiteCanMove = false;

	//		}
	//		else
	//		{
	//			mBlackCanMove = false;
	//		}

	//		if (mWhiteCanMove || mBlackCanMove)
	//		{
	//			mWhitePlayerTurn = !mWhitePlayerTurn;
	//		}
	//	}
	//	else
	//	{
	//		if (mWhitePlayerTurn)
	//		{
	//			mWhiteCanMove = true;

	//		}
	//		else
	//		{
	//			mBlackCanMove = true;
	//		}
	//	}

	//	if (!mWhiteCanMove && !mBlackCanMove)
	//	{
	//		mGameOver = true;
	//	}
	//}

	/*void Board::Draw(const Library::GameTime & gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);*/

		// Offsets for grid placement
		//float xpos = 398.0f;// = //398.0f; // 605
		//float ypos = 511.0f; // 510

		//if (mDraw)
		//{
		//	float xpos = 610.0f;
		//	float ypos = 510.0f;

		//	for (int row = 7; row >= 0; row--)
		//	{
		//		for (int col = 7; col >= 0; col--)
		//		{
		//			if (mBoard[row][col] == 'W')
		//			{
		//				SpriteManager::DrawTexture2D(mWhiteTexture.Get(), XMFLOAT2(xpos, ypos));
		//				//xpos -= mBoundsBlack.Width + 5.0f;
		//			}
		//			else if (mBoard[row][col] == 'B')
		//			{
		//				SpriteManager::DrawTexture2D(mBlackTexture.Get(), XMFLOAT2(xpos, ypos));
		//				//xpos -= mBoundsBlack.Width + 5.0f;
		//			}

		//			xpos -= mBoundsBlack.Width + 5.0f;
		//		}

		//		// Reset offset for x position
		//		xpos = 610.0f; // 605
		//		ypos -= mBoundsWhite.Height + 5.0f;
		//	}

		//	ypos = 510.0f;

		//	for (int row = 7; row >= 0; row--)
		//	{
		//		for (int col = 7; col >= 0; col--)
		//		{
		//			if (mAvailableMoves[row][col] && mBoard[row][col] == '-')
		//			{
		//				SpriteManager::DrawTexture2D(mAvailableTexture.Get(), XMFLOAT2(xpos, ypos));
		//			}

		//			xpos -= mBoundsAvailable.Width;
		//		}

		//		// Reset offset for x position
		//		xpos = 610.0f;
		//		ypos -= mBoundsAvailable.Height;
		//	}

		//	wostringstream whiteScore;
		//	wostringstream blackScore;

		//	whiteScore << "White: " << mWhiteScore;
		//	blackScore << "Black: " << mBlackScore;

		//	mRenderStateHelper.SaveAll();
		//	SpriteManager::DrawString(mSpriteFont14, whiteScore.str().c_str(), XMFLOAT2(685, 20));
		//	SpriteManager::DrawString(mSpriteFont14, blackScore.str().c_str(), XMFLOAT2(685, 45));
		//	mRenderStateHelper.RestoreAll();
		//}
	//}

	bool Board::IsValidMove(int x, int y)
	{
		if (mBoard[y][x] != '-')
		{
			return false;
		}

		if (CheckForAdjacentPiece(x, y))
		{
			if (FlipPieces(x, y, true))
			{
				if (mWhitePlayerTurn)
				{
					mBoard[y][x] = 'W';
					//mWhiteScore++;
				}
				else
				{
					mBoard[y][x] = 'B';
					//mBlackScore++;
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
					/*if (CheckForAdjacentPiece(row, col))
					{*/
						if (FlipPieces(row, col, false))
						{
							mAvailableMoves[col][row] = 1;
							mNumAvailableMoves++;
							mMoves.emplace_back(Point(col, row));
						}
						else
						{
							mAvailableMoves[col][row] = 0;
						}
					//} 
					/*if (CheckForAdjacentPiece(row, col))
					{
						mAvailableMoves[row][col] = 1;
					}
					else
					{
						mAvailableMoves[row][col] = 0;
					}*/
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

	/*bool Board::CheckForClosingPiece(int x, int y)
	{
		return false;
	}*/

	bool Board::FlipPieces(int x, int y, bool flip)
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

		// Check for diagonals
		// Lower-Right Diagonal
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
					break;
					//return true;
				}

				//for (int j = y + 2; j < 8; j++)
				//{
				//	if (mBoard[j][i] == targetPiece)
				//	{
				//		i--;
				//		j--;

				//		if (flip)
				//		{
				//			while (mBoard[j][i] != targetPiece && (i > x && j > y))
				//			{
				//				mBoard[j][i] = targetPiece;
				//				i--;
				//				j--;

				//				UpdateScore();
				//			}
				//		}

				//		closingPiece = true;
				//		pieceFound = true;
				//		break;
				//		//return true;
				//	}
				//}

				if (pieceFound)
				{
					break;
				}

				k++;
			}
		}

		pieceFound = false;

		// Upper-Left Diagonal
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
					//return true;
				}

				//for (int j = y - 2; j >= 0; j--)
				//{
				//	if (mBoard[j][i] == targetPiece)
				//	{
				//		i++;
				//		j++;

				//		if (flip)
				//		{
				//			while (mBoard[j][i] != targetPiece && (i < x && j < y))
				//			{
				//				mBoard[j][i] = targetPiece;
				//				i++;
				//				j++;

				//				UpdateScore();
				//			}
				//		}

				//		closingPiece = true;
				//		pieceFound = true;
				//		break;
				//		//return true;
				//	}
				//}

				if (pieceFound)
				{
					break;
				}

				k--;
			}
		}

		pieceFound = false;

		// Lower-Left Diagonal
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
					//return true;
				}

				//for (int j = y - 2; j < 8; j++)
				//{
				//	if (mBoard[i][j] == targetPiece)
				//	{
				//		i--;
				//		j++;

				//		if (flip)
				//		{
				//			while (mBoard[i][j] != targetPiece && (i > y && j < x))
				//			{
				//				mBoard[i][j] = targetPiece;
				//				i--;
				//				j++;

				//				UpdateScore();
				//			}
				//		}

				//		closingPiece = true;
				//		pieceFound = true;
				//		break;
				//		//return true;
				//	}
				//}

				if (pieceFound)
				{
					break;
				}

				k--;
			}
		}

		pieceFound = false;

		// Upper-Right Diagonal
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

					//return true;
				}
				//for (int j = x + 2; j >= 0; j--)
				//{
				//	if (mBoard[i][j] == targetPiece)
				//	{
				//		i++;
				//		j--;
				//		if (flip)

				//		{
				//			while (mBoard[i][j] != targetPiece && (j > x && i < y))
				//			{
				//				mBoard[i][j] = targetPiece;
				//				i++;
				//				j--;

				//				UpdateScore();
				//			}
				//		}

				//		closingPiece = true;
				//		pieceFound = true;
				//		break;
				//		//return true;
				//	}
				//}

				if (pieceFound)
				{
					break;
				}

				k++;
			}
		} 

		/// LOOK AT HORIZONTAL
		// Check horizontal
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
					//return true;
				}
			}
		}

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
					//return true;
				}
			}
		}

		// Check vertical
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
					//return true;
				}
			}
		}

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
					//return true;
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

		//return false;
		return closingPiece;
	}

	void Board::Evaluate(int x, int y)
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

		// Check for diagonals
		// Lower-Right Diagonal
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

					while (mBoard[k][i] != targetPiece && (i > x && k > y))
					{
						i--;
						k--;

						UpdateScore();
					}

					closingPiece = true;
					pieceFound = true;
					break;
					//return true;
				}

				if (pieceFound)
				{
					break;
				}

				k++;
			}
		}

		pieceFound = false;

		// Upper-Left Diagonal
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

					while (mBoard[k][i] != targetPiece && (i < x && k < y))
					{
						i++;
						k++;

						UpdateScore();
					}

					closingPiece = true;
					pieceFound = true;
					break;
					//return true;
				}

				if (pieceFound)
				{
					break;
				}

				k--;
			}
		}

		pieceFound = false;

		// Lower-Left Diagonal
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

					while (mBoard[i][k] != targetPiece && (i > y && k < x))
					{
						i--;
						k++;

						UpdateScore();
					}

					closingPiece = true;
					pieceFound = true;
					break;
					//return true;
				}

				if (pieceFound)
				{
					break;
				}

				k--;
			}
		}

		pieceFound = false;

		// Upper-Right Diagonal
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

					while (mBoard[i][k] != targetPiece && (k > x && i < y))
					{
						i++;
						k--;

						UpdateScore();
					}

					closingPiece = true;
					pieceFound = true;
					break;

					//return true;
				}

				if (pieceFound)
				{
					break;
				}

				k++;
			}
		}

		/// LOOK AT HORIZONTAL
		// Check horizontal
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

					while (mBoard[y][j] != targetPiece && j < x)
					{
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
				if (mBoard[y][j] == '.')
				{
					break;
				}

				if (mBoard[y][j] == targetPiece)
				{
					j--;

					while (mBoard[y][j] != targetPiece && j > x)
					{
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
				if (mBoard[i][x] == '-')
				{
					break;
				}

				if (mBoard[i][x] == targetPiece)
				{
					i++;

					while (mBoard[i][x] != targetPiece && i < y)
					{
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
				if (mBoard[i][x] == '-')
				{
					break;
				}

				if (mBoard[i][x] == targetPiece)
				{
					i--;

					while (mBoard[i][x] != targetPiece &&  i > y)
					{
						i--;

						UpdateScore();
					}
				
					closingPiece = true;
					break;
					//return true;
				}
			}
		}

		if (closingPiece)
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

	void Board::SetDraw(bool flag)
	{
		mDraw = flag;
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

	/*std::vector<std::vector<char>> Board::GetBoard()
	{
		return mBoard;
	}*/
}