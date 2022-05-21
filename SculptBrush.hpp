#ifndef SculptBrush_HPP
#define SculptBrush_HPP

#include "Sampler.hpp"

namespace SculptBrushDefinition
{
	using namespace SamplerDefinition;

	class SculptBrush : public Sampler
	{
		public:
			SculptBrush();
			~SculptBrush();

			bool shouldApplySymmetrically = false;

	};
}

#endif // !SculptBrush_HPP

