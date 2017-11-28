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
}