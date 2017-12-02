#include "stdafx.h"
#include "GraphReversi.h"

using namespace Library;

namespace Reversi 
{
	/*GraphReversi::GraphReversi()
	{
		
	}*/

	/*const std::map<Point, std::shared_ptr<NodeReversi>>& GraphReversi::Nodes() const
	{
		return mNodes;
	}*/

	const std::vector<std::shared_ptr<NodeReversi>>& GraphReversi::Nodes() const
	{
		return mNodes;
	}

	void GraphReversi::AddNode(std::shared_ptr<NodeReversi> node)
	{

		/*if (mNodes.find(node->Location()) != mNodes.end())
		{
			throw exception("Node with the same location already exists.");
		}

		mNodes.insert(make_pair(node->Location(), node));*/
		mNodes.emplace_back(node);
	}

	/*void GraphReversi::Reset()
	{
		for (auto& pair : mNodes)
		{
			pair.second->Reset();
		}
	}

	std::shared_ptr<NodeReversi> GraphReversi::At(const Point & location) const
	{
		return mNodes.at(location);
	}

	std::shared_ptr<NodeReversi> GraphReversi::At(const int x, const int y) const
	{
		return At(Point(x, y));
	}

	bool GraphReversi::Contains(const Point & location) const
	{
		return mNodes.find(location) != mNodes.end();
	}

	bool GraphReversi::Contains(const int x, const int y) const
	{
		return Contains(Point(x, y));
	}*/
}