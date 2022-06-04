#ifndef Gizmo_HPP
#define Gizmo_HPP

#include "Sampler.hpp"

namespace GizmoDefinition
{
	using namespace SamplerDefinition;
	using namespace StaticMeshDefinition;

	class Gizmo : public Sampler
	{
	public:
		class GizmoColors {
			public:
				const static inline v4 red = { 1.0, 0.0, 0.0, 1.0 };
				const static inline v4 green = { 0.0, 1.0, 0.0, 1.0 };
				const static inline v4 blue = { 0.0, 0.0, 1.0, 1.0 };
		};
		class GizmoAxes {
			public:
				const static inline v3 x = { 1.0, 0.0, 0.0 };
				const static inline v3 y = { 0.0, 1.0, 0.0 };
				const static inline v3 z = { 0.0, 0.0, 1.0 };
		};

		Gizmo() {};
		Gizmo(bool trueConstructor);
		~Gizmo() {};

		virtual bool query() { return false; };
		virtual void draw() {};

		StaticMesh CreateGizmoMesh(string fileName, v4 color, v3 offset, float rotationAngle, v3 rotationAxis, float scale);

		bool active = false;

	protected:
		
	};
}

#endif // !Gizmo_HPP