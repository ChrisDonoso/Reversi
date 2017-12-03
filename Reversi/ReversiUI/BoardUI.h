#pragma once

#include <vector>

namespace Reversi
{
	class Board;

	class BoardUI final : public Library::DrawableGameComponent
	{
	public:
		BoardUI(Library::Game& game);

		virtual void Initialize() override;
		virtual void Update(const Library::GameTime& gameTime) override;
		virtual void Draw(const Library::GameTime& gameTime) override;

		void SetBoard(std::shared_ptr<Board> board);
		void SetAvailableMoves(std::shared_ptr<Board> board);
		void SetWhiteScore(int score);
		void SetBlackScore(int score);
		void SetWhitePlayerTurn(bool flag);
		void SetGameOver(bool gameover);

	private:
		char *mBoard;
		int *mAvailableMoves;

		int mWhiteScore;
		int mBlackScore;

		bool mWhitePlayerTurn;
		bool mGameOver;

		std::shared_ptr<DirectX::SpriteFont> mSpriteFont14;

		Library::RenderStateHelper mRenderStateHelper;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mWhiteTexture;
		Library::Rectangle mBoundsWhite;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mBlackTexture;
		Library::Rectangle mBoundsBlack;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mAvailableTexture;
		Library::Rectangle mBoundsAvailable;
	};
}
