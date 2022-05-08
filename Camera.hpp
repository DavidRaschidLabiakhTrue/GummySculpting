#ifndef Camera_HPP
#define Camera_HPP

#include "MathDefinitions.hpp"
#include "CameraParameters.hpp"

Usage MathTypeDefinitions::CoordinateDefine;
Usage MathTypeDefinitions::MatrixDefine;

namespace CameraDefinition
{
	Usage CameraParametersDefinition;
	class Camera : protected CameraParameters
	{
		public:
			Camera();
			~Camera();

			void checkInput();
			void updateMatrix();

			m4 cameraMatrix;
			m4 view;
			m4 projection;

			v3 pos;

			v3 orientation;
			v3 up;

		protected:
			void checkKeyInput();
			void checkMouseInput();

			bool firstClick = true;

	};
	typedef Camera* CameraPTR;


	extern CameraPTR GlobalCamera;


}

#endif // !Camera_HPP

