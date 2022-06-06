#ifndef TranslateGizmo_HPP
#define TranslateGizmo_HPP

#include "Gizmo.hpp"
#include "MeshFileLoader.hpp" // also includes "Mesh.h"

#include "Debug.hpp"

namespace TranslateGizmoDefinition
{
	using namespace GizmoDefinition;
	using namespace MathTypeDefinitions;
	using namespace CoordinateDefine;

	class TranslateGizmo : public Gizmo
	{
		typedef struct Arrow {
			StaticMesh mesh;
			v4 hoverColor;
			v4 activeColor;
			bool hovered = false;
			float distanceFromCam;
			function<void(MeshReference cMesh)> callback;
		} Arrow;

		public:
			TranslateGizmo();
			~TranslateGizmo();

			TranslateGizmo(bool trueConstructor);

		
			void query(MeshReference cMesh) override;
			void draw() override;

		protected:
			const static int numArrows = 3;
			//Arrow arrows[numArrows];
			vector<Arrow> arrows;
			string arrowFileName = "arrow.gum";
			void translateMesh(MeshReference cMesh, v3 axis);
			Arrow* activeArrow;
			void sortArrowsByDistance();
			void clearHover();
	};
}

#endif // !TranslateGizmo_HPP