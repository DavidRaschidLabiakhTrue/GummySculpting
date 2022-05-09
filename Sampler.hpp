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

		
	};
}

#endif // !Sampler_HPP

