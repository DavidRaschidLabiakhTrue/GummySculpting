#ifndef Grid_HPP
#define Grid_HPP

#include "GraphicsData.hpp"
#include "IndiceList.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
namespace GridDefinition
{
	using namespace IndiceListDefinition;
	using namespace GraphicsDataDefinition;
	using namespace CameraDefinition;
	using namespace ShaderDefinition;

	// visual 3D drawn grid
	class Grid : public IndiceList, public GraphicsData
	{
		public:
			Grid();
			Grid(bool trueConstructor);
			~Grid();

			void bindGrid(); // bind the grid to the gpu
			void drawGrid(); // draw the grid

			// no refresh method is required. It's a grid.

			bool shouldDrawGrid = true;
			
	};
}

#endif 
