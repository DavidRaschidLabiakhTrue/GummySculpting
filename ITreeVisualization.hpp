#ifndef ITreeVisualization_HPP
#define ITreeVisualization_HPP

#include "ITree.hpp"
#include "ItreeDrawContainer.hpp"

namespace ITreeVisualizationDefinition
{
	using namespace ITreeDefinition;
	using namespace ITreeDrawContainerDefinition;

	// visualization class that builds a drawn item based off the ITree. - to be made a compile time class
	class ITreeVisualization : public ITree
	{
		public:
			ITreeVisualization();
			~ITreeVisualization();

			void generateITreeVisualization();

			ItreeDrawContainer itreeDrawContainer;
			

	};
}

#endif // !ITreeVisualization_HPP

