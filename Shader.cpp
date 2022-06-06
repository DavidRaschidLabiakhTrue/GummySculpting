#include "Shader.hpp"
#include "Camera.hpp"

#include <fstream> 
#include <sstream>

namespace ShaderDefinition
{
	Shader StandardShader;
	Shader WireFrameShader;

	Shader StaticMeshShader;

	Shader GridShader;

	void compileGlobalShaders()
	{
		StandardShader.compileShader("StandardShader.vert", "StandardShader.frag", "Standard Shader");
		WireFrameShader.compileShader("WireFrameShader.vert", "WireFrameShader.frag", "WireFrame Shader");
		StaticMeshShader.compileShader("StaticMeshShader.vert", "StaticMeshShader.frag", "Static Mesh Shader");
		GridShader.compileShader("GridShader.vert", "GridShader.frag", "Grid Shader");
	}
}

Usage ShaderDefinition;
Usage ShaderPositionDefinition;
Usage CameraDefinition;



Shader::Shader()
{

}

Shader::~Shader()
{

}



void Shader::use()
{
	glUseProgram(id);
	uploadCameraMatrixToGPU(); // load the camera matrix to the gpu before batch rendering.
}

// need to simplify with Glad wrapper
void Shader::compileShader(string vertexFilePath, string fragmentFilePath, string name)
{
	this->name = name;

	// 1. retrieve the vertex/fragment source code from filePath
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertexFilePath);
		fShaderFile.open(fragmentFilePath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkShaderStatus("VERTEX", vertex);

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkShaderStatus("Fragment", fragment);
	// shader Program
	this->id = glCreateProgram();
	glAttachShader(this->id, vertex);
	glAttachShader(this->id, fragment);
	glLinkProgram(this->id);
	checkShaderStatus("PROGRAM", id);
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);


}
void ShaderDefinition::Shader::uploadScaleFloatToGPU(float renderScale)
{

	glUniform1f(ShaderSlotInfo.scale.position, renderScale);
}

void ShaderDefinition::Shader::uploadOffsetVectorToGPU(rv3 renderOffset)
{

	glUniform3f(ShaderSlotInfo.offset.position, renderOffset.x, renderOffset.y, renderOffset.z);
}

void ShaderDefinition::Shader::uploadStaticColorVectorToGPU(rv4 renderColor)
{

	glUniform4f(ShaderSlotInfo.staticColor.position, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
}

void ShaderDefinition::Shader::uploadModelMatrixToGPU(rm4 model)
{
	glUniformMatrix4fv(ShaderSlotInfo.modelMatrix.position, 1, GL_FALSE, value_ptr(model));
}

void ShaderDefinition::Shader::setStaticColorBool(bool useStaticColor)
{
	glUniform1i(ShaderSlotInfo.staticColorBool.position, useStaticColor);
}

void ShaderDefinition::Shader::uploadProjectionMatrixToGPU()
{
	glUniformMatrix4fv(ShaderSlotInfo.projection.position, 1, GL_FALSE, value_ptr(GlobalCamera->projection));
}

void ShaderDefinition::Shader::uploadViewMatrixToGPU()
{
	glUniformMatrix4fv(ShaderSlotInfo.view.position, 1, GL_FALSE, value_ptr(GlobalCamera->view));
}

void Shader::uploadCameraMatrixToGPU()
{
	//glUniformMatrix4fv(ShaderSlotInfo.cameraMatrix.position, 1, GL_FALSE, value_ptr(GlobalCamera->cameraMatrix));
	uploadProjectionMatrixToGPU();
	uploadViewMatrixToGPU();
}

void Shader::uploadRandomVectorToGPU()
{
	// to be implemented
}

void Shader::compileStandardShader()
{
	compileShader("StandardShader.vert", "StandardShader.frag", "Standard Shader");
}

void Shader::compileWireFrameShader()
{
	compileShader("WireFrameShader.vert", "WireFrameShader.frag", "WireFrame Shader");
}



void Shader::checkShaderStatus(string shaderType, int shaderProgramID)
{
	int success; // does not need initialized;
	char infoLog[1024] = { 0 }; // zero out
	std::string compileErrorSTR = "";
	if (shaderType != "PROGRAM")
	{
		glGetShaderiv(shaderProgramID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			cout << "Shader component" + shaderType +"failed to Compile\n";
			glGetShaderInfoLog(shaderProgramID, 1024, NULL, infoLog);
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			cout << "Shader Program failed to Compile\n";
			glGetShaderInfoLog(id, 1024, NULL, infoLog);
		}
	}
}
