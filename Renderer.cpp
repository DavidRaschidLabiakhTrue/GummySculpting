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
		StandardShader.uploadModelMatrixToGPU(meshes[i].model);
		meshes[i].render();
	}
	if (activeMesh->octreeWireframe.shouldDraw)
	{
		activeMesh->drawOctreeWireframe();
	}

}

inline void RendererDefinition::Renderer::drawWireFrame()
{
	
	if (this->shouldDrawWire)
	{
		WireFrameShader.use();
		GL::drawLined();
		const int meshSize = meshes.size();
		for (int i = 0; i < meshSize; i++)
		{

			StandardShader.uploadModelMatrixToGPU(meshes[i].model);
			meshes[i].render();
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


