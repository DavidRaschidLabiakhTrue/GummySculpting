#ifndef DebugPlane_HPP
#define DebugPlane_HPP

#include "MeshStats.hpp"

#include "Shader.hpp"

namespace DebugPlaneDefinition
{
	using namespace MeshStatsDefinition;
	using namespace ShaderDefinition;

	class DebugPlane : public GraphicsData
	{
	public:
		DebugPlane();
		~DebugPlane();
		DebugPlane(v3 center, v3 normal, float width, float height, v4 color);

		void addTri(vector<int> indices);
		void calcVertices(v3 center, v3 normal, float width, float height);

		bool shouldDraw;
	};

	typedef DebugPlane& DebugPlaneReference;
}

#endif
