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
	if (cast())
	{
		auto key = currentMesh->searchLinear(direction, vertices[0].position);

		say key done;
	}
	
}

void SamplerDefinition::Sampler::queryRay()
{
	cast();
}
