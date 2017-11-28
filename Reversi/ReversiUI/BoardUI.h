#pragma once

#include "Game.h"
#include "Rectangle.h"

namespace Library
{
	class KeyboardComponent;
}

namespace Board
{
	class BoardUI : public Library::Game
	{
	public:
		BoardUI(std::function<void*()> getWindowCallback, std::function<void(SIZE&)> getRenderTargetSizeCallback);

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void Update(const Library::GameTime& gameTime) override;
		virtual void Draw(const Library::GameTime& gameTime) override;


	private:
		void Exit();

		static const DirectX::XMVECTORF32 BackgroundColor;

		std::shared_ptr<Library::KeyboardComponent> mKeyboard;

		//Library::Rectangle mSpriteBounds;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mWhiteTexture;
		Library::Rectangle mBoundsWhite;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTileTexture;
		Library::Rectangle mBoundsTile;

	};
}
