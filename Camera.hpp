#ifndef Camera_HPP
#define Camera_HPP

#include "MathDefinitions.hpp"
#include "CameraParameters.hpp"
#include "Transformer.hpp"
#include "MainStateMachine.hpp"


#include "OrbitRing.hpp"

#include "OrbitArray.hpp"

Usage MathTypeDefinitions::CoordinateDefine;
Usage MathTypeDefinitions::MatrixDefine;

namespace CameraDefinition
{
	using namespace CameraParametersDefinition;
	using namespace MainStateMachineDefinition;
	using TransformerDefinition::CameraTransformer;
	using OrbitArray_::OrbitArray;
	// Camera class that enables 3D rendering.
	class Camera : public CameraParameters, public CameraTransformer
	{
		public:
			enum CameraState
			{
				FREEFOCUS,
				ORBIT
			};
			Camera();
			~Camera();

			void checkInput(); // checks for use rinput
			void updateMatrix(); // updates the matrix sent out.

			m4 cameraMatrix;

			CameraState cameraState = ORBIT;

			bool shouldDrawCursor = true;

			OrbitArray XY; // railing for moving about x & y -- left right up down
			OrbitArray YZ; // railing for moving about y & z -- up down forward backward
			OrbitArray XZ; // railing for moving about x & z -- left right forward backward -- we follow this array to circle around

			OrbitRing_::OrbitRing ringXY;

			bool experimental = false;


		protected:
			void experimentalKeyInput();
			void standardKeyInput();
			void checkKeyInput(); // checks for user key input
			void checkMouseInput(); // checks for mouse input from the user

			bool firstClick = false;
			bool shouldResetMouse = false;
	};
	typedef Camera* CameraPTR;


	extern CameraPTR GlobalCamera;


}

#endif // !Camera_HPP

