#ifndef MeshChangeLog_HPP
#define MeshChangeLog_HPP

#include "MeshStats.hpp"
#include "MeshHistory.hpp"



namespace MeshChangeLogDefinition
{
	using namespace MeshStatsDefinition;

	using namespace MeshHistoryDefinition;

	using std::unordered_map;

	typedef vector<HistoryKeyVertexMap> HistoryChangeList; // vector of maps that contain key based changes.

	/*
	*	Contains a mesh's change history. Stored in Mesh.
	*	Sampler/Brush Operate on this class directly used it to store vertices changes.
	*	*Not to be Inherited*
	*/

	class ChangeLog
	{
		public:
			ChangeLog();
			~ChangeLog();



			HistoryChangeList changeList; // store changes in mesh history onto a stack.
	};
}

#endif