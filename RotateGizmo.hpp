#ifndef RotateGizmo_HPP
#define RotateGizmo_HPP

#include "Gizmo.hpp"
#include "MeshFileLoader.hpp" // also includes "Mesh.h"

namespace RotateGizmoDefinition
{
	using namespace GizmoDefinition;
	using namespace MathTypeDefinitions;
	using namespace CoordinateDefine;

	class RotateGizmo : public Gizmo
	{
		public:
			RotateGizmo();
			~RotateGizmo();

			RotateGizmo(bool trueConstructor);


			void query(MeshReference cMesh) override;
			void draw() override;


		protected:
			string sphereFileName = "sphere.gum";

			StaticMesh outerSphere;
			StaticMesh innerSphere;

			void RotateMesh(MeshReference cMesh, float radians, v3 axis);
	};
}

#endif // !RotateGizmo_HPP