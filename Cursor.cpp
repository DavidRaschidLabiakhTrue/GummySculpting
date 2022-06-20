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
		for (auto& v : this->vertices)
		{
			v.position = v3(model * v4(v.position, 1.0f));
		}
		this->model = m4(1.0f);
	}
	v3 newPosition = offset + center;
	CursorShader.uploadOffsetVectorToGPU(newPosition);
	CursorShader.uploadTimeToGPU();
	CursorShader.uploadModelMatrixToGPU(this->model);

	bindVAO();
	glDrawElements(GL_LINES, (GLsizei)indices.size(), GL_UNSIGNED_INT, NULL);
	unbindActiveVAO();

}

void _Cursor::Cursor::updateRadius()
{

}
