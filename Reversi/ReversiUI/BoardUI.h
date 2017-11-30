#pragma once

#include "Game.h"
#include "Rectangle.h"
#include "Graph.h"

namespace Library
{
	class KeyboardComponent;
}

namespace Board
{
	class Board;

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

		bool mWhiteCanMove;
		bool mBlackCanMove;

		std::shared_ptr<Library::KeyboardComponent> mKeyboard;
		std::shared_ptr<Library::MouseComponent> mMouse;
		std::shared_ptr<Board> mBoard;

		std::shared_ptr<DirectX::SpriteFont> mSpriteFont14;

		Library::RenderStateHelper mRenderStateHelper;

		//Library::Rectangle mSpriteBounds;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mWhiteTexture;
		Library::Rectangle mBoundsWhite;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mBlackTexture;
		Library::Rectangle mBoundsBlack;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTileTexture;
		Library::Rectangle mBoundsTile;

	};
}
