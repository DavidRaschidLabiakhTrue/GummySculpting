#ifndef MeshFileExporter_HPP
#define MeshFileExporter_HPP

#include "Mesh.hpp"
#include "GraphicsData.hpp"
#include <fstream>
#include <string>
#include <cstdio>

namespace MeshFileExporter
{
	using std::string;
	using namespace MeshDefinition;
	void exportGumFile(string filepath, Mesh& mesh);
}

namespace MeshFileExporter::GumExporting
{
	void exportGumMesh(string filePath, Mesh& mesh); // export a mesh to .gum file
}

#endif //MeshFileExporter_HPP