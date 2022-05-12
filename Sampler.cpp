#include "Sampler.hpp"

SamplerDefinition::Sampler::Sampler()
{
}

SamplerDefinition::Sampler::Sampler(bool trueConstructor)
	: RayCast(trueConstructor)
{
	
}

SamplerDefinition::Sampler::~Sampler()
{
}

void SamplerDefinition::Sampler::queryRay(MeshPTR currentMesh)
{
	if (cast() && direction != currentDir)
	{
		currentDir = direction;
		auto key = currentMesh->searchLinear(direction, vertices[0].position);

		if (key != ImpossibleKey)
		{

			auto& foundPoint = currentMesh->vertices[key];

			foundPoint += foundPoint.position * 0.01f;

	

			currentMesh->refresh();
		}
		else
		{
			// Impossible Key Found
		}
	}
	
}

void SamplerDefinition::Sampler::queryRay()
{
	cast();
}
