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
			Empty_Construct TranslateGizmo();
			TranslateGizmo(bool trueConstructor);
			~TranslateGizmo();
		
			void query(MeshReference cMesh) override;
			void translateMesh(MeshReference cMesh);

		protected:
			class Arrow : public Handle
			{
				static const inline string arrowFileName = "arrow.gum";
				static const inline float arrowScale = 0.5f;
				public:
					Empty_Construct Arrow() {};
					Arrow(GizmoAxis axis, v4 color, v4 hoverColor, v4 activeColor, v3 offset, float rot, v3 rotAxis);
					~Arrow() {};
					float distanceFromCam;
			};
			class TranslateGizmoState
			{
				public:
					TranslateGizmoState() {};
					TranslateGizmoState(int meshID, v3 position) {
						this->meshID = meshID;
						this->position = position;
					};
					~TranslateGizmoState() {};
					int meshID;
					v3 position;
			};
			
			
			void sortArrowsByDistance();
			glm::vec3 getCloserPlaneNormal(glm::vec3 position, glm::vec3 center, glm::vec3 normalA, glm::vec3 normalB);
			float calculateMoveDistance();
			float mouseStartOffset;

			vector<shared_ptr<Arrow>> arrows;

			vector<shared_ptr<TranslateGizmoState>> undoHistory;

			TranslateGizmoState state;

			bool shouldUpdate = true;

			vec3 newPosition;
	};
}

#endif // !TranslateGizmo_HPP