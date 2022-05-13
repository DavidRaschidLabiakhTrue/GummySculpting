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
	void loadGumFile(string filepath, Mesh& mesh); // wrapper for gum mesh file loading
}

namespace MeshFileLoader::Util
{
	void skipFileLines(FILE* file, int linestoSkip); // skip lines in a FILE*

}

namespace MeshFileLoader::GumLoading
{
	void readVertex(FILE** file, string& str, Mesh& mesh); // read a vertex into memory

#ifdef IMPLEMENT_LINEAR_INDICES
	void readIndice(FILE** file, string& str, Mesh& mesh);
#endif
	KeyData readTriangleIndice(FILE** file, string& str); // read a triangle into memory from indice
	void readTriangle(FILE** file, string& str, Mesh& mesh); // read a triangle into memory

	// actual implementation of reading .gum files
	void readGumMesh(string filePath, Mesh& mesh); // read a .gum mesh into memory
}

#endif
