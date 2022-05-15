#include "ITree.hpp"

using namespace ITreeDefinition;

ITreeDefinition::ITree::ITree()
{
	// empty
}

ITreeDefinition::ITree::~ITree()
{

}

void ITreeDefinition::ITree::itreeGenerate()
{
	collectStats(); // get the maximum extention data
}


void ITreeDefinition::ITree::inodeSubdivide(INodeID id)
{
	INodeReference ref = inodes[id];

	INodeList newNodes;

	int nodeLevel = inodesTotal(); // 0 elements makes size 0, 1 element makes size 1, with element at 0 - Therefore, the next element is this value from subdivision logic

	for (int i = 0; i < 8; i++)
	{
		ref.children[i] = nodeLevel; // set the child index of the parent to this value.
		nodeLevel++; // raise it so the next child added also fills this slot.
		inodes.emplace_back(INode());
		INodeReference noderef = inodes.back();
		noderef.parent = id;
		noderef.inodeState = INodeState::INodeBody;
		noderef.inodeDepth = ref.inodeDepth + 1;
	}
	const int lastDepthAdded = inodes.back().inodeDepth; // this checks the last added element which should be the latest iteration of subdivision. If it's greater than the tree's depth, update the tree's depth to it.
	if (lastDepthAdded > itreeCurrentDepth)
	{
		itreeCurrentDepth = lastDepthAdded;
	}

	// now the center of each box must be computed.
	// assuming uniform box construction because dynamic box construction has proven to be a failure to develop for efficiently.






}






void ITreeDefinition::ITree::itreeGenerateRoot()
{
	INode rootNode;

	float halfWidth = 0;

	float maxExtent;
	float minExtent;


	// get the lowest and the highest components
	maxExtent = limMax.x > limMax.y ? limMax.x : limMax.y;
	maxExtent = maxExtent > limMax.z ? maxExtent : limMax.z;

	minExtent = limMin.x < limMin.y ? limMin.x : limMin.y;
	minExtent = minExtent < limMin.z ? minExtent : limMin.z;

	if (abs(minExtent) > abs(maxExtent))
	{
		halfWidth = abs(minExtent);
	}
	else
	{
		halfWidth = abs(maxExtent);
	}

	halfWidth *= 1.5f; // raise it 50% to provide some spacing

	rootNode.initializeAsRoot(halfWidth, this->center); // the root should generally always be empty.
	this->inodes.push_back(rootNode);

	// as a general rule of thumb, do not store elements into the rootNode.


}