#include "stdafx.h"
#include "Node.h"

namespace Board
{
	Node *Node::getNext()
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
	}
}