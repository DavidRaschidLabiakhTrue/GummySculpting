#ifndef MeshHistory_HPP
#define MeshHistory_HPP


#include "V3D.hpp"
#include "Indices.hpp"

#include <unordered_map>

namespace MeshHistoryDefinition
{
	using namespace VertexDefinition;
	using namespace IndicesDefinition;


	// basically a structure that contains a list of changes onto a mesh using key pair association

	typedef unordered_map<KeyData, V3D> HistoryKeyVertexMap; // maps of previously associated vertex values.

}

#endif