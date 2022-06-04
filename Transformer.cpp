#include "Transformer.hpp"
#include "MathDefinitions.hpp"

using namespace MathTypeDefinitions::CoordinateDefine::Basis;

TransformerDefinition::ModelMatrix::ModelMatrix()
{
}

TransformerDefinition::ModelMatrix::~ModelMatrix()
{
}

void TransformerDefinition::ModelMatrix::rotateX(const float x)
{
	model = rotate(model, glm::radians(x), Basis::X);
}

void TransformerDefinition::ModelMatrix::rotateY(const float y)
{
	model = rotate(model, glm::radians(y), Basis::Y);
}

void TransformerDefinition::ModelMatrix::rotateZ(const float z)
{
	model = rotate(model, glm::radians(z), Basis::Z);
}

void TransformerDefinition::ModelMatrix::translateX(const float x)
{
}

void TransformerDefinition::ModelMatrix::translateY(const float y)
{
}

void TransformerDefinition::ModelMatrix::translateZ(const float z)
{
}


TransformerDefinition::CameraTransformer::CameraTransformer()
{
}

TransformerDefinition::CameraTransformer::~CameraTransformer()
{
}
