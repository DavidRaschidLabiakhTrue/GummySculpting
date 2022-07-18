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


	for (auto i = meshes.begin(); i != meshes.end(); ++i)
	{
		StandardShader.uploadModelMatrixToGPU((*i).model);
		(*i).render();
	}

	activeMesh->drawOctreeWireframe(); // ShouldDraw handled inside function // sussy

}

inline void RendererDefinition::Renderer::drawWireFrame()
{

	if (this->shouldDrawWire)
	{
		WireFrameShader.use();
		GL::drawLined();
		const int meshSize = meshes.size();
		for (auto i = meshes.begin(); i != meshes.end(); ++i)
		{

			WireFrameShader.uploadModelMatrixToGPU((*i).model);
			(*i).render();
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
	if (thereIsMeshes()) // do not attempt to draw what doesn't exist(some functions are not memory safe inside).
	{
		drawStandard();
		drawWireFrame();
	}

}

void RendererDefinition::Renderer::toggleWireFrame()
{
	this->shouldDrawWire = !this->shouldDrawWire;// flip
}


