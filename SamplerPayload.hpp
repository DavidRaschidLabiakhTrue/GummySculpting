#ifndef SamplerPayload_HPP
#define SamplerPayload_HPP

#include "V3D.hpp"

namespace SamplerPayloadDefinition
{
	using namespace VertexDefinition;
	class SamplerPayload
	{
		public:
			SamplerPayload();
			~SamplerPayload();

			v3 origin;
			v3 direction;
			float radius;

	};
	typedef SamplerPayload& SamplerPayloadReference;
}

#endif
