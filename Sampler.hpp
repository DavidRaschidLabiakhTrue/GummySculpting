#ifndef Sampler_HPP
#define Sampler_HPP

#include "RayCasting.hpp"
#include "Mesh_Manager.hpp"

namespace SamplerDefinition
{
	using namespace RayCastDefinition;
	using namespace Mesh_Manager_Definition;

	// mesh sampler that reads in a mesh and processes it directly from it's maps and graphs to perform sculpting actions on.
	class Sampler: public RayCast
	{
		public:
			Sampler();
			Sampler(bool trueConstructor);
			~Sampler();

			void queryRay(MeshPTR currentMesh);
			void queryRay();

			v3 currentDir = v3(0);

		
	};
}

#endif // !Sampler_HPP

