#ifndef Gizmo_HPP
#define Gizmo_HPP

#include "Sampler.hpp"

#include "Debug.hpp"

namespace GizmoDefinition
{
	using namespace SamplerDefinition;
	using namespace StaticMeshDefinition;

	class Gizmo : public Sampler
	{
	public:
		class GizmoColors {
			public:
				const static inline v4 red = { 1.0f, 0.0f, 0.0f, 1.0f };
				const static inline v4 green = { 0.0f, 1.0f, 0.0f, 1.0f };
				const static inline v4 blue = { 0.0f, 0.0f, 1.0f, 1.0f };
				const static inline v4 darkGray = { 0.35f, 0.35f, 0.35f, 1.0f };
				const static inline v4 lightGray = { 0.65f, 0.65f, 0.65f, 1.0f };
				const static inline v4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
				const static inline v4 lightOrange = { 0.9f, 0.85f, 0.65f, 1.0f };
				const static inline v4 lightRed = { 1.0f, 0.5f, 0.5f, 1.0f };
				const static inline v4 lightGreen = { 0.65f, 0.95f, 0.65f, 1.0f };
				const static inline v4 lightBlue = { 0.5f, 0.5f, 0.9f, 1.0f };
		};
		struct GizmoState {
			GizmoState(MeshReference cMesh) : cMesh(cMesh) {
				position = cMesh.center;
			};
			MeshReference cMesh;
			v3 position;
			//put virtual functions here
		};

		enum GizmoAxis
		{
			NONE,
			X,
			Y,
			Z
		};

		class Handle
		{
			public:
				Empty_Construct Handle() {};
				Handle(bool trueConstructor) {};
				virtual ~Handle() {};
				StaticMesh mesh;
				GizmoAxis axis;
				v4 hoverColor;
				v4 activeColor;
				v3 offsetFromGizmo;
				bool hovered;
		};

		Empty_Construct Gizmo();
		Gizmo(bool trueConstructor);
		~Gizmo();

		virtual void query(MeshReference cMesh) {};

		void draw();

		void clearHover();
		void checkClicked();

		static StaticMesh createGizmoMesh(string fileName, v4 color, v3 offset, float rotationAngle, v3 rotationAxis, float scale, bool invertFaces = false);
		bool detectMeshClick(StaticMeshReference cMesh);

		bool active = false;

		bool clicked = false;

		GizmoAxis activeAxis;

		vector<shared_ptr<Handle>> handles;

	protected:

	};
}

#endif // !Gizmo_HPP