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

		float xpos = 610.0f;
		float ypos = 580.0f; // 510.0f;

		for (int i = 64; i >= 0; i--)
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
				xpos = 610.0f;
				ypos -= mBoundsWhite.Height + 5.0f;
			}
		}

		ypos = 580.0f;

		for (int i = 64; i >= 0; i--)
		{
			if (mAvailableMoves[i] && mBoard[i] == '-')
			{
				SpriteManager::DrawTexture2D(mAvailableTexture.Get(), XMFLOAT2(xpos, ypos));
			}

			xpos -= mBoundsAvailable.Width;

			if (i % 8 == 0)
			{
				// Reset offset for x position
				xpos = 610.0f;
				ypos -= mBoundsAvailable.Height;
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
	}

	void BoardUI::SetBoard(std::shared_ptr<Board> board)
	{
		mBoard = board->GetBoard();
	}

	void BoardUI::SetAvailableMoves(std::shared_ptr<Board> board)
	{
		mAvailableMoves = board->GetAvailableMoves();
	}

	void BoardUI::SetWhiteScore(int score)
	{
		mWhiteScore = score;
	}

	void BoardUI::SetBlackScore(int score)
	{
		mBlackScore = score;
	}

	void BoardUI::SetGameOver(std::shared_ptr<Board> board)
	{
		mGameOver = board->IsGameOver();
	}
}