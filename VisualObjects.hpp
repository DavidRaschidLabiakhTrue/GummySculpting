#ifndef VisualObjects_HPP
#define VisualObjects_HPP

#include "Grid.hpp"

namespace VisualObjectsDefinition
{
	using namespace GridDefinition;
	// container for static drawn objects that do not change in 3D.
	class VisualObjects
	{
		public:
			VisualObjects();
			VisualObjects(bool trueConstructor);
			~VisualObjects();
			
			void drawVisualObjects();

			Grid grid;

	};
}

#endif // !VisualObjects_HPP

