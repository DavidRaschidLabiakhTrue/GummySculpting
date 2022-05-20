#include "Sampler.hpp"
#include "KeyInput.hpp"

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
	// this logic is faulty and needs revised for proper state mechanics
	if (cast())
	{
		currentMesh->history.sealChange = false;

		if (direction != currentDir)
		{
			currentDir = direction;
			auto key = currentMesh->searchLinear(direction, vertices[0].position);

			if (key != ImpossibleKey)
			{

				auto& foundPoint = currentMesh->vertices[key];

				foundPoint = currentMesh->averageAt(key);


				forall(edge, currentMesh->edges[key].vertexEdges)
				{
					currentMesh->vertices[edge] = currentMesh->averageAt(key);
				}

				currentMesh->refresh();
				return;
			}
			else
			{
				// Impossible Key Found
				return;
			}
		}
	}

	else if (currentMesh->history.sealChange == false && CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT))
	{
		currentMesh->history.sealChange = true;
		say "Sampler Sealed off" done;
	}


	
}

void SamplerDefinition::Sampler::queryRay()
{
	cast();
}
