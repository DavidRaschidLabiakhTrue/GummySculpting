#include "INode.hpp"

using namespace INodeDefinition;

INodeDefinition::INode::INode()
{
}

INodeDefinition::INode::~INode()
{
}

const int INodeDefinition::INode::inodeTotalElements()
{
    return elements.size();
}

void INodeDefinition::INode::initializeAsRoot(float halfWidth, rv3 center)
{


	this->parent = -1; // there is no parent to the root
	this->inodeState = INodeState::INodeRoot;
	this->inodeDepth = 0; // root depth is 0.
}
