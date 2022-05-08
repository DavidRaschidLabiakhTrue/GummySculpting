#include "V3D.hpp"
#include "Color.hpp"
Usage VertexDefinition;
Usage ColorDefinition;

// Vertex Parameter Globals
const float GlobalVertexParameters::DefaultAlphaValue = 1.0f;
const v4 GlobalVertexParameters::DefaultColorLoader = v4(0.5, 0.5, 0.5, GlobalVertexParameters::DefaultAlphaValue); // start off with color of grey
const BitData GlobalVertexParameters::DefaultBinaryWeightData = 10000; // start off with a weight of 100.00 *technically*


V3D::V3D()
{

}

V3D::V3D(float x, float y, float z)
{
	position = v3(x, y, z);
	color = GlobalVertexParameters::DefaultColorLoader;
	bitData = GlobalVertexParameters::DefaultBinaryWeightData;
}

V3D::V3D(float x, float y, float z, float r, float g, float b)
{
	position = v3(x, y, z);
	color = v4(r, g, b, GlobalVertexParameters::DefaultAlphaValue);
	bitData = GlobalVertexParameters::DefaultBinaryWeightData;
}

V3D::~V3D()
{
}

void V3D::operator=(v3 newPosition)
{
	position = newPosition;
}

void V3D::operator=(rv3 newPosition)
{
	position = newPosition;
}

void V3D::operator=(v4 newColor)
{
	color = newColor;
}

void V3D::operator=(rv4 newColor)
{
	color = newColor;
}

void V3D::operator+=(v3 positionOffset)
{
	position += positionOffset;
}

void V3D::operator-=(v3 positionOffset)
{
	position -= positionOffset;
}

void V3D::operator+=(v4 colorOffset)
{
	color.r = ((color.r + colorOffset.r > 1.0f) ? 1.0f : color.r + colorOffset.r);
	color.g = ((color.g + colorOffset.g > 1.0f) ? 1.0f : color.g + colorOffset.g);
	color.b = ((color.b + colorOffset.b > 1.0f) ? 1.0f : color.b + colorOffset.b);
	// color.a is *always* 1.0.
}

void V3D::operator-=(rv4 colorOffset)
{
	color.r = ((color.r - colorOffset.r < 0.0f) ? 0.0f : color.r - colorOffset.r);
	color.g = ((color.g - colorOffset.g > 0.0f) ? 0.0f : color.g - colorOffset.g);
	color.b = ((color.b - colorOffset.b > 0.0f) ? 0.0f : color.b - colorOffset.b);
	// color.a is *always* 1.0.
}