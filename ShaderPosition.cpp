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



void ShaderPositionDefinition::ShaderPosition::loadProjectionMatrix()
{
	slot = "projectionMatrix";
	position = 15;
}

void ShaderPositionDefinition::ShaderPosition::loadViewMatrix()
{
	slot = "viewMatrix";
	position = 20;
}
void ShaderPosition::loadModelMatrix()
{
	slot = "modelMatrix";
	position = 25;
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

void ShaderPositionDefinition::ShaderPosition::loadStaticColor()
{
	slot = "staticColor";
	position = 10;
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
	staticColor.loadStaticColor();
	view.loadViewMatrix();
	projection.loadProjectionMatrix();
}

ShaderPositionData::~ShaderPositionData()
{
}
