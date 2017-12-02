#pragma once

//#include <memory>
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

		//void SetBoard(std::vector<std::vector<char>> board);// board[8][8]);
		void SetBoard(std::shared_ptr<Board> board);//char* board);//[][8]);
		void SetWhiteScore(int score);
		void SetBlackScore(int score);

	private:
		//std::vector<std::vector<char>> mBoard;
		//char mBoard[8][8];
		char *mBoard;

		int mWhiteScore;
		int mBlackScore;

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
