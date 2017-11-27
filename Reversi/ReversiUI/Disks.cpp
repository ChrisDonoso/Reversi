#include "stdafx.h"
#include "Disks.h"
#include "BoardUI.h"
#include "GridHelper.h"

using namespace DirectX;
using namespace Library;
using namespace std;
using namespace Microsoft::WRL;

namespace Board
{
	Disks::Disks(Game& game) :
		DrawableGameComponent(game), mBounds(Rectangle::Empty)
	{
	}

	const Library::Rectangle& Disks::Bounds() const
	{
		return mBounds;
	}

	void Disks::Initialize()
	{
		// Load a texture
		ComPtr<ID3D11Resource> textureResource;
		ComPtr<ID3D11Texture2D> texture;

		//ISSUE ACQUIRING TEXTURE

		wstring textureName = L"Content\\Textures\\White.png";
		ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mWhiteTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");

		//textureName = L"Content\\Textures\\Black.png";
		//ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mBlackTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");
		//ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");

		mBounds = TextureHelper::GetTextureBounds(texture.Get());
	}

	void Disks::Draw(const Library::GameTime & gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);

		string filename = "Content\\Grid\\Grid.grid";

		int32_t gridWidth;
		int32_t gridHeight;

		Graph graph = GridHelper::LoadGridFromFile(filename, gridWidth, gridHeight);

		float x = 0;
		float y = 100;

		for (int col = 0; col < gridWidth; col++)
		{
			for (int row = 0; row < gridHeight; row++)
			{
				if (graph.At(row, col)->Type() == NodeType::White)
				{
					//SpriteManager::DrawTexture2D(mWhiteTexture.Get(), XMFLOAT2(x, y));
				}

				if (graph.At(row, col)->Type() == NodeType::Black)
				{
					//SpriteManager::DrawTexture2D(mBlackTexture.Get(), XMFLOAT2(x, y));
				}

				x += mBounds.Width;

				if (x >= (mBounds.Width * gridWidth))
				{
					y += mBounds.Height;
					x = 0;
				}
			}
		}
	}
}