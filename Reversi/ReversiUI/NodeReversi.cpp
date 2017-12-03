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
		// SET VALUES TO NEG OR POS INFINITY???
		//mValue = INFINITY;
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

	/*const Point & NodeReversi::Location() const
	{
		return mLocation;
	}*/

	std::vector<std::weak_ptr<NodeReversi>>& NodeReversi::Neighbors()
	{
		return mNeighbors;
		// TODO: insert return statement here
	}

	const std::vector<std::weak_ptr<NodeReversi>>& NodeReversi::Neighbors() const
	{
		return mNeighbors;
		// TODO: insert return statement here
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

	std::weak_ptr<NodeReversi> NodeReversi::Parent()
	{
		return mParent;
	}

	void NodeReversi::SetParent(std::shared_ptr<NodeReversi> parent)
	{
		mParent = parent;
	}

	void NodeReversi::Reset()
	{
		// Reset some variables here?
		//mParent.reset();

		for (auto& child : mChildren)
		{
			child.reset();
		}
	}
	/*Node *Node::getNext()
	{
		return mNext;
	}
	void Node::setData(int value, int alpha, int beta)
	{
		mValue = value;
		mAlpha = alpha;
		mBeta = beta;
	}
	void Node::setNext(Node *next)
	{
		mNext = next;
	}*/
}