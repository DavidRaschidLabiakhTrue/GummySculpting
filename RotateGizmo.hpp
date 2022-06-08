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
					RotateGizmoState(int meshID, v3 rotations, v3 position) {
						this->meshID = meshID;
						this->rotations = rotations;
						this->position = position;
					};
					~RotateGizmoState() {};

					int meshID;
					v3 rotations;
					v3 position;
			};

			static const inline float detectionRange = 0.1f;

			void RotateMesh(MeshReference cMesh);

			v3 getPlaneNormal(GizmoAxis axis);

			v3 ringScales = { 0.3f, 0.297f, 0.295f };

			RotateGizmoState state;
			v3 mouseStartPos;
			vector<shared_ptr<Ring>> rings;
			bool didRotate = false;
	};
}

#endif // !RotateGizmo_HPP