#pragma once
#include <memory>
#include <vector>

namespace Board
{
	class Board;

	class NodeReversi final
	{
	public:
		
		NodeReversi(std::shared_ptr<Board> board);
		//~Node();

		//int getData();
		//Node *getNext();


		//void setData(int value, int alpha, int beta);
		//void setNext(Node *);

		std::shared_ptr<Board> GetBoard();

		int GetValue();
		int GetAlpha();
		int GetBeta();

		void SetValue(int value);
		void SetAlpha(int alpha);
		void SetBeta(int beta);

		//const Library::Point& Location() const;

		std::vector<std::weak_ptr<NodeReversi>>& Neighbors();
		const std::vector<std::weak_ptr<NodeReversi>>& Neighbors() const;

		std::vector<std::weak_ptr<NodeReversi>>& Children();
		const std::vector<std::weak_ptr<NodeReversi>>& Children() const;

		std::weak_ptr<NodeReversi> Parent(); // const;
		void SetParent(std::shared_ptr<NodeReversi> parent);

		void Reset();

	private:
		std::shared_ptr<Board> mBoard;
		int mValue;
		int mAlpha;
		int mBeta;
		//int mINFINITY;

		//Library::Point mLocation;

		//Node *mNext;
		std::vector<std::weak_ptr<NodeReversi>> mNeighbors;
		std::vector<std::weak_ptr<NodeReversi>> mChildren;
		std::weak_ptr<NodeReversi> mParent;

	};
}