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

		protected:
			class Ring : public Handle
			{
				static const inline string ringFileName = "ring.gum";
				public:
					Empty_Construct Ring() {};
					Ring(GizmoAxis axis, v4 color, v4 hoverColor, v4 activeColor, float rot, v3 rotAxis, float scale);
					~Ring() {};
			};
			class RotateGizmoState
			{
				public:
					RotateGizmoState() {};
					RotateGizmoState(int meshID, v3 position) {
						this->meshID = meshID;
						this->position = position;
					};
					~RotateGizmoState() {};

					int meshID;
					v3 position;
			};

			static const inline float detectionRange = 0.1;

			void RotateMesh(MeshReference cMesh, float radians, v3 axis);

			RotateGizmoState state;

			vector<shared_ptr<Ring>> rings;
	};
}

#endif // !RotateGizmo_HPP