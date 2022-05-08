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
	

	class Renderer : public Mesh_Manager
	{
		public:
			 Renderer();
			 ~Renderer();
			
			void draw(); // draw all meshes to GPU

			void setDrawWireOn();
			void setDrawWireOff();

		protected:

			bool shouldDrawWire = true;

			inline void drawStandard();
			inline void drawWireFrame();
			

			
	};
}

#endif // !Renderer_HPP
