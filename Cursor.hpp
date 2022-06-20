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

			void updateRadius();
		
	};
}

#endif // !Cursor_HPP
