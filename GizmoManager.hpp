#ifndef GizmoManager_HPP
#define GizmoManager_HPP

#include "Gizmo.hpp"
#include "TranslateGizmo.hpp"
#include "RotateGizmo.hpp"

namespace GizmoManagerDefinition
{
	using namespace GizmoDefinition;
	using namespace TranslateGizmoDefinition;
	using namespace RotateGizmoDefinition;

	class GizmoManager
	{
	public:
		GizmoManager();
		~GizmoManager();

		GizmoManager(bool trueConstructor);

		void queryGizmo(MeshReference cMesh);
		void drawGizmo();

		Gizmo* currentGizmo;

		bool gizmoActive = false;
	protected:

	};
}

#endif // !GizmoManager_HPP