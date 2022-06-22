#ifndef MeshFileLoader_HPP
#define MeshFileLoader_HPP

#include "Mesh.hpp"
#include "StaticMesh.hpp"
#include "GraphicsData.hpp"
#include <fstream>
#include <string>
#include <cstdio>

namespace MeshFileLoader
{
	using std::string;
	using namespace MeshDefinition;
	using namespace StaticMeshDefinition;
	// wrapper for gum mesh file loading
	void loadGumFile(string filepath, Mesh& mesh);

	void loadGumFile(string filepath, StaticMeshReference mesh, bool shouldBind = true);

	void loadObjFile(string filepath, Mesh& mesh);
}

namespace MeshFileLoader::Util
{
	void skipFileLines(FILE* file, int linestoSkip); // skip lines in a FILE*
	void skipMessage(FILE* file); //skips beginning text of a line in a FILE*
}

namespace MeshFileLoader::GumLoading
{
	void readVertex(FILE** file, string& str, Mesh& mesh); // read a vertex into memory
	KeyData readTriangleIndice(FILE** file, string& str); // read a triangle into memory from indice
	void readTriangle(FILE** file, string& str, Mesh& mesh); // read a triangle into memory
	void readColor(FILE** file, string& str, Mesh& mesh); // read vertex colors into memory

	// actual implementation of reading .gum files into mesh
	void readGumMesh(string filePath, Mesh& mesh); // read a .gum mesh into memory

#ifdef IMPLEMENT_LINEAR_INDICES
	void readIndice(FILE** file, string& str, Mesh& mesh);
#endif



	void readVertex(FILE** file, string& str, StaticMeshReference mesh); // read a vertex into memory
	KeyData readTriangleIndice(FILE** file, string& str); // read a triangle into memory from indice
	void readTriangle(FILE** file, string& str, StaticMeshReference mesh); // read a triangle into memory
	void readGumMesh(string filePath, StaticMeshReference mesh);


}

namespace MeshFileLoader::ObjLoading
{
	void readObjTriangle(string& str, Mesh& mesh);
	void readOBJVertex(string& str, Mesh& mesh);
	void readObjMesh(string filePath, Mesh& mesh);
}

#endif
