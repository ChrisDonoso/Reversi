#pragma once

#include "Game.h"
#include "Rectangle.h"
#include <limits.h>

#define INFINITY2 INT_MAX;
#define TWO_SECONDS 2000
const static int MAX_DEPTH = 1;

struct AIMove {
	int x;
	int y;
	int score;
};

namespace Library
{
	class KeyboardComponent;
}

namespace Reversi
{
	class Board;
	class BoardUI;
	class NodeReversi;

	class ReversiGame : public Library::Game
	{
	public:
		ReversiGame(std::function<void*()> getWindowCallback, std::function<void(SIZE&)> getRenderTargetSizeCallback);

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void Update(const Library::GameTime& gameTime) override;
		virtual void Draw(const Library::GameTime& gameTime) override;

		Library::Point test();

	private:
		void Exit();
		std::pair<int, int> GetBestMove(std::shared_ptr<NodeReversi> origin, int depth, bool maximizingPlayer);
		AIMove MiniMax(std::shared_ptr<NodeReversi> root, int depth, int alpha, int beta, bool maximizingPlayer);

		static const DirectX::XMVECTORF32 BackgroundColor;

		bool mWhiteCanMove;
		bool mBlackCanMove;

		std::shared_ptr<Library::KeyboardComponent> mKeyboard;
		std::shared_ptr<Library::MouseComponent> mMouse;
		std::shared_ptr<BoardUI> mBoardUI;

		std::shared_ptr<Board> mBoard;
		std::shared_ptr<NodeReversi> mRoot;

		std::shared_ptr<DirectX::SpriteFont> mSpriteFont14;

		Library::RenderStateHelper mRenderStateHelper;

		std::unique_ptr<DirectX::SoundEffect> mMusic;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mWhiteTexture;
		Library::Rectangle mBoundsWhite;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mBlackTexture;
		Library::Rectangle mBoundsBlack;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTileTexture;
		Library::Rectangle mBoundsTile;

	};
}
