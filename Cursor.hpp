#ifndef Cursor_HPP
#define Cursor_HPP

#include "StaticCircle.hpp"

#include "Shader.hpp"


namespace _Cursor
{
	using namespace StaticCircleDefinition;
	using namespace ShaderDefinition;

	class Cursor : public StaticCircle
	{
		public:
			Cursor();
			Cursor(bool trueConstructor);
			~Cursor();

			void drawCursor();
			void rotateCursor();
			void updateRadius();

			v3 orientation = v3(0,0,0);
			v3 lastOrientation = v3(0, 0, 0);
		
	};
}

#endif // !Cursor_HPP
