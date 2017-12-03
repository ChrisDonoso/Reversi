#include "stdafx.h"
#include "ReversiGame.h"
#include "Board.h"
#include "BoardUI.h"
#include "NodeReversi.h"
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
		SpriteManager::Initialize(*this);
		BlendStates::Initialize(mDirect3DDevice.Get());

		mKeyboard = make_shared<KeyboardComponent>(*this);
		mComponents.push_back(mKeyboard);
		mServices.AddService(KeyboardComponent::TypeIdClass(), mKeyboard.get());

		mMouse = make_shared<MouseComponent>(*this, MouseModes::Absolute);
		mComponents.push_back(mMouse);
		mServices.AddService(MouseComponent::TypeIdClass(), mMouse.get());

		auto audioEngine = make_shared<AudioEngineComponent>(*this);
		assert(audioEngine != nullptr);
		mComponents.push_back(audioEngine);
		mServices.AddService(AudioEngineComponent::TypeIdClass(), audioEngine.get());

		mBoardUI = make_shared<BoardUI>(*this);
		mComponents.push_back(mBoardUI);
		
		mBoard = make_shared<Board>();

		mMusic = make_unique<SoundEffect>(audioEngine->AudioEngine().get(), L"Content\\Sound\\Patakas-World.wav");

		ComPtr<ID3D11Resource> textureResource;
		wstring textureName = L"Content\\Textures\\Tile.png";

		ThrowIfFailed(CreateWICTextureFromFile(this->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mTileTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");

		ComPtr<ID3D11Texture2D> texture;
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");

		mBoundsTile = TextureHelper::GetTextureBounds(texture.Get());

		mSpriteFont14 = make_unique<SpriteFont>(this->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");

		mBoard->Initialize();

		mBoardUI->Initialize();
		mBoardUI->SetBoard(mBoard);
		mBoardUI->SetWhiteScore(mBoard->GetWhiteScore());
		mBoardUI->SetBlackScore(mBoard->GetBlackScore());

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
		if (mKeyboard->WasKeyPressedThisFrame(Keys::Escape))
		{
			Exit();
		}

		// Loops the background music
		if (!mMusic->IsInUse())
		{
			mMusic->Play();
		}

		mBoard->CheckForAvailableMoves();

		mBoardUI->SetAvailableMoves(mBoard);
		
		if (mBoard->GetWhitePlayerTurn())
		{
			if (mMouse->WasButtonReleasedThisFrame(MouseButtons::Left))
			{
				int xpos = (mMouse->X() - 120) / 70;
				int ypos = (mMouse->Y() - 20) / 70;

				if ((xpos >= 0 && xpos < 8) && (ypos >= 0 && ypos < 8))
				{
					if (mBoard->IsValidMove(xpos, ypos))
					{
						//mBoard->SetWhitePlayerTurn(!mBoard->GetWhitePlayerTurn());
						mBoard->SetWhitePlayerTurn(false);
						mBoardUI->SetWhitePlayerTurn(false);
					}
				}
			}
		}
		else
		{
			mBoard->CheckForAvailableMoves();

			clock_t timer = clock();

			while (clock() - timer < TWO_SECONDS)
			{
				// WAIT TWO SECONDS SO THAT IT GIVES THE PLAYER A CHANCE TO SEE WHAT HAPPENED
			}

			mRoot.reset();

			mRoot = make_shared<NodeReversi>(*mBoard);

			std::pair<int, int> move = GetBestMove(mRoot, 0, true);
			
			mBoard->FlipPieces(move.first, move.second, true, false);
			mBoard->SetAIMove(move.first, move.second);

			mBoard->SetWhitePlayerTurn(true);
			mBoardUI->SetWhitePlayerTurn(true);
		}

		mBoardUI->SetWhiteScore(mBoard->GetWhiteScore());
		mBoardUI->SetBlackScore(mBoard->GetBlackScore());
		mBoard->UpdateGameOver();
		mBoardUI->SetGameOver(mBoard->IsGameOver());

		Game::Update(gameTime);
	}

	void ReversiGame::Draw(const Library::GameTime & gameTime)
	{
		mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), reinterpret_cast<const float*>(&BackgroundColor));
		mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		// Offsets for grid placement
		float xpos = 610.0f;
		float ypos = 510.0f;

		// Draw the Reversi Grid textures to the screen
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
	std::pair<int, int> ReversiGame::GetBestMove(std::shared_ptr<NodeReversi> origin, int depth, bool maximizingPlayer)
	{
		AIMove move = MiniMax(origin, depth, INT_MIN, INT_MAX, maximizingPlayer);

		return std::pair<int, int>(move.x, move.y);
	}

	AIMove ReversiGame::MiniMax(std::shared_ptr<NodeReversi> root, int depth, int alpha, int beta, bool maximizingPlayer)
	{
		shared_ptr<NodeReversi> node = make_shared<NodeReversi>(*root->GetBoard());

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

		if (node->GetBoard()->IsGameOver() || depth == MAX_DEPTH)
		{
			if (maximizingPlayer)
			{
				move.score = node->GetBoard()->GetWhiteScore();
			}
			else
			{
				move.score = node->GetBoard()->GetBlackScore();
			}

			std::pair<int, int> lastMoveMade = node->GetBoard()->GetLastMoveMade();
			move.x = lastMoveMade.first;
			move.y = lastMoveMade.second;

			return move; 
		}

		node->GetBoard()->CheckForAvailableMoves();

		if (maximizingPlayer)
		{
			bestMove.score = -INFINITY2;

			for (auto& availableMove : node->GetBoard()->GetMoves())
			{
				std::shared_ptr<Board> newBoard = make_shared<Board>(*node->GetBoard());

				std::shared_ptr<NodeReversi> child = make_shared<NodeReversi>(*newBoard);

				node->AddChild(child);

				child->GetBoard()->FlipPieces(availableMove.X, availableMove.Y, true, true);

				move = MiniMax(child, depth + 1, alpha, beta, false);

				if (move.score > bestMove.score)
				{
					bestMove = move;
				}

				alpha = max(alpha, child->GetAlpha());

				// Alpha Beta Pruning
				if (beta <= alpha)
				{
					break;
				}
			}

			return bestMove;
		}
		else
		{
			bestMove.score = INFINITY2;

			for (auto& availableMove : node->GetBoard()->GetMoves())
			{
				std::shared_ptr<Board> newBoard = make_shared<Board>(*node->GetBoard());

				std::shared_ptr<NodeReversi> child = make_shared<NodeReversi>(*newBoard);

				node->AddChild(child);

				child->GetBoard()->FlipPieces(availableMove.X, availableMove.Y, true, true);

				move = MiniMax(child, depth + 1, alpha, beta, true);

				if (move.score < bestMove.score)
				{
					bestMove = move;
				}

				beta = min(beta, child->GetBeta());

				// Alpha Beta Pruning
				if (beta <= alpha)
				{
					break;
				}
			}

			return bestMove;
		}
	}
}