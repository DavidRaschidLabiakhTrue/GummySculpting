#ifndef VertexIDHashing_HPP
#define VertexIDHashing_HPP

#include "MeshStats.hpp"


namespace VertexIDHashingDefinition
{
	// Not Happy about this code at all. This is just Lambda with more steps. Anonymous undocumented functions for what they are supposed to achieve.
	using namespace MeshStatsDefinition;


	struct point_hash
	{
		std::size_t operator()(const KeyData& p) const
		{
            return std::hash<int>()(p);
		}
	};


	struct point_equal
	{
		bool operator()(const KeyData& p1, const KeyData& p2) const
		{
			return p1 == p2;
		}
	};

}

#endif