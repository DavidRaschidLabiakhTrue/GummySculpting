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

void SamplerDefinition::Sampler::queryRay(MeshPTR cMesh)
{
	// this logic is faulty and needs revised for proper state mechanics
	if (cast())
	{
		cMesh->history.sealChange = false;

		if (direction != currentDir)
		{
			currentDir = direction;
			auto key = cMesh->searchLinear(direction, vertices[0].position);

			if (key != ImpossibleKey)
			{
				cMesh->history.changeList[cMesh->history.currentLevelIndex()][key] = V3D(cMesh->averageAt(key));
				cMesh->history.currentChangeLog[key] = V3D(cMesh->averageAt(key));

				forall(edge, cMesh->edges[key].vertexEdges)
				{
					cMesh->history.changeList[cMesh->history.currentLevelIndex()][edge] = V3D(cMesh->averageAt(edge));
					cMesh->history.currentChangeLog[edge] = V3D(cMesh->averageAt(edge));

				}

				// apply changes

				forall(change, cMesh->history.currentChangeLog)
				{
					cMesh->vertices[change.first] = change.second;
				}

				cMesh->history.currentChangeLog.clear();
				


				cMesh->refresh();
				return;
			}
			else
			{
				// Impossible Key Found
				return;
			}
		}
	}

	else if (cMesh->history.sealChange == false && CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT))
	{
		cMesh->history.sealChange = true;
		cMesh->history.adjustLevelUp();
		say "Sampler Sealed off" done;

		
	}


	
}

void SamplerDefinition::Sampler::queryRay()
{
	cast();
}
