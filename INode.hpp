#ifndef INode_HPP
#define INode_HPP

#include "MeshStats.hpp"

#include "SamplerPayload.hpp"

#include "INodeBox.hpp"

#include <unordered_set>

#include "VertexList.hpp"
#include "IndiceList.hpp"
#include <utility>

namespace INodeDefinition
{
	using namespace MeshStatsDefinition;
	using namespace SamplerPayloadDefinition;

	using namespace VertexListDefinition;
	using namespace IndiceListDefinition;
	using std::pair;
	using std::make_pair;
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

			v3 assignChildNodeCenter(INodeMortonCodePosition iteratorID); // take in an morton code value and returns an subdivided INode center

			NodeElements elements; // unordered set of elements to allow for faster removal of elements
			INodeParent parent = UnassignedINodeParent;
			INodeChildren children[8] = { UnassignedINodeChild };
			INodeDepth inodeDepth = UninitializedINodeDepth;
			INodeID inodeID = UnassignedINodeID;
			INodeState inodeState = INodeState::INodeUnset;

			void generateVisualVertices(Vertices& vertices, Indices& indices, int& counter); // generate Visual Vertices
			

	};

	typedef INode& INodeReference;
}

#endif // !INode_HPP
