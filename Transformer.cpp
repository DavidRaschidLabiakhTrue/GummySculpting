#include "Transformer.hpp"
#include "MathDefinitions.hpp"

using namespace MathTypeDefinitions::CoordinateDefine::Basis;

TransformerDefinition::ModelMatrix::ModelMatrix()
{
}

TransformerDefinition::ModelMatrix::~ModelMatrix()
{
}

void TransformerDefinition::ModelMatrix::resetModelMatrix()
{
	this->model = m4(1.0f);
}

void TransformerDefinition::ModelMatrix::rotateX(const float x)
{
	m4 rotation = rotate(x, Basis::X);
	model = rotation * model;
}

void TransformerDefinition::ModelMatrix::rotateY(const float y)
{
	m4 rotation = rotate(y, Basis::Y);
	model = rotation * model;
}

void TransformerDefinition::ModelMatrix::rotateZ(const float z)
{
	m4 rotation = rotate(z, Basis::Z);
	model = rotation * model;
}

void TransformerDefinition::ModelMatrix::rotateX_deg(const float x)
{
	model = rotate(model, glm::radians(x), Basis::X);
}

void TransformerDefinition::ModelMatrix::rotateY_deg(const float y)
{
	model = rotate(model, glm::radians(y), Basis::Y);
}

void TransformerDefinition::ModelMatrix::rotateZ_deg(const float z)
{
	model = rotate(model, glm::radians(z), Basis::Z);
}

void TransformerDefinition::ModelMatrix::translateX(const float x)
{
	model = translate(model, v3(x, 0, 0));
}

void TransformerDefinition::ModelMatrix::translateY(const float y)
{
	model = translate(model, v3(0, y, 0));
}

void TransformerDefinition::ModelMatrix::translateZ(const float z)
{
	model = translate(model, v3(0, 0, z));
}

void TransformerDefinition::ModelMatrix::scaleUniform(const float scalar)
{
	model = scale(model, v3(scalar));
}

void TransformerDefinition::ModelMatrix::scaleX(const float scalarx)
{
	model = scale(model, v3(scalarx, 1.0f, 1.0f));
}

void TransformerDefinition::ModelMatrix::scaleY(const float scalary)
{
	model = scale(model, v3(1.0f, scalary, 1.0f));
}

void TransformerDefinition::ModelMatrix::scaleZ(const float scalarz)
{
	model = scale(model, v3(1.0f, 1.0f, scalarz));
}


TransformerDefinition::CameraTransformer::CameraTransformer()
{
}

TransformerDefinition::CameraTransformer::~CameraTransformer()
{
}
