#ifndef Gizmo_HPP
#define Gizmo_HPP

#include "Sampler.hpp"
#include "SculptPayload.hpp"

namespace GizmoDefinition
{
	using namespace SamplerDefinition;
	using namespace GizmoDefinition;

	class Gizmo : public Sampler
	{
	public:
		Gizmo();
		~Gizmo();
		Gizmo(bool trueConstructor);

		void queryGizmo();

	protected:
		bool gizmoActive = false;
	};
}

#endif // !Gizmo_HPP