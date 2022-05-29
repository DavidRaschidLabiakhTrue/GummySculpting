#ifndef SamplerPayload_HPP
#define SamplerPayload_HPP

#include "V3D.hpp"
#include "TriangleList.hpp"
namespace SamplerPayloadDefinition
{
	using namespace VertexDefinition;
	using namespace TriangleListDefinition;
	class SamplerPayload
	{
		public:
			SamplerPayload();
			~SamplerPayload();

			v3 origin;
			v3 direction;
			float radius;
			TriangleID last = -1; // last hit ID;

			bool wasRun = false;


	};
	typedef SamplerPayload& SamplerPayloadReference;
}

#endif
