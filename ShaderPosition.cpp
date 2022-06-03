#include "ShaderPosition.hpp"

namespace ShaderPositionDefinition
{
	ShaderPositionData ShaderSlotInfo;
}

Usage ShaderPositionDefinition;



ShaderPosition::ShaderPosition()
{

}

ShaderPosition::~ShaderPosition()
{
}

void ShaderPosition::loadPosition()
{
	slot = "aPos";
	position = 0;
}

void ShaderPosition::loadColor()
{
	slot = "aColor";
	position = 2;
}

void ShaderPosition::loadWeight()
{
	slot = "aData";
	position = 3;
}

void ShaderPosition::loadCameraMatrix()
{
	slot = "camMatrix";
	position = 0;
}

void ShaderPosition::loadModelMatrix()
{
	slot = "modelMatrix";
	position = 1;
}

void ShaderPositionDefinition::ShaderPosition::loadOffset()
{
	slot = "staticOffset";
	position = 1;

}

void ShaderPositionDefinition::ShaderPosition::loadScale()
{
	slot = "staticScale";
	position = 2;
}

ShaderPositionData::ShaderPositionData()
{
	position.loadPosition();
	color.loadColor();
	data.loadWeight();
	cameraMatrix.loadCameraMatrix();
	modelMatrix.loadModelMatrix();
	offset.loadOffset();
	scale.loadScale();
}

ShaderPositionData::~ShaderPositionData()
{
}
