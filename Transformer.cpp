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

void TransformerDefinition::ModelMatrix::setModelMatrix()
{
	//resetModelMatrix();
	//setScale(scaleValues);	
	//setRotation(rotationMatrix);
	//setTranslation(translationValues);

	v3 s = transform.scale;
	v3 r = transform.rotation;

	say "x:" spc r.x spc "y:" spc r.y spc "z:" spc r.z done;

	model = scale(s);
	model *= rotate(r.z, Basis::Z);
	model *= rotate(r.y, Basis::Y);
	model *= rotate(r.x, Basis::X);

	// Add world translation
	model[3][0] += transform.worldTranslation.x;
	model[3][1] += transform.worldTranslation.y;
	model[3][2] += transform.worldTranslation.z;

	position = v3(model[3][0], model[3][1], model[3][2]);
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
	model = m4(1.0f);
	model = scale(model, v3(radius));
}

TransformerDefinition::CameraTransformer::CameraTransformer()
{
}

TransformerDefinition::CameraTransformer::~CameraTransformer()
{
}
