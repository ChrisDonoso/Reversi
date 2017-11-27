#pragma once

#include "Game.h"
#include "DrawableGameComponent.h"
#include "Game.h"
#include "Rectangle.h"
#include <d3d11_2.h>
#include <DirectXMath.h>
#include <wrl.h>


namespace Board
{
	class Disks : public Library::DrawableGameComponent
	{
	public:
		Disks(Library::Game& game);

		const Library::Rectangle& Bounds() const;

		virtual void Initialize() override;
		//virtual void Update(const Library::GameTime& gameTime) override;
		virtual void Draw(const Library::GameTime& gameTime) override;


		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mWhiteTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mBlackTexture;

	private:
	

		Library::Rectangle mBounds;

	};
}
