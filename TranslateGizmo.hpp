#ifndef TranslateGizmo_HPP
#define TranslateGizmo_HPP

#include "Gizmo.hpp"
#include "MeshFileLoader.hpp" // also includes "Mesh.h"

namespace TranslateGizmoDefinition
{
	using namespace GizmoDefinition;
	using namespace MathTypeDefinitions;
	using namespace CoordinateDefine;

	class TranslateGizmo : public Gizmo
	{
		typedef struct Arrow {
			StaticMesh mesh;
			function<void(MeshReference cMesh)> callback;
		} Arrow;

		public:
			TranslateGizmo();
			~TranslateGizmo();

			TranslateGizmo(bool trueConstructor);

		
			void query(MeshReference cMesh) override;
			void draw() override;
			

		protected:
			Arrow arrows[3];
			string arrowFileName = "arrow.gum";
			void translateMesh(MeshReference cMesh, v3 axis);
			Arrow activeArrow;
	};
}

#endif // !TranslateGizmo_HPP