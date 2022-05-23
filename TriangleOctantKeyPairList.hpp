#ifndef TriangleOctantKeyPairList_HPP
#define TriangleOctantKeyPairList_HPP

#include "TriangleOctantKeyPair.hpp"
#include "MeshStats.hpp"
#include "VertexList.hpp"
#include "IndiceList.hpp"

namespace TriangleOctantKeyPairListDefinition
{
	using namespace TriangleOctantKeyPairDefinition;
	using namespace MeshStatsDefinition;
	using namespace VertexListDefinition;
	using namespace IndiceListDefinition;

	typedef vector<TriangleOctantKeyPair> TriangleAndOctantPairList;

	class TriangleOctantKeyPairList : public MeshStats
	{
		public:
			TriangleOctantKeyPairList();
			~TriangleOctantKeyPairList();

			void loadTriangleOctantKeyPairList();


			TriangleAndOctantPairList triangleToOctantList;
	};



}



#endif // !TriangleOctantKeyPairList_HPP


