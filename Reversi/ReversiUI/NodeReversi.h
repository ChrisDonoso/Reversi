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

		std::shared_ptr<Board> GetBoard();

		int GetValue();
		int GetAlpha();
		int GetBeta();
		int GetDepth();

		void SetValue(int value);
		void SetAlpha(int alpha);
		void SetBeta(int beta);
		void SetDepth(int depth);

		std::vector<std::weak_ptr<NodeReversi>>& Children();
		const std::vector<std::weak_ptr<NodeReversi>>& Children() const;

		void AddChild(std::shared_ptr<NodeReversi> child);

		void Reset();

	private:
		std::shared_ptr<Board> mBoard;
		int mValue;
		int mAlpha;
		int mBeta;
		int mDepth;

		std::vector<std::weak_ptr<NodeReversi>> mChildren;
	};
}