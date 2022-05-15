#ifndef ITree_HPP
#define ITree_HPP

#include "ITreeStats.hpp"
#include "SamplerPayload.hpp"

namespace ITreeDefinition
{
	using namespace ItreeStatsDefinition;
	using namespace SamplerPayloadDefinition;
	// indexed based octree
	class ITree : public ITreeStats
	{
		public:
			ITree();
			~ITree();

			void itreeGenerate();
			void itreeGenerateRoot();

			void inodeSubdivide(INodeID id); // subdivide an node into 8 more nodes
	};
}


#endif