#include "MeshFileExporter.hpp"

using namespace MeshDefinition;

void MeshFileExporter::exportGumFile(string filepath, Mesh& mesh)
{
	GumExporting::exportGumMesh(filepath, mesh);
}

namespace MeshFileExporter::GumExporting
{

	void exportGumMesh(string filePath, Mesh& mesh)
	{
		std::ofstream writer;
		writer.open(filePath);

		if (writer.is_open())
		{
			writer << "Name: " << mesh.name << '\n';
			writer << "Vertex Count: " << mesh.vertices.size() << '\n';
			writer << "Indice Count: " << mesh.triangles.size() * 3 << '\n';

			writer << "vertexData: ";
			for(int i = 0; i < mesh.vertices.size(); i++)
			{
				writer << mesh.vertices[i].position.x << ' ';
				writer << mesh.vertices[i].position.y << ' ';
				writer << mesh.vertices[i].position.z;
				if (mesh.vertices[i].color != Mesh::defaultMeshColor)
				{
					writer << ' ';
					writer << mesh.vertices[i].color.r << ' ';
					writer << mesh.vertices[i].color.g << ' ';
					writer << mesh.vertices[i].color.b << ' ';
					writer << mesh.vertices[i].color.a;
				}
				writer << " /";
			}
			writer << '\n';

			writer << "IndiceData:";
			forall(tri, mesh.triangles)
			{
				writer << ' ';
				writer << tri.indice[0] << ' ';
				writer << tri.indice[1] << ' ';
				writer << tri.indice[2];
			}
		}
		else {
			//raise error
		}
	}
}