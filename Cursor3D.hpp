#ifndef Cursor3D_HPP
#define Cursor3D_HPP

#include "StaticMesh.hpp"


namespace _Cursor3D
{
	using namespace StaticMeshDefinition;

	

	class Cursor3D : public StaticMesh
	{
		public:
			Cursor3D();
			Cursor3D(bool trueConstructor);
			~Cursor3D();

			void drawCursor();

			float radius;
	};
}

#endif
