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

			void resetModelMatrix();
			
			// rotate the model x degrees
			void rotateX(const float x);
			// rotate the model y degrees
			void rotateY(const float y);
			// rotate the model z degrees
			void rotateZ(const float z);

			// translate the model x units in x
			void translateX(const float x);
			// translate the model y units in y
			void translateY(const float y);
			// translate the model z units in z
			void translateZ(const float z);

			// scale the model uniformly
			void scaleUniform(const float scalar);

			// these 3 are only here for *completeness*, you should not use them on any *deforming meshes*

			// scale the model by a scalar factor of x
			void scaleX(const float scalarx);
			// scale the model by a scalar factor of y
			void scaleY(const float scalary);
			// scale the model by a scalar factor of z
			void scaleZ(const float scalarz);
			

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
