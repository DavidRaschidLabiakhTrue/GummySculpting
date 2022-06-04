#include "Renderer.hpp"
using namespace RendererDefinition;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void RendererDefinition::Renderer::setDrawWireOn()
{
	this->shouldDrawWire = true;
}

void RendererDefinition::Renderer::setDrawWireOff()
{
	this->shouldDrawWire = false;
}

inline void RendererDefinition::Renderer::drawStandard()
{
	StandardShader.use();
	const int meshSize = meshes.size();
	for (int i = 0; i < meshSize; i++)
	{
		if (meshes[i].needToRefresh)
		{
			meshes[i].refresh();
			meshes[i].needToRefresh = false;
		}
		meshes[i].render();
	}
	//forall(mesh, meshes)
	//{
	//	if (mesh.needToRefresh)
	//	{
	//		mesh.refresh();
	//		mesh.needToRefresh = false;
	//	}
	//	mesh.render();
	//	// mesh.itreeDrawContainer.drawContainer();
	//	//mesh.drawOctreeWireframe();
	//}
}

inline void RendererDefinition::Renderer::drawWireFrame()
{
	
	if (this->shouldDrawWire)
	{
		WireFrameShader.use();
		GL::drawLined();
		forall(mesh, meshes)
		{
			mesh.render();
		}
		GL::drawFilled();
	}
	

}

void Renderer::clearDepthInfo()
{
	GL::clearDepthBuffer();
}

void Renderer::draw()
{
	drawStandard();
	drawWireFrame();
}

void RendererDefinition::Renderer::toggleWireFrame()
{
	this->shouldDrawWire = !this->shouldDrawWire;// flip
}


