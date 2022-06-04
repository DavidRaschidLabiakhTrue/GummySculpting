#ifndef Transformer_HPP
#define Transformer_HPP

#include "LinearAlgebra.hpp"
#include "MathDefinitions.hpp"


namespace TransformerDefinition
{
	using namespace MathTypeDefinitions::CoordinateDefine;
	using namespace MathTypeDefinitions::MatrixDefine;

	class Transformer
	{
		public:

			Transformer();
			~Transformer();

			void translateX(float movex);
			void translateY(float movey);
			void translateZ(float movez);

			

			m4 model = m4(1.0f);
			v3 offset = v3(0);
	};

	class CameraTransformer
	{
		public:

			CameraTransformer();
			~CameraTransformer();

			m4 view = m4(1.0f);
			m4 projection = m4(1.0f);

			v3 pos;

			v3 orientation;
			v3 up;


	};

}

#endif
