#ifndef Shader_HPP
#define Shader_HPP

#include "OpenGLWrapper.hpp"
#include "ShaderPosition.hpp"


namespace ShaderDefinition
{
	Usage ShaderPositionDefinition;

	class Shader
	{
		public:
			Construct Shader();
			Deconstruct ~Shader();

			void use(); // load shader for usage on program load.
			void compileShader(string vertexFilePath, string fragmentFilePath, string name); // compile a shader file.
			
			void compileStandardShader();
			void compileWireFrameShader();

			string name; // name of shader for debugging
			
		protected:
			void uploadCameraMatrixToGPU(); // send the camera matrix to opengl to load into the shaders on the GPU.
			void uploadRandomVectorToGPU();
			int id; // shader id on gpu
			void checkShaderStatus(string shaderType, int shaderProgramID); // check the shader compilation status.

	};
	extern Shader StandardShader;
	extern Shader WireFrameShader;

	extern void compileGlobalShaders();
}

#endif
