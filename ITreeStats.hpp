#ifndef ITreeStats_HPP
#define ITreeStats_HPP

#include "MeshStats.hpp"
#include "INode.hpp"
#include "IndexNodeList.hpp"
namespace ItreeStatsDefinition
{
	using namespace MeshStatsDefinition;
	using namespace IndexNodeListDefinition;
	using namespace INodeDefinition;

	typedef int ITreeDepth;
	typedef int ITreeNodeLimit;


	class ITreeStats : public MeshStats, public IndexNodeList
	{
		public:
			ITreeStats();
			~ITreeStats();

			const ITreeDepth itreeMaxDepth = 1000;

			ITreeDepth itreeCurrentDepth = -1;


			

	};
}
#endif // !ITreeStats_HPP
