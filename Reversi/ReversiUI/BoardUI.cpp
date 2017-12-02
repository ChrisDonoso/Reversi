#include "stdafx.h"
#include "BoardUI.h"
#include "Board.h"

using namespace DirectX;
using namespace Library;
using namespace std;
using namespace Microsoft::WRL;

namespace Reversi
{
	BoardUI::BoardUI(Library::Game & game) :
		DrawableGameComponent(game), mRenderStateHelper(game), mBoundsWhite(Rectangle::Empty), mBoundsBlack(Rectangle::Empty), mBoundsAvailable(Rectangle::Empty)
	{
	}

	void BoardUI::Initialize()
	{
		/*mBoard = new char*[8];

		for (int i = 0; i < 8; i++)
		{
			mBoard[i] = new char[8];
		}*/

		/*mBoard.resize(8);

		for (int i = 0; i < 8; i++)
		{
			mBoard[i].resize(8);
		}
*/
		ComPtr<ID3D11Resource> textureResource;
		wstring textureName = L"Content\\Textures\\whiteCoin2.png";

		ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mWhiteTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");

		ComPtr<ID3D11Texture2D> texture;
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");

		mBoundsWhite = TextureHelper::GetTextureBounds(texture.Get());

		textureName = L"Content\\Textures\\blackCoin2.png";
		ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mBlackTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");
		mBoundsBlack = TextureHelper::GetTextureBounds(texture.Get());

		textureName = L"Content\\Textures\\AvailableTile.png";
		ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mAvailableTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");
		mBoundsAvailable = TextureHelper::GetTextureBounds(texture.Get());

		mSpriteFont14 = make_unique<SpriteFont>(mGame->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");
	}

	void BoardUI::Update(const Library::GameTime & gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);
	}

	void BoardUI::Draw(const Library::GameTime & gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);
		//if (mDraw)
		//{
		float xpos = 610.0f;
		float ypos = 510.0f;

		//for (int row = 7; row >= 0; row--)
		//{
		//	for (int col = 7; col >= 0; col--)
		//	{
		//		if (mBoard[row][col] == 'W')
		//		{
		//			SpriteManager::DrawTexture2D(mWhiteTexture.Get(), XMFLOAT2(xpos, ypos));
		//			//xpos -= mBoundsBlack.Width + 5.0f;
		//		}
		//		else if (mBoard[row][col] == 'B')
		//		{
		//			SpriteManager::DrawTexture2D(mBlackTexture.Get(), XMFLOAT2(xpos, ypos));
		//			//xpos -= mBoundsBlack.Width + 5.0f;
		//		}

		//		xpos -= mBoundsBlack.Width + 5.0f;
		//	}

		//	// Reset offset for x position
		//	xpos = 610.0f; // 605
		//	ypos -= mBoundsWhite.Height + 5.0f;
		//}

		//ypos = 510.0f;

		//for (int row = 7; row >= 0; row--)
		//{
		//	for (int col = 7; col >= 0; col--)
		//	{
		//		if (mBoard[row][col] == '-') //mAvailableMoves[row][col] && mBoard[row][col] == '-')
		//		{
		//			SpriteManager::DrawTexture2D(mAvailableTexture.Get(), XMFLOAT2(xpos, ypos));
		//		}

		//		xpos -= mBoundsAvailable.Width;
		//	}

		//	// Reset offset for x position
		//	xpos = 610.0f;
		//	ypos -= mBoundsAvailable.Height;
		//}

		for (int i = 0; i < 64; i++)
		{
			if (mBoard[i] == 'W')
			{
				SpriteManager::DrawTexture2D(mWhiteTexture.Get(), XMFLOAT2(xpos, ypos));
			}
			else if (mBoard[i] == 'B')
			{
				SpriteManager::DrawTexture2D(mBlackTexture.Get(), XMFLOAT2(xpos, ypos));
			}

			xpos -= mBoundsBlack.Width + 5.0f;

			if (i % 8 == 0)
			{
				// Reset offset for x position
				xpos = 610.0f; // 605
				ypos -= mBoundsWhite.Height + 5.0f;
			}
		}

		wostringstream whiteScore;
		wostringstream blackScore;

		whiteScore << "White: " << mWhiteScore;
		blackScore << "Black: " << mBlackScore;

		mRenderStateHelper.SaveAll();
		SpriteManager::DrawString(mSpriteFont14, whiteScore.str().c_str(), XMFLOAT2(685, 20));
		SpriteManager::DrawString(mSpriteFont14, blackScore.str().c_str(), XMFLOAT2(685, 45));
		mRenderStateHelper.RestoreAll();
		//}
	}

	//void BoardUI::SetBoard(std::vector<std::vector<char>> board)
	//{
		/*for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mBoard[i][j] = board[i][j];
			}
		}*/
	//}

	//void BoardUI::SetBoard(char ** board);//[][8])
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		for (int j = 0; j < 8; j++)
	//		{
	//			mBoard[i][j] = board[i][j];
	//		}
	//	}
	//}

	//void BoardUI::SetBoard(char * board)
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		//board[i] = new char[8];
	//		for (int j = 0; j < 8; j++)
	//		{
	//			mBoard[i][j] = board[i][j];
	//		}
	//	}
	//}

	void BoardUI::SetBoard(std::shared_ptr<Board> board)
	{
		//char *tempBoard = board->GetBoard();
		//mBoard = board->GetBoard();
		mBoard = board->GetBoard();
	}

	void BoardUI::SetWhiteScore(int score)
	{
		mWhiteScore = score;
	}

	void BoardUI::SetBlackScore(int score)
	{
		mBlackScore = score;
	}
}