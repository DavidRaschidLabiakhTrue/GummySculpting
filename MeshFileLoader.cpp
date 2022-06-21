#include "MeshFileLoader.hpp"

using namespace MeshDefinition;

// the call implementation
void MeshFileLoader::loadGumFile(string filepath, MeshReference mesh)
{
	GumLoading::readGumMesh(filepath, mesh); // the actual implementation
	mesh.bind();
	mesh.createVariableMap();
	mesh.generateGraphsAndTrees();
}

// static mesh overload
void MeshFileLoader::loadGumFile(string filepath, StaticMeshReference mesh, bool shouldBind)
{
	GumLoading::readGumMesh(filepath, mesh);

	if (shouldBind)
	{
		mesh.collectStats();
		mesh.bind(); // this mesh is going to be only modified in the shader as it is static.
	}
}

void MeshFileLoader::loadObjFile(string filepath, MeshReference mesh)
{
	ObjLoading::readObjMesh(filepath, mesh);
	mesh.bind();
	mesh.createVariableMap();
	mesh.generateGraphsAndTrees();
}

namespace MeshFileLoader::Util
{
	void skipFileLines(FILE* file, int linestoSkip)
	{
		int count = 0;
		char ret;
		while (ret = fgetc(file))
		{
			//std::cout << ret;
			if (ret == '\n')
			{
				count += 1;
				//std::cout << "nl found\n";
			}

			if (count == linestoSkip)
				break;
		}
		//std::cout << "end of skip\n";
		return;
	}

	void skipMessage(FILE* file)
	{
		string message;
		char parser;
		while ((parser = fgetc(file)) != ' ')
		{
			if (parser == EOF)
				break;
			message += parser;
		}

		message.clear();
		return;
	}
}
namespace MeshFileLoader::GumLoading
{
	void readVertex(FILE** file, string& str, MeshReference mesh)
	{
		char buffer;
		int lim = 0;

		while (lim != 3)
		{
			while ((buffer = fgetc(*file)) != ' ')
			{
				str.push_back(buffer);
			}
			str.push_back(' ');
			lim++;
		}
		V3D vert;
		
		sscanf(str.c_str(), "%f %f %f", &vert.position.x, &vert.position.y, &vert.position.z); // load the vertex from the string.
		mesh.vertices.push_back(vert);

		return;
	}

#ifdef IMPLEMENT_LINEAR_INDICES
	// UNIMPLEMENTED - COLLAPSE
	void readIndice(FILE** file, string& str, MeshReference mesh)
	{
		char parser;
		while ((parser = fgetc(*file)) != ' ')
		{
			if (parser == '\n')
				break;
			str += parser;
		}
		mesh.indices.push_back(stoi(str));
	}
#endif
	KeyData readTriangleIndice(FILE** file, string& str)
	{
		char parser;
		while ((parser = fgetc(*file)) != ' ')
		{
			if (parser == '\n')
				break;
			str.push_back(parser);
		}
		return (KeyData)stoi(str);
	}

    void GumLoading::readGumMesh(string filePath, StaticMeshReference mesh)
    {
		Mesh rMesh;

		readGumMesh(filePath, rMesh);
		// hacky but simple
		mesh.vertices.insert(mesh.vertices.begin(), rMesh.vertices.begin(), rMesh.vertices.end());
		mesh.triangles.insert(mesh.triangles.begin(), rMesh.triangles.begin(), rMesh.triangles.end());

    }


	void GumLoading::readTriangle(FILE** file, string& str, MeshReference mesh)
	{
		IndexedTriangle tri;
		tri[0] = readTriangleIndice(file, str);
		str.clear();
		tri[1] = readTriangleIndice(file, str);
		str.clear();
		tri[2] = readTriangleIndice(file, str);
		str.clear();

		TriangleID triangleID = (TriangleID) mesh.triangles.size();
		mesh.vertices[tri[0]].triangleIDs.emplace_back(triangleID);
		mesh.vertices[tri[1]].triangleIDs.emplace_back(triangleID);
		mesh.vertices[tri[2]].triangleIDs.emplace_back(triangleID);

		mesh.triangles.push_back(tri);
	}

	void readColor(FILE** file, string& str, MeshReference mesh)
	{
		//read index of vertex
		char parser;
		while ((parser = fgetc(*file)) != ' ')
		{
			say parser;
			if (parser == EOF)
				break;
			str.push_back(parser);
		}
		int idx = stoi(str);
		str.clear();

		//read float color values
		for (int i = 0; i < 4; i++)
		{
			while ((parser = fgetc(*file)) != ' ')
			{
				if (parser == EOF)
					break;
				str.push_back(parser);
			}
			str.push_back(' ');
		}
		sscanf(str.c_str(), "%f %f %f %f", &mesh.vertices[idx].color.r, &mesh.vertices[idx].color.g, &mesh.vertices[idx].color.b, &mesh.vertices[idx].color.a);
		str.clear();

		return;
	}

	void readGumMesh(string filePath, MeshReference mesh)
	{

		std::ifstream reader;
		reader.open(filePath); // open the gum file.

		std::string retname;
		std::string retvertcount;
		std::string retindicecount;
		std::string retcolorcount;

		std::getline(reader, retname);
		std::getline(reader, retvertcount);
		std::getline(reader, retindicecount);
		std::getline(reader, retcolorcount);

		mesh.name = retname.substr(6, retvertcount.size());
		retvertcount = retvertcount.substr(14, retvertcount.size());
		retindicecount = retindicecount.substr(14, retindicecount.size());

		if (retcolorcount.substr(13, retcolorcount.size()) == "")
		{
			retcolorcount = "0";

		}
		else
			retcolorcount = retcolorcount.substr(12, retcolorcount.size());

		int vertexLim = std::stoi(retvertcount);
		int indiceLim = std::stoi(retindicecount);
		int colorLim = std::stoi(retcolorcount);

		reader.close();
		// this may seem odd to do...
		//but it's because C++ file importing sucks and is very slow when precision is desperately needed.

		FILE* file = fopen(filePath.c_str(), "r");
		ifn(file)
		{
			say "Error: Cannot Open .gum file" done;
			return;
		}
		MeshFileLoader::Util::skipFileLines(file, 4);

		mesh.vertices.reserve(vertexLim);
		mesh.triangles.reserve(indiceLim / 3);

		MeshFileLoader::Util::skipMessage(file);

		string str;
		for (int i = 0; i < vertexLim; i++)
		{
			readVertex(&file, str, mesh);
			str.clear();
		};

		str.clear();

		const int triLimit = indiceLim / 3;
		for (int j = 0; j < triLimit; j++)
		{
			readTriangle(&file, str, mesh);
		}

		str.clear();

		MeshFileLoader::Util::skipMessage(file);

		auto uniformcolor = Mesh::defaultMeshColor;
		mesh.colorDataUniformly(uniformcolor);

		for (int k = 0; k < colorLim; k++)
		{
			readColor(&file, str, mesh);
		}

		fclose(file);

		return;
	}
}



void MeshFileLoader::ObjLoading::readObjTriangle(string& str, MeshReference mesh)
{
	using IndexedTriangleDefinition::IndexedTriangle;

	IndexedTriangle tri;
	sscanf(str.c_str(), "%d %d %d", &tri.indice[0], &tri.indice[1], &tri.indice[2]);
	tri.delevel();
	mesh.triangles.push_back(tri); // not a fan of not being able to use reserve on this.

	

}

void MeshFileLoader::ObjLoading::readOBJVertex(string& vertexString, MeshReference mesh)
{
	v3 vert;
	sscanf(vertexString.c_str(), "%f %f %f", &vert.x, &vert.y, &vert.z);
	mesh.vertices.push_back(vert);
}

void MeshFileLoader::ObjLoading::readObjMesh(string filePath, MeshReference mesh)
{
	ifstream reader;
	string str;
	reader.open(filePath);

	if (!reader.is_open())
	{
		say "Cannot open file" spc filePath done;
		return;
	}
	
	while (getline(reader, str))
	{
		if (str.size() == 0 || str[0] == '#')
			continue;

		if (str.substr(0, 2) == "v ")
		{
			str = str.substr(2, str.length());
			readOBJVertex(str, mesh);
			continue;
		}
		if (str.substr(0, 2) == "f ")
		{
			str = str.substr(2, str.length());
			readObjTriangle(str, mesh);
			continue;

		}
		if (str.substr(0, 2) == "s ") // don't care
		{
			continue; // not implemented
		}
		if (str.substr(0, 3) == "vt ") // don't care
		{
			continue; // not implemented
		}
		if (str.substr(0, 3) == "vn ") // don't care
		{
			continue; // not implemented
		}
		if (str.substr(0, 2) == "o ")
		{
			mesh.name = str;
			continue; // not implemented

		}
	}


	return;
}
