#ifndef TriangleOctantKeyPairList_HPP
#define TriangleOctantKeyPairList_HPP

#include "TriangleOctantKeyPair.hpp"
#include "ITreeVisualization.hpp"

namespace TriangleOctantKeyPairListDefinition
{
	using namespace TriangleOctantKeyPairDefinition;
	using namespace ITreeVisualizationDefinition;

	typedef vector<TriangleOctantKeyPair> TriangleAndOctantPairList;

	class TriangleOctantKeyPairList : public ITreeVisualization
	{
		public:
			TriangleOctantKeyPairList();
			~TriangleOctantKeyPairList();

			void loadTriangleOctantKeyPairList();


			TriangleAndOctantPairList triangleToOctantList;
	};



}



#endif // !TriangleOctantKeyPairList_HPP


