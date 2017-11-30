#pragma once

namespace Board
{
	class Node 
	{
	public:
		
		Node();
		~Node();

		int getData();
		Node *getNext();

		void setData(int value, int alpha, int beta);
		void setNext(Node *);

	private:
		int mValue;
		int mAlpha;
		int mBeta;

		Node *mNext;

	};
}