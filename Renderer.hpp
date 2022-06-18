#ifndef Renderer_HPP
#define Renderer_HPP
#include "Macro.hpp"

#include "Mesh.hpp"

#include "Mesh_Manager.hpp"
#include "Shader.hpp"

namespace RendererDefinition
{
	Usage Macros;
	Usage Mesh_Manager_Definition;
	Usage ShaderDefinition;
	
	// the class that draws meshes to the screen. in gummy, the renderer is what technically controls meshes as well.
	class Renderer : public Mesh_Manager
	{
		public:
			 Renderer();
			 ~Renderer();
			
			void draw(); // draw all meshes to GPU

			void toggleWireFrame();

			void setDrawWireOn();
			void setDrawWireOff();
			void clearDepthInfo();

		protected:

			bool drawingITreeContainer = true;

			bool shouldDrawWire = true;

			inline void drawStandard();
			inline void drawWireFrame();
			

			
	};
}

#endif // !Renderer_HPP

