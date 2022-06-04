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
				const static inline v4 red = { 1.0f, 0.0f, 0.0f, 1.0f };
				const static inline v4 green = { 0.0f, 1.0f, 0.0f, 1.0f };
				const static inline v4 blue = { 0.0f, 0.0f, 1.0f, 1.0f };
				const static inline v4 darkGray = { 0.35f, 0.35f, 0.35f, 1.0f };
				const static inline v4 lightGray = { 0.65f, 0.65f, 0.65f, 1.0f };
				const static inline v4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
				const static inline v4 lightOrange = { 0.9f, 0.85f, 0.65f, 1.0f };
		};
		class GizmoAxes {
			public:
				const static inline v3 x = { 1.0f, 0.0f, 0.0f };
				const static inline v3 y = { 0.0f, 1.0f, 0.0f };
				const static inline v3 z = { 0.0f, 0.0f, 1.0f };
		};

		Gizmo() {};
		Gizmo(bool trueConstructor);
		~Gizmo() {};

		virtual void query(MeshReference cMesh) {};
		virtual void draw() {};

		StaticMesh createGizmoMesh(string fileName, v4 color, v3 offset, float rotationAngle, v3 rotationAxis, float scale, bool invertFaces = false);
		bool detectMeshClick(StaticMeshReference cMesh);

		bool active = false;

	protected:
		
	};
}

#endif // !Gizmo_HPP