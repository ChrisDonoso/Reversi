#include "stdafx.h"
#include "BoardUI.h"


using namespace std;
using namespace DirectX;
using namespace Library;
using namespace Microsoft::WRL;

namespace Board
{
	const XMVECTORF32 BoardUI::BackgroundColor = Colors::BurlyWood;

	BoardUI::BoardUI(function<void*()> getWindowCallback, function<void(SIZE&)> getRenderTargetSizeCallback) :
		Game(getWindowCallback, getRenderTargetSizeCallback), mSpriteBounds(Rectangle::Empty)
	{
	}

	void BoardUI::Initialize()
	{
		// Load a texture
		/*ComPtr<ID3D11Resource> textureResource;
		wstring textureName = L"Content\\Textures\\WhiteDisk.png";

		ThrowIfFailed(CreateWICTextureFromFile(Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mWhiteTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");

		ComPtr<ID3D11Texture2D> texture;
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");*/



		SpriteManager::Initialize(*this);
		BlendStates::Initialize(mDirect3DDevice.Get());

		mKeyboard = make_shared<KeyboardComponent>(*this);
		mComponents.push_back(mKeyboard);
		mServices.AddService(KeyboardComponent::TypeIdClass(), mKeyboard.get());

		ComPtr<ID3D11Resource> textureResource;
		wstring textureName = L"Content\\Textures\\WhiteDisk.png";

		ThrowIfFailed(CreateWICTextureFromFile(this->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mWhiteTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");

		ComPtr<ID3D11Texture2D> texture;
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");

		Game::Initialize();
	}

	void BoardUI::Shutdown()
	{
		BlendStates::Shutdown();
		SpriteManager::Shutdown();

		Game::Shutdown();
	}

	void BoardUI::Update(const GameTime &gameTime)
	{
		if (mKeyboard->WasKeyPressedThisFrame(Keys::Escape))
		{
			Exit();
		}

		Game::Update(gameTime);
	}

	void BoardUI::Draw(const Library::GameTime & gameTime)
	{
		mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), reinterpret_cast<const float*>(&BackgroundColor));
		mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		Game::Draw(gameTime);

		HRESULT hr = mSwapChain->Present(1, 0);

		// If the device was removed either by a disconnection or a driver upgrade, we must recreate all device resources.
		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			HandleDeviceLost();
		}
		else
		{
			ThrowIfFailed(hr, "IDXGISwapChain::Present() failed.");
		}
	}

	void BoardUI::Exit()
	{
		PostQuitMessage(0);
	}

}