#ifndef IndexNodeList_HPP
#define IndexNodeList_HPP

#include "INode.hpp"
#include "SamplerPayload.hpp"
namespace IndexNodeListDefinition
{
	using namespace INodeDefinition;
	using namespace SamplerPayloadDefinition;

	typedef vector<INode> INodeList;

	class IndexNodeList
	{
		public:
			IndexNodeList();
			~IndexNodeList();

			const int inodesTotal();

			auto inodesSearch(SamplerPayloadReference payload);

			INodeList inodes;

	};
}

#endif
