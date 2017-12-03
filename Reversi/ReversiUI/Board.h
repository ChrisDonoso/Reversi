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
#include <vector>

namespace Reversi
{
	class Board final
	{
	public:
		Board();
		
		virtual void Initialize();

		bool IsValidMove(int x, int y);
		void CheckForAvailableMoves();
		std::list<Library::Point> GetMoves();
		int NumberOfAvailableMoves();
		bool CheckForAdjacentPiece(int x, int y);
		bool FlipPieces(int x, int y, bool flip, bool changePlayerTurn);
		void UpdateScore();
		int GetWhiteScore();
		int GetBlackScore();
		bool GetWhitePlayerTurn();
		void SetWhitePlayerTurn(bool flag);
		bool IsGameOver();
		void UpdateGameOver();
		void SetLastMoveMade(int x, int y);
		std::pair<int, int> GetLastMoveMade();
		char* GetBoard();
		int* GetAvailableMoves();
		void SetAIMove(int x, int y);

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

		std::list<Library::Point> mMoves;

		std::pair<int, int> mLastMoveMade;
	};
}