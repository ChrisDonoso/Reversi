#pragma once

/*
Board should have:
An array mBoard
bool mWhitePlayer
mWhiteScore
mBlackScore
*/

namespace Board
{
	class Board final : public Library::DrawableGameComponent
	{
	public:
		Board(Library::Game& game);
		
		virtual void Initialize() override;
		virtual void Update(const Library::GameTime& gameTime) override;
		virtual void Draw(const Library::GameTime& gameTime) override;

	private:
		char mBoard[8][8];

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mWhiteTexture;
		Library::Rectangle mBoundsWhite;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mBlackTexture;
		Library::Rectangle mBoundsBlack;
	};
}