#include "MeshFileExporter.hpp"

using namespace MeshDefinition;

void MeshFileExporter::exportGumFile(string filepath, Mesh& mesh)
{
	GumExporting::exportGumMesh(filepath, mesh);
}

void MeshFileExporter::exportStlFile(string filepath, Mesh& mesh)
{
	StlExporting::exportStlMesh(filepath, mesh);
}

namespace MeshFileExporter::GumExporting
{
	void exportGumMesh(string filePath, Mesh& mesh)
	{
		ofstream outfile;
		outfile.open(filePath);

		if (outfile.is_open())
		{
			outfile << "Name: " << mesh.name << '\n';
			outfile << "Vertex Count: " << mesh.vertices.size() << '\n';
			outfile << "Indice Count: " << mesh.triangles.size() * 3 << '\n';

			outfile << "vertexData: ";
			for(int i = 0; i < mesh.vertices.size(); i++)
			{
				outfile << mesh.vertices[i].position.x << ' ';
				outfile << mesh.vertices[i].position.y << ' ';
				outfile << mesh.vertices[i].position.z;
				if (mesh.vertices[i].color != Mesh::defaultMeshColor)
				{
					outfile << ' ';
					outfile << mesh.vertices[i].color.r << ' ';
					outfile << mesh.vertices[i].color.g << ' ';
					outfile << mesh.vertices[i].color.b << ' ';
					outfile << mesh.vertices[i].color.a;
				}
				outfile << " /";
			}
			outfile << '\n';

			outfile << "IndiceData:";
			forall(tri, mesh.triangles)
			{
				outfile << ' ';
				outfile << tri.indice[0] << ' ';
				outfile << tri.indice[1] << ' ';
				outfile << tri.indice[2];
			}
		}
		else {
			//raise error
		}

		outfile.close();
	}
}

namespace MeshFileExporter::StlExporting
{
	void exportStlMesh(string filePath, Mesh& mesh)
	{
		ofstream outfile = ofstream(filePath, ios::out | ios::binary);
		if (outfile.is_open())
		{
			unsigned int numTriangles, attrByteCount;
			v3 normal;
			V3D vert1, vert2, vert3;

			numTriangles = (unsigned int)mesh.triangles.size();
			attrByteCount = 0;

			outfile.write("Exported from Gummy", 0x50);
			outfile.write((char*)&numTriangles, 0x4);

			for(int i = 0; i < mesh.triangles.size(); i++)
			{
				normal = mesh.getTriangleNormal(i);
				vert1 = mesh.vertices[mesh.triangles[i][0]];
				vert2 = mesh.vertices[mesh.triangles[i][1]];
				vert3 = mesh.vertices[mesh.triangles[i][2]];

				//write normal vector
				outfile.write((char*)&normal, 0xC);
				//write vertices
				outfile.write((char*)&vert1, 0xC);
				outfile.write((char*)&vert2, 0xC);
				outfile.write((char*)&vert3, 0xC);
				//write "attribute byte count", should just be 0
				outfile.write((char*)&attrByteCount, 0x2);
			}
		}
		else {
			//raise error
		}

		outfile.close();
	}
}