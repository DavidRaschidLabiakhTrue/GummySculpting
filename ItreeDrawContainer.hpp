#ifndef ITreeDrawContainer_HPP
#define ITreeDrawContainer_HPP

#include "ITree.hpp"
#include "IndiceList.hpp"
#include "GraphicsData.hpp"

namespace ITreeDrawContainerDefinition
{

	using namespace IndiceListDefinition;
	using namespace GraphicsDataDefinition;

	// contains a seperate - uninteractable copy of the Itree data meant for single shot static rendering *only*.
	struct ItreeDrawContainer
	{
		public:
			ItreeDrawContainer();
			~ItreeDrawContainer();

			void bindContainer();
			void drawContainer();


			Indices itreeDrawIndices;
			Vertices itreeDrawVertex;

			GraphicsBufferObject gboITreeDrawContainer;

			bool shoulddraw = true;
	};

}

#endif
