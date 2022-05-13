#ifndef TriangleOctantKeyPairList_HPP
#define TriangleOctantKeyPairList_HPP

#include "TriangleOctantKeyPair.hpp"

namespace TriangleOctantKeyPairListDefinition
{
	using namespace TriangleOctantKeyPairDefinition;

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


