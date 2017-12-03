#include "stdafx.h"
#include "NodeReversi.h"
#include "Board.h"
#include <limits.h>

#define INFINITY2 INT_MAX;

using namespace Library;

namespace Reversi
{
	NodeReversi::NodeReversi(Board board)
	{
		mBoard = std::make_shared<Board>(board);
		mAlpha = -INFINITY2;
		mBeta = INFINITY2;
		mValue = INFINITY2;
	}

	std::shared_ptr<Board> NodeReversi::GetBoard()
	{
		return mBoard;
	}

	int NodeReversi::GetValue()
	{
		return mValue;
	}

	int NodeReversi::GetAlpha()
	{
		return mAlpha;
	}

	int NodeReversi::GetBeta()
	{
		return mBeta;
	}

	int NodeReversi::GetDepth()
	{
		return mDepth;
	}

	void NodeReversi::SetValue(int value)
	{
		mValue = value;
	}

	void NodeReversi::SetAlpha(int alpha)
	{
		mAlpha = alpha;
	}

	void NodeReversi::SetBeta(int beta)
	{
		mBeta = beta;
	}

	void NodeReversi::SetDepth(int depth)
	{
		mDepth = depth;
	}

	std::vector<std::weak_ptr<NodeReversi>>& NodeReversi::Children()
	{
		// TODO: insert return statement here
		return mChildren;
	}

	const std::vector<std::weak_ptr<NodeReversi>>& NodeReversi::Children() const
	{
		// TODO: insert return statement here
		return mChildren;
	}

	void NodeReversi::AddChild(std::shared_ptr<NodeReversi> child)
	{
		mChildren.emplace_back(child);
	}

	void NodeReversi::Reset()
	{
		for (auto& child : mChildren)
		{
			child.reset();
		}
	}
}