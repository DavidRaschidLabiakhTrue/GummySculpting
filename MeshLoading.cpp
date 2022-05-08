#include "MeshLoading.hpp"

/*
using namespace MeshLoadingFunctions;

namespace GeneralFileFunctions
{
	void skipFileLines(FILE* file, int linestoSkip)
	{
		int count = 0;
		char ret;
		while (ret = fgetc(file))
		{
			if (ret == '\n')
			{
				count += 1;
			}
			if (count == linestoSkip)
			{
				break;
			}
		}
		return;
	}
}


// loads .gum files
namespace GumLoadingFunctions
{
	void readGumVertex(FILE** file, string& str, Mesh& mesh)
	{
		char buffer;
		int lim = 0;
		while (lim != 3)
		{
			while ((buffer = fgetc(*file)) != ' ')
			{
				str += buffer;
			}
			str += ' ';
			lim++;
		}
		v3 vert;
		sscanf(str.c_str(), "%f %f %f", &vert.x, &vert.y, &vert.z); // load the vertex from the string.

		// implement stat computation
		return;
	}
	void readGumIndice(FILE** file, string& str, Mesh& mesh)
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
	void loadMeshFromGum(string meshFilePath, MeshReference mesh)
	{
		std::ifstream reader;
		reader.open(meshFilePath); // open the gum file.

		std::string retname;
		std::string retvertcount;
		std::string retindicecount;
		std::string retcolorcount;

		std::getline(reader, retname);
		std::getline(reader, retvertcount);
		std::getline(reader, retindicecount);
		std::getline(reader, retcolorcount);
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

		FILE* file = fopen(meshFilePath.c_str(), "r");

		if (file == FileNotOpen)
		{
			// raise error
		}

		GeneralFileFunctions::skipFileLines(file, 4);

		string message;
		char parser;
		while ((parser = fgetc(file)) != ' ')
		{
			message += parser;
		}
		//broadcast(message);
		message.clear();

		string str;
		for (int i = 0; i < vertexLim; i++)
		{
			readGumVertex(&file, str, mesh);
			str.clear();
		};
		str.clear();
		for (int j = 0; j < indiceLim; j++)
		{
			readGumIndice(&file, str, mesh);
			str.clear();
		}
		str.clear();

		auto tempcolorgrey = v4(0.5, 0.5, 0.5, 1.0); // grey
		mesh.colorDataUniformly(tempcolorgrey);

		return;
	}
}



// loads .obj files
namespace OBJLoadingFunctions
{
	void loadMeshFromOBJ(string meshFilePath, MeshReference mesh)
	{
		// un-reimplemented
	}
}
// loads .fbx files - stretch goal
namespace FBXLoadingFunctions
{
	void loadMeshFromFBX(string meshFilePath, MeshReference mesh)
	{
		// Not implemented
	}
}

*/