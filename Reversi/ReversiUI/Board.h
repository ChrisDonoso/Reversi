#pragma once

/*
Board should have:
An array mBoard
bool mWhitePlayer
mWhiteScore
mBlackScore
*/

#include <list>
#include <Point.h>
//#include <memory>

namespace Board
{
	class Board final : public Library::DrawableGameComponent
	{
	public:
		Board(Library::Game& game);
		
		virtual void Initialize() override;
		virtual void Update(const Library::GameTime& gameTime) override;
		virtual void Draw(const Library::GameTime& gameTime) override;

		bool IsValidMove(int x, int y);
		void CheckForAvailableMoves();
		std::list<Library::Point> GetMoves();
		int NumberOfAvailableMoves();
		bool CheckForAdjacentPiece(int x, int y);
		//bool CheckForClosingPiece(int x, int y);
		bool FlipPieces(int x, int y, bool flip);
		void Evaluate(int x, int y);
		void UpdateScore();
		int GetWhiteScore();
		int GetBlackScore();
		bool GetWhitePlayerTurn();
		void SetWhitePlayerTurn(bool flag);
		bool IsGameOver();
		void SetDraw(bool flag);
		void SetLastMoveMade(int x, int y);
		std::pair<int, int> GetLastMoveMade();

	private:
		char mBoard[8][8];
		int mAvailableMoves[8][8];

		int mWhiteScore;
		int mBlackScore;
		int mNumAvailableMoves;

		bool mWhitePlayerTurn;
		bool mWhiteCanMove;
		bool mBlackCanMove;
		bool mGameOver;
		bool mDraw;

		std::list<Library::Point> mMoves;

		std::pair<int, int> mLastMoveMade;

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