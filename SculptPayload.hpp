#ifndef SculptPayload_HPP
#define SculptPayload_HPP

#include "SamplerPayload.hpp"
#include "Mesh.hpp"
namespace SculptPayloadDefinition
{
	using namespace MeshDefinition;
	class SculptPayload : public SamplerPayloadDefinition::SamplerPayload
	{
		public:
			SculptPayload();
			~SculptPayload();

			void changeRadius(float newRadius);

			void updateLast(const TriangleID& id);

	};
	typedef SculptPayload& SculptPayloadReference;
}

#endif
