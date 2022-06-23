#include "Transformer.hpp"
#include "Debug.hpp"

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

void TransformerDefinition::ModelMatrix::setModelMatrix()
{
	resetModelMatrix();
	//translate model matrix to world origin
	translateAll(-1.0f * transform.worldTranslation);

	model = scale(transform.scale) * transform.rotationMatrix * model;

	//translate matrix back then add new translation
	translateAll(transform.worldTranslation + transform.translation);

	position = transform.worldTranslation + transform.translation;
}

void TransformerDefinition::ModelMatrix::rotateX(const float x)
{
	m4 rotationMatrix = rotate(x, Basis::X);
	model = rotationMatrix * model;
}

void TransformerDefinition::ModelMatrix::rotateY(const float y)
{
	m4 rotationMatrix = rotate(y, Basis::Y);
	model = rotationMatrix * model;
}

void TransformerDefinition::ModelMatrix::rotateZ(const float z)
{
	m4 rotationMatrix = rotate(z, Basis::Z);
	model = rotationMatrix * model;
}

void TransformerDefinition::ModelMatrix::rotateX_deg(const float x)
{
	m4 rotationMatrix = rotate(glm::radians(x), Basis::X);
	model = rotationMatrix * model;
}

void TransformerDefinition::ModelMatrix::rotateY_deg(const float y)
{
	m4 rotationMatrix = rotate(glm::radians(y), Basis::Y);
	model = rotationMatrix * model;
}

void TransformerDefinition::ModelMatrix::rotateZ_deg(const float z)
{
	m4 rotationMatrix = rotate(glm::radians(z), Basis::Z);
	model = rotationMatrix * model;
}

void TransformerDefinition::ModelMatrix::setRotation(const m4 r)
{
	model = rotationMatrix * model;
}

void TransformerDefinition::ModelMatrix::translateAll(v3 t)
{
	model[3][0] += t.x;
	model[3][1] += t.y;
	model[3][2] += t.z;
}

void TransformerDefinition::ModelMatrix::translateX(const float x)
{
	m4 translationMatrix = translate(v3(x, 0, 0));
	model = translationMatrix * model;
}

void TransformerDefinition::ModelMatrix::translateY(const float y)
{
	m4 translationMatrix = translate(v3(0, y, 0));
	model = translationMatrix * model;
}

void TransformerDefinition::ModelMatrix::translateZ(const float z)
{
	m4 translationMatrix = translate(v3(0, 0, z));
	model = translationMatrix * model;
}

void TransformerDefinition::ModelMatrix::setTranslation(const v3 t)
{
	m4 translationMatrix = translate(t);
	model = translationMatrix * model;
}

void TransformerDefinition::ModelMatrix::scaleUniform(const float scalar)
{
	m4 scaleMatrix = scale(v3(scalar));
	model = scaleMatrix * model;
}

void TransformerDefinition::ModelMatrix::scaleX(const float scalarx)
{
	m4 scaleMatrix = scale(v3(scalarx, 1.0f, 1.0f));
	model = scaleMatrix * model;
}

void TransformerDefinition::ModelMatrix::scaleY(const float scalary)
{
	m4 scaleMatrix = scale(v3(1.0f, scalary, 1.0f));
	model = scaleMatrix * model;
}

void TransformerDefinition::ModelMatrix::scaleZ(const float scalarz)
{
	m4 scaleMatrix = scale(v3(1.0f, 1.0f, scalarz));
	model = scaleMatrix * model;
}

void TransformerDefinition::ModelMatrix::setScale(const v3 s)
{
	m4 scaleMatrix = scale(s);
	model = scaleMatrix * model;
}

void TransformerDefinition::ModelMatrix::scaleWithRadius(const float radius)
{
	auto mat = scale(model, v3(radius));
	model = model * mat;
}

TransformerDefinition::CameraTransformer::CameraTransformer()
{
}

TransformerDefinition::CameraTransformer::~CameraTransformer()
{
}
