#include "MeshFileLoader.hpp"


// the call implementation
void MeshFileLoader::loadGumFile(string filepath, Mesh& mesh)
{
	GumLoading::readGumMesh(filepath, mesh); // the actual implementation
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
}
namespace MeshFileLoader::GumLoading
{
	void readVertex(FILE** file, string& str, Mesh& mesh)
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
		V3D vert;
		sscanf(str.c_str(), "%f %f %f", &vert.position.x, &vert.position.y, &vert.position.z); // load the vertex from the string.
		mesh.vertices.push_back(vert);

		return;
	}
	void readIndice(FILE** file, string& str, Mesh& mesh)
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

	void readGumMesh(string filePath, Mesh& mesh)
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

		string message;
		char parser;
		while ((parser = fgetc(file)) != ' ')
		{
			message += parser;
		}

		message.clear();

		string str;
		for (int i = 0; i < vertexLim; i++)
		{
			readVertex(&file, str, mesh);
			str.clear();
		};

		str.clear();

		for (int j = 0; j < indiceLim; j++)
		{
			readIndice(&file, str, mesh);
			str.clear();
		}
		str.clear();
		auto uniformcolor = v4(0.5, 0.5, 0.5, 1.0);
		mesh.colorDataUniformly(uniformcolor);
		
		fclose(file);

		return;
	}
}

