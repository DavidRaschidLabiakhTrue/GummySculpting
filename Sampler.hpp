#ifndef Sampler_HPP
#define Sampler_HPP

#include "RayCasting.hpp"

namespace SamplerDefinition
{
	using namespace RayCastDefinition;

	class Sampler: public RayCast
	{
		public:
			Sampler();
			Sampler(bool trueConstructor);
			~Sampler();

			void queryRay();

		
	};
}

#endif // !Sampler_HPP

