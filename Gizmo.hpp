#ifndef Gizmo_HPP
#define Gizmo_HPP

#include "Sampler.hpp"
#include "Debug.hpp"

namespace GizmoDefinition
{
	using namespace GizmoDefinition;
	using namespace SamplerDefinition;

	class Gizmo : Sampler
	{
	public:
		enum GizmoState
		{
			INACTIVE,
			ROTATE,
			TRANSLATE,
			SCALE
		};
		enum GizmoAxis
		{
			X,
			Y,
			Z,
			ALL,
			NONE
		};
		class GizmoColors {
			public:
				const static inline v4 red = { 1.0f, 0.0f, 0.0f, 1.0f };
				const static inline v4 green = { 0.0f, 1.0f, 0.0f, 1.0f };
				const static inline v4 blue = { 0.0f, 0.0f, 1.0f, 1.0f };
				const static inline v4 yellow = { 0.85f, 0.75f, 0.33f, 1.0f };
				const static inline v4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
				const static inline v4 lightOrange = { 0.9f, 0.85f, 0.65f, 1.0f };
				const static inline v4 lightRed = { 1.0f, 0.5f, 0.5f, 1.0f };
				const static inline v4 lightGreen = { 0.65f, 0.95f, 0.65f, 1.0f };
				const static inline v4 lightBlue = { 0.5f, 0.5f, 0.9f, 1.0f };
				const static inline v4 lightYellow = { 1.0f, 0.95f, 0.65f, 1.0f };
		};
		struct Handle
		{
			Handle(string fileName, v4 color, v4 hoverColor, v3 offset, float scale, float rot, v3 rotAxis, GizmoAxis axis);
			StaticMesh mesh;
			GizmoAxis axis;
			v3 offsetFromGizmo;
			v4 hoverColor;
			bool hovered = false;
			float distanceFromCam = 0;
		};

		Gizmo();
		~Gizmo();
		Gizmo(bool trueConstructor);

		void checkInput(MeshReference cMesh);
		bool queryTransforms(MeshReference cMesh);
		void drawGizmo();
		void setState(GizmoState newState);
		void iterateState(MeshReference cMesh);
		void moveGizmo(v3 newPosition);

		GizmoState state = INACTIVE;

	protected:
		void queryTranslate(MeshReference cMesh);
		void queryRotate(MeshReference cMesh);
		void queryScale(MeshReference cMesh);

		void drawTranslate();
		void drawRotate();
		void drawScale();

		void translateMesh(MeshReference cMesh);
		void rotateMesh(MeshReference cMesh);
		void scaleMesh(MeshReference cMesh);

		static bool sortHandlesByDistance(Handle const& lhs, Handle const& rhs);

		void moveHandles(v3 newPosition, vector<Handle>& handles);
		void clearHover(vector<Handle>& handles);
		float calculateMouseOffset(MeshReference cMesh);
		v3 getFartherPlaneNormal(v3 position, v3 center, v3 normalA, v3 normalB);

		int meshID = -1;
		GizmoAxis activeAxis = GizmoAxis::NONE;
		float prevMouseOffset;
		float prevMouseDistance;
		v3 startMousePosition;
		v3 prevMousePosition;
		bool didChangeState = false;
		bool didTransform = false;
		v3 gizmoPosition = v3(0);

		// I like there are no pointers anymore.

		//Translate
		vector<Handle> arrows;
		string arrowFileName = "arrow.gum"; 
		float arrowScale = 0.5f;
		
		//Rotate
		vector<Handle> rings;
		string ringFileName = "ring.gum";
		float ringScale = 0.3f;

		//Scale
		vector<Handle> arms;
		string armFileName = "scale_arm.gum";
		string cubeFileName = "cube.gum";
		float armScale = 0.5f;
		float cubeScale = 0.1f;
	};
}

#endif // !Gizmo_HPP