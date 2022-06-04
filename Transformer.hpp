#ifndef Transformer_HPP
#define Transformer_HPP

#include "LinearAlgebra.hpp"
#include "MathDefinitions.hpp"


namespace TransformerDefinition
{
	using namespace MathTypeDefinitions::CoordinateDefine;
	using namespace MathTypeDefinitions::MatrixDefine;

	class ModelMatrix
	{
		public:

			ModelMatrix();
			~ModelMatrix();
			
			// rotate the model x degrees
			void rotateX(const float x);
			void rotateY(const float y);
			void rotateZ(const float z);

			void translateX(const float x);
			void translateY(const float y);
			void translateZ(const float z);
			

			m4 model = m4(1.0f);
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
