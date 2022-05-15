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