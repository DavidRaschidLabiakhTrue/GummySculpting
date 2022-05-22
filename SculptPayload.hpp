#ifndef SculptPayload_HPP
#define SculptPayload_HPP

#include "SamplerPayload.hpp"

namespace SculptPayloadDefinition
{
	class SculptPayload : public SamplerPayloadDefinition::SamplerPayload
	{
		public:
			SculptPayload();
			~SculptPayload();

			void changeRadius(float newRadius);
	};
	typedef SculptPayload& SculptPayloadReference;
}

#endif
