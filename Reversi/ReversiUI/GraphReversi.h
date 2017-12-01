#pragma once

#include "Point.h"
#include "NodeReversi.h"
#include <vector>
//#include <map>

namespace Board
{
	class GraphReversi final
	{
	public:
		//const std::map<Library::Point, std::shared_ptr<NodeReversi>>& Nodes() const;
		const std::vector<std::shared_ptr<NodeReversi>>& Nodes() const;

		void AddNode(std::shared_ptr<NodeReversi> node);
		/*void Reset();
		std::shared_ptr<NodeReversi> At(const Library::Point& location) const;
		std::shared_ptr<NodeReversi> At(const int x, const int y) const;
		bool Contains(const Library::Point& location) const;
		bool Contains(const int x, const int y) const;*/

	private:
		std::vector<std::shared_ptr<NodeReversi>> mNodes;
		//std::map<Library::Point, std::shared_ptr<NodeReversi>> mNodes;
	};
}