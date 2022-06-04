#ifndef Shader_HPP
#define Shader_HPP

#include "OpenGLWrapper.hpp"
#include "ShaderPosition.hpp"
#include "MathDefinitions.hpp"

namespace ShaderDefinition
{
	Usage ShaderPositionDefinition;
	using namespace MathTypeDefinitions::CoordinateDefine;

	// shader class that enables meshes to be drawn on the GPU through a shader program
	class Shader
	{
		public:
			Construct Shader();
			Deconstruct ~Shader();

			void use(); // load shader for usage on program load.

			void compileShader(string vertexFilePath, string fragmentFilePath, string name); // compile a shader file.
			
			void compileStandardShader(); // hard coded compiling
			void compileWireFrameShader(); // hard coded compiling


			void uploadScaleFloatToGPU(float renderScale);
			void uploadOffsetVectorToGPU(rv3 renderOffset);
			void uploadStaticColorVectorToGPU(rv4 renderColor);

			string name; // name of shader for debugging
			
		protected:
			void uploadProjectionMatrixToGPU();
			void uploadViewMatrixToGPU();
			void uploadCameraMatrixToGPU(); // send the camera matrix to opengl to load into the shaders on the GPU.
			void uploadRandomVectorToGPU();
			int id; // shader id on gpu
			void checkShaderStatus(string shaderType, int shaderProgramID); // check the shader compilation status.

	};
	extern Shader StandardShader;
	extern Shader WireFrameShader;
	extern Shader StaticMeshShader;

	extern void compileGlobalShaders();
}

#endif
