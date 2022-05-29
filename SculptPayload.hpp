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

			void updateLast(const TriangleID& id, rv3 lastHit, v3 tempNorm);

			void reverseDir();

			v3 hitNorm;
			v3 rDir;
			v3 hit;

	};
	typedef SculptPayload& SculptPayloadReference;
}

#endif
