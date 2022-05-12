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

	class Grid : public IndiceList, public GraphicsData
	{
		public:
			Grid();
			Grid(bool trueConstructor);
			~Grid();

			void bindGrid();
			void drawGrid();
			// no refresh method is required. It's a grid.

			bool shouldDrawGrid = true;
			
	};
}

#endif 
