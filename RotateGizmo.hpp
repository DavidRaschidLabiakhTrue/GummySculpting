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
					RotateGizmoState(int meshID, v3 rotations) {
						this->meshID = meshID;
						this->rotations = rotations;
					};
					~RotateGizmoState() {};

					int meshID;
					v3 rotations;
			};

			static const inline float detectionRange = 0.1f;

			void RotateMesh(MeshReference cMesh);

			v3 getPlaneNormal(GizmoAxis axis);

			float ringScale = 0.3f;

			RotateGizmoState state;
			v3 mouseStartPos;
			vector<shared_ptr<Ring>> rings;
			bool didRotate = false;
	};
}

#endif // !RotateGizmo_HPP