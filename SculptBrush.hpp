#ifndef SculptBrush_HPP
#define SculptBrush_HPP

#include "Sampler.hpp"
#include "SculptPayload.hpp"

namespace SculptBrushDefinition
{
	using namespace SamplerDefinition;
	using namespace SculptPayloadDefinition;

	enum BrushState{BrushStateSmooth, BrushStateStroke, BrushStateColor};

	class SculptBrush : public Sampler
	{
		public:
			SculptBrush();
			~SculptBrush();
			SculptBrush(bool trueConstructor);

			void querySculpt(MeshReference cMesh);


			BrushState currentState = BrushStateSmooth;
			bool shouldApplySymmetrically = false;
		protected:
			SculptPayload payload;



	};
}

#endif // !SculptBrush_HPP

