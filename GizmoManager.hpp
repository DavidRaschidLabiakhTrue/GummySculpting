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
		enum GizmoManagerState
		{
			NONE,
			ROTATE,
			TRANSLATE
		};
		GizmoManager();
		~GizmoManager();

		GizmoManager(bool trueConstructor);

		void queryGizmo(MeshReference cMesh);
		void drawGizmo();
		void iterateState();
		void setCurrentGizmo();

		Gizmo* currentGizmo;

		TranslateGizmo* translateGizmo;
		RotateGizmo* rotateGizmo;

		GizmoManagerState state = NONE;

		bool gizmoActive = false;

	protected:

	};
}

#endif // !GizmoManager_HPP