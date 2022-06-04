#ifndef Camera_HPP
#define Camera_HPP

#include "MathDefinitions.hpp"
#include "CameraParameters.hpp"
#include "Transformer.hpp"
#include "MainStateMachine.hpp"

Usage MathTypeDefinitions::CoordinateDefine;
Usage MathTypeDefinitions::MatrixDefine;

namespace CameraDefinition
{
	using namespace CameraParametersDefinition;
	using namespace MainStateMachineDefinition;
	using TransformerDefinition::CameraTransformer;

	// Camera class that enables 3D rendering.
	class Camera : public CameraParameters, public CameraTransformer
	{
		public:
			Camera();
			~Camera();

			void checkInput(); // checks for use rinput
			void updateMatrix(); // updates the matrix sent out.

			m4 cameraMatrix;


		protected:
			void checkKeyInput(); // checks for user key input
			void checkMouseInput(); // checks for mouse input from the user

			bool firstClick = false;

	};
	typedef Camera* CameraPTR;


	extern CameraPTR GlobalCamera;


}

#endif // !Camera_HPP

