#include "Cursor.hpp"
#include "ToolsWindow.hpp"

using namespace _Cursor;

_Cursor::Cursor::Cursor()
{

}

_Cursor::Cursor::Cursor(bool trueConstructor) : StaticCircle(trueConstructor)
{
	this->radius = 0;
}

_Cursor::Cursor::~Cursor()
{
}

void _Cursor::Cursor::drawCursor()
{

	CursorShader.use();
	if (ToolsWindowDefinition::RadiusSlider != this->radius)
	{
		this->radius = ToolsWindowDefinition::RadiusSlider;
		scaleWithRadius(radius);
	}
	CursorShader.uploadTimeToGPU();
	CursorShader.uploadModelMatrixToGPU(this->model);

	bindVAO();
	glDrawElements(GL_LINES, (GLsizei)indices.size(), GL_UNSIGNED_INT, NULL);
	unbindActiveVAO();

}

void _Cursor::Cursor::updateRadius()
{

}
