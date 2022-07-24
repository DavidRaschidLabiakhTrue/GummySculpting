#ifndef SculptPayload_HPP
#define SculptPayload_HPP

#include "SamplerPayload.hpp"
#include "Mesh.hpp"
#include "Window_Class.hpp"
namespace SculptPayloadDefinition
{
	using namespace MeshDefinition;
	using Window_Class::WindowGlobal::capsLockCheck;
	class SculptPayload : public SamplerPayloadDefinition::SamplerPayload
	{
		public:
			SculptPayload();
			~SculptPayload();

			void changeRadius(float newRadius);

			void updateLast(const TriangleID& id, rv3 lastHit, v3 tempNorm);

			void reverseDir();

			void modifyPolarity();

			v3 hitNorm;
			v3 rDir;
			v3 hit;
			float polarity;
			v3 selectionDirection;
			v3 selectionOrigin;

	};
	typedef SculptPayload& SculptPayloadReference;
}

#endif
