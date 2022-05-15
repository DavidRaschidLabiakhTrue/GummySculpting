#ifndef INode_HPP
#define INode_HPP

#include "MeshStats.hpp"

#include "SamplerPayload.hpp"

#include "INodeBox.hpp"

#include <unordered_set>

namespace INodeDefinition
{
	using namespace MeshStatsDefinition;
	using namespace SamplerPayloadDefinition;
	using std::unordered_set;

	using namespace INodeBoxDefinition;

	typedef unordered_set<KeyData> NodeElements;

	typedef int INodeParent;
	typedef int INodeChildren;
	typedef int INodeDepth;
	typedef int INodeID;


	#define INodeLimit 100

	#define UnassignedINodeChild -1
	#define UnassignedINodeParent -2
	#define UnassignedINodeID -1
	#define UninitializedINodeDepth -1


	enum INodeState
	{
		INodeUnset = 0, // new node 
		INodeRoot = 1, // definitely the root node
		INodeBody = 2 // body node == not root
	};

	class INode : public INodeBox
	{
		public:
			INode();
			~INode();
			const int inodeTotalElements();
			void initializeAsRoot(float halfWidth, rv3 center);

			NodeElements elements; // unordered set of elements to allow for faster removal of elements
			INodeParent parent = UnassignedINodeParent;
			INodeChildren children[8] = { UnassignedINodeChild };
			INodeDepth inodeDepth = UninitializedINodeDepth;
			INodeID inodeID = UnassignedINodeID;
			INodeState inodeState = INodeState::INodeUnset;


	};

	typedef INode& INodeReference;
}

#endif // !INode_HPP
