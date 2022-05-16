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
	itreeGenerateRoot();
	inodeSubdivide(0); // subdivide the root to get the iTree started up.


}


void ITreeDefinition::ITree::inodeSubdivide(INodeID id)
{


	int nodeLevel = inodesTotal() - 1; // 0 elements makes size 0, 1 element makes size 1, with element at 0 - Therefore, the next element is this value from subdivision logic
	const float newHalfWidth = inodes[id].boxHalfSize * 0.5f;


	for (int i = 0; i < 8; i++)
	{
		inodes[id].children[i] = nodeLevel; // set the child index of the parent to this value.
		nodeLevel++; // raise it so the next child added also fills this slot.
		INode newNode = INode(inodes[id].assignChildNodeCenter((INodeMortonCodePosition)i), newHalfWidth);
		newNode.parent = id;
		newNode.inodeState = INodeState::INodeBody;
		newNode.inodeDepth = inodes[id].inodeDepth + 1;

		inodes.push_back(newNode);
	}



	const int lastDepthAdded = inodes[nodeLevel].inodeDepth; // this checks the last added element which should be the latest iteration of subdivision. If it's greater than the tree's depth, update the tree's depth to it.
	if (lastDepthAdded > itreeCurrentDepth)
	{
		say "New Divided depth:" spc lastDepthAdded done;
		itreeCurrentDepth = lastDepthAdded;
	}

	say "Octree Subdivided, total ictants:" spc inodes.size() done;
	say "currentDepth:" spc itreeCurrentDepth done;
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