#ifndef Indices_HPP
#define Indices_HPP
#include "Macro.hpp"
#include <vector>

#include "OpenGLWrapper.hpp"


Usage Macros;



namespace IndicesDefinition
{

	using std::vector;

	typedef GLuint KeyData; // Used to call values or reference by indice in a vertex array.

	extern const KeyData ImpossibleKey; // Impossible key value for any mesh.

	typedef vector<KeyData> KeyList; // list of keys returned for sculpting...I think?
}


#endif // !Indices_HPP
