#pragma once
#include <memory>
#include <vector>

namespace Reversi
{
	class Board;

	class NodeReversi final
	{
	public:
		
		NodeReversi(Board board);
		//NodeReversi(std::shared_ptr<Board> board);
		//~Node();

		//int getData();
		//Node *getNext();


		//void setData(int value, int alpha, int beta);
		//void setNext(Node *);

		std::shared_ptr<Board> GetBoard();

		int GetValue();
		int GetAlpha();
		int GetBeta();
		int GetDepth();

		void SetValue(int value);
		void SetAlpha(int alpha);
		void SetBeta(int beta);
		void SetDepth(int depth);

		//const Library::Point& Location() const;

		std::vector<std::weak_ptr<NodeReversi>>& Neighbors();
		const std::vector<std::weak_ptr<NodeReversi>>& Neighbors() const;

		std::vector<std::weak_ptr<NodeReversi>>& Children();
		const std::vector<std::weak_ptr<NodeReversi>>& Children() const;

		void AddChild(std::shared_ptr<NodeReversi> child);

		std::weak_ptr<NodeReversi> Parent(); // const;
		void SetParent(std::shared_ptr<NodeReversi> parent);

		void Reset();

	private:
		std::shared_ptr<Board> mBoard;
		int mValue;
		int mAlpha;
		int mBeta;
		int mDepth;
		//int mINFINITY;

		//Library::Point mLocation;

		//Node *mNext;
		std::vector<std::weak_ptr<NodeReversi>> mNeighbors;
		std::vector<std::weak_ptr<NodeReversi>> mChildren;
		std::weak_ptr<NodeReversi> mParent;
	};
}