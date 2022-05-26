#ifndef SculptBrush_HPP
#define SculptBrush_HPP

#include "Sampler.hpp"
#include "SculptPayload.hpp"

namespace SculptBrushDefinition
{
	using namespace SamplerDefinition;
	using namespace SculptPayloadDefinition;

	enum BrushState{BrushStateSmooth, BrushStateStroke, BrushStateColor, BrushStateNoise, BrushStateSmoothedColor};

	class SculptBrush : public Sampler
	{
		public:
			SculptBrush();
			~SculptBrush();
			SculptBrush(bool trueConstructor);

			void applySculpt(MeshReference cMesh);

			void querySculpt(MeshReference cMesh);


			BrushState currentState = BrushStateColor;
			bool shouldApplySymmetrically = false;
		protected:
			SculptPayload payload;



	};
}

#endif // !SculptBrush_HPP

