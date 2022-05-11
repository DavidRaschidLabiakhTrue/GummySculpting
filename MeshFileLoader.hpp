#ifndef MeshFileLoader_HPP
#define MeshFileLoader_HPP

#include "Mesh.hpp"
#include "GraphicsData.hpp"
#include <fstream>
#include <string>
#include <cstdio>

namespace MeshFileLoader
{
	using std::string;
	using namespace MeshDefinition;
	void loadGumFile(string filepath, Mesh& mesh);
}

namespace MeshFileLoader::Util
{
	void skipFileLines(FILE* file, int linestoSkip);

}

namespace MeshFileLoader::GumLoading
{
	void readVertex(FILE** file, string& str, Mesh& mesh);

#ifdef IMPLEMENT_LINEAR_INDICES
	void readIndice(FILE** file, string& str, Mesh& mesh);
#endif
	KeyData readTriangleIndice(FILE** file, string& str);
	void readTriangle(FILE** file, string& str, Mesh& mesh);

	// actual implementation of reading .gum files
	void readGumMesh(string filePath, Mesh& mesh);
}

#endif
