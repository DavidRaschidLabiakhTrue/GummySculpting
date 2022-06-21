#include "Cursor.hpp"
#include "ToolsWindow.hpp"

using namespace _Cursor;

_Cursor::Cursor::Cursor()
{

}

_Cursor::Cursor::Cursor(bool trueConstructor) : StaticCircle(trueConstructor)
{
	
}

_Cursor::Cursor::~Cursor()
{
}

void _Cursor::Cursor::drawCursor()
{

	CursorShader.use();
	setTranslation(offset + center);

	rotateCursor();
	
	v3 newPosition = v3(0.0f);
	CursorShader.uploadOffsetVectorToGPU(newPosition);
	CursorShader.uploadTimeToGPU();
	CursorShader.uploadModelMatrixToGPU(this->model);

	bindVAO();
	glDrawElements(GL_LINES, (GLsizei)indices.size(), GL_UNSIGNED_INT, NULL);
	unbindActiveVAO();

	this->resetModelMatrix();
	updateRadius();

}

void _Cursor::Cursor::rotateCursor()
{
	//if (orientation != lastOrientation)
	//{
	//	lastOrientation = orientation;
	//	model = m4(1.0f);
	//	say to_string(orientation) done;

	//	v3 newvec;

	//	newvec.x = atan(orientation.x);
	//	newvec.y = atan(orientation.y);
	//	newvec.z = atan(orientation.z);

	//	this->rotateX(newvec.x);
	//	this->rotateY(newvec.y);
	//	this->rotateZ(newvec.z);


	//	say to_string(newvec) done;
	//}
}

void _Cursor::Cursor::updateRadius()
{
	if (ToolsWindowDefinition::RadiusSlider != this->diameter)
	{
		this->diameter = ToolsWindowDefinition::RadiusSlider;
		this->radius = diameter / 2.0f;
		scaleWithRadius(radius);
	}
}
