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
	public:
		TranslateGizmo();
		~TranslateGizmo();

		TranslateGizmo(bool trueConstructor);

		void draw() override;
		bool query() override;
		void CreateArrow(v4 color, v3 offset, float rotationAngle, v3 rotationAxis);

	protected:
		StaticMesh arrows[3];
		string arrowFileName = "arrow.gum";
	};
}

#endif // !TranslateGizmo_HPP