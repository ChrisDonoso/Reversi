#include "stdafx.h"
#include "ReversiGame.h"
#include "Board.h"
#include "BoardUI.h"
#include "Point.h"

using namespace std;
using namespace DirectX;
using namespace Library;
using namespace Microsoft::WRL;

namespace Reversi
{
	const XMVECTORF32 ReversiGame::BackgroundColor = Colors::BurlyWood;

	ReversiGame::ReversiGame(function<void*()> getWindowCallback, function<void(SIZE&)> getRenderTargetSizeCallback) :
		Game(getWindowCallback, getRenderTargetSizeCallback), mRenderStateHelper(*this), mBoundsWhite(Rectangle::Empty), mBoundsBlack(Rectangle::Empty), mBoundsTile(Rectangle::Empty)
	{
	}

	void ReversiGame::Initialize()
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

		mMouse = make_shared<MouseComponent>(*this, MouseModes::Absolute);
		mComponents.push_back(mMouse);
		mServices.AddService(MouseComponent::TypeIdClass(), mMouse.get());

		mBoardUI = make_shared<BoardUI>(*this);
		mComponents.push_back(mBoardUI);
		
		mBoard = make_shared<Board>();

		/*mBoard = make_shared<Board>(*this);
		mComponents.push_back(mBoard);*/

		//mWhiteCanMove = true;
		//mBlackCanMove = true;

		ComPtr<ID3D11Resource> textureResource;
		wstring textureName = L"Content\\Textures\\Tile.png";

		ThrowIfFailed(CreateWICTextureFromFile(this->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mTileTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");

		ComPtr<ID3D11Texture2D> texture;
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");

		mBoundsTile = TextureHelper::GetTextureBounds(texture.Get());

		mSpriteFont14 = make_unique<SpriteFont>(this->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");

		/*textureName = L"Content\\Textures\\blackCoin.png";
		ThrowIfFailed(CreateWICTextureFromFile(this->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mBlackTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");
		mBoundsBlack = TextureHelper::GetTextureBounds(texture.Get());

		textureName = L"Content\\Textures\\Tile.png";
		ThrowIfFailed(CreateWICTextureFromFile(this->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mTileTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");
		mBoundsTile = TextureHelper::GetTextureBounds(texture.Get());*/

		mBoard->Initialize();
		mBoardUI->Initialize();
		mBoardUI->SetBoard(mBoard);
		//mBoardUI->SetBoard(mBoard->GetBoard());
		mBoardUI->SetWhiteScore(mBoard->GetWhiteScore());
		mBoardUI->SetBlackScore(mBoard->GetBlackScore());
		//mBoardUI->SetWhiteScore(2)
		//mBoard->SetWhitePlayerTurn(false);
		Game::Initialize();
	}

	void ReversiGame::Shutdown()
	{
		BlendStates::Shutdown();
		SpriteManager::Shutdown();

		Game::Shutdown();
	}

	void ReversiGame::Update(const GameTime &gameTime)
	{
		//mBoard->SetDraw(true);

		if (mKeyboard->WasKeyPressedThisFrame(Keys::Escape))
		{
			Exit();
		}

		//mBoard->CheckForAvailableMoves();

		/*if (mBoard->NumberOfAvailableMoves() == 0)
		{
			if (mBoard->GetWhitePlayerTurn())
			{
				mWhiteCanMove = false;

			}
			else
			{
				mBlackCanMove = false;
			}

			if (mWhiteCanMove || mBlackCanMove)
			{
				mBoard->SetWhitePlayerTurn(!mBoard->GetWhitePlayerTurn());
			}
		}
		else
		{
			if (mBoard->GetWhitePlayerTurn())
			{
				mWhiteCanMove = true;

			}
			else
			{
				mBlackCanMove = true;
			}
		}*/

		// Select start node

		mBoard->CheckForAvailableMoves();

		mBoardUI->SetAvailableMoves(mBoard);
		
		if (mBoard->GetWhitePlayerTurn())
		{
			//mBoard->CheckForAvailableMoves();

			if (mMouse->WasButtonReleasedThisFrame(MouseButtons::Left))
			{
				int xpos = (mMouse->X() - 120) / 70; // Might need to change the 3
				int ypos = (mMouse->Y() - 20) / 70; // Might need to change the 1
													/*int xMouse = mMouse->X();
													int yMouse = mMouse->Y();*/

				if ((xpos >= 0 && xpos < 8) && (ypos >= 0 && ypos < 8))
				{
					if (mBoard->IsValidMove(xpos, ypos))
					{
						//mBoard->SetWhitePlayerTurn(!mBoard->GetWhitePlayerTurn());
						mBoard->SetWhitePlayerTurn(false);

						//mBoard->CheckForAvailableMoves();
					}
					/*if (mGraph.At(xpos, ypos)->Type() != NodeType::Wall)
					{
					mStartNode = mGraph.At(xpos, ypos);
					}*/

					// Check for valid move.
				}
			}
		}
		else
		{
			/*for (auto& move : mBoard->GetMoves())
			{
				int x = move.X;
				int y = move.Y;

				UNREFERENCED_PARAMETER(x);
				UNREFERENCED_PARAMETER(y);
			}*/

			mBoard->CheckForAvailableMoves();

			clock_t timer = clock();

			while (clock() - timer < TWO_SECONDS)
			{

			}
			/*if (clock() - timer >= THREE_SECONDS)
			{*/

			//std::weak_ptr<Board> board = mBoard;

			std::pair<int, int> move = GetBestMove(mBoard, false, 1);
			
			mBoard->FlipPieces(move.first, move.second, true);
			mBoard->SetAIMove(move.first, move.second);

			mBoard->SetWhitePlayerTurn(true);
			//}
		}

		mBoardUI->SetWhiteScore(mBoard->GetWhiteScore());
		mBoardUI->SetBlackScore(mBoard->GetBlackScore());
		mBoard->UpdateGameOver();
		mBoardUI->SetGameOver(mBoard);

		Game::Update(gameTime);
	}

	void ReversiGame::Draw(const Library::GameTime & gameTime)
	{
		mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), reinterpret_cast<const float*>(&BackgroundColor));
		mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		// Offsets for grid placement
		float xpos = 610.0f;
		float ypos = 510.0f;

		// Draw the graph textures to the screen (Start node, End node, Normal nodes, and Wall nodes)
		for (int row = 7; row >= 0; row--)
		{
			for (int col = 7; col >= 0; col--)
			{
				SpriteManager::DrawTexture2D(mTileTexture.Get(), XMFLOAT2(xpos, ypos));
			
				xpos -= mBoundsTile.Width;
			}

			// Reset offset for x position
			xpos = 610.0f;
			ypos -= mBoundsTile.Height;
		}

		//mBoardUI->Draw(gameTime);

		// RIGHT HERE IS WHERE WE DRAW THE CONTENTS OF THE BOARD
		/*for (int row = 0; row < 8; row++)
		{
			for (int col = 0; col < 8; col++)
			{
				mBoard->Draw();
			}
		}*/

		wostringstream gameOver;

		if (mBoard->IsGameOver())
		{
			if (mBoard->GetWhiteScore() > mBoard->GetBlackScore())
			{
				gameOver << L"Game Over. White wins!";
			}
			else if (mBoard->GetWhiteScore() < mBoard->GetBlackScore())
			{
				gameOver << L"Game Over. Black wins!";
			}
			else
			{
				gameOver << L"Game Over. It is a draw!";
			}

			mRenderStateHelper.SaveAll();
			SpriteManager::DrawString(mSpriteFont14, gameOver.str().c_str(), XMFLOAT2(293, 0));
			mRenderStateHelper.RestoreAll();
		}

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

	Library::Point ReversiGame::test()
	{
		return Library::Point();
	}

	void ReversiGame::Exit()
	{
		PostQuitMessage(0);
	}

	// Driver for MiniMax function
	std::pair<int, int> ReversiGame::GetBestMove(std::shared_ptr<Board> board, bool whitePlayer, int maxDepth)
	{
		AIMove move = MiniMax(board, whitePlayer, maxDepth, 0);

		return std::pair<int, int>(move.x, move.y);
	}

	AIMove ReversiGame::MiniMax(std::shared_ptr<Board> board, bool whitePlayer, int maxDepth, int currentDepth)
	{
		AIMove move;

		// Initialize AIMove struct for move
		move.x = -1;
		move.y = -1;
		move.score = -1;

		AIMove bestMove;

		// Initialize AIMove struct for bestMove
		bestMove.x = -1;
		bestMove.y = -1;
		bestMove.score = -1;


		if (board->IsGameOver() || currentDepth == maxDepth)
		{
			if (whitePlayer)
			{
				move.score = board->GetBlackScore();
			}
			else
			{
				move.score = board->GetWhiteScore();
			}

			std::pair<int, int> lastMoveMade = board->GetLastMoveMade();
			move.x = lastMoveMade.first;
			move.y = lastMoveMade.second;

			return move;
		}

		if (board->GetWhitePlayerTurn() == whitePlayer)
		{
			bestMove.score = -INFINITY2;
		}
		else
		{
			bestMove.score = INFINITY2;
		}

		board->CheckForAvailableMoves();

		// Go through each move
		for (auto& availableMove : board->GetMoves())
		{
			std::shared_ptr<Board> newBoard = make_shared<Board>(*board);

			//newBoard.lock()->SetDraw(false);
			//newBoard->Evaluate(availableMove.X, availableMove.Y);
			newBoard->FlipPieces(availableMove.X, availableMove.Y, true);

			move = MiniMax(newBoard, !whitePlayer, maxDepth, currentDepth + 1);

			// Update the best score
			if (board->GetWhitePlayerTurn() == whitePlayer)
			{
				if (move.score > bestMove.score)
				{
					bestMove = move;
				}
			}
			else
			{
				if (move.score < bestMove.score)
				{
					bestMove = move;
				}
			}
		}

		return bestMove;
	}
}