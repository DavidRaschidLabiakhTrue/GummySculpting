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

// this format allows for iteration
v3 INodeDefinition::INode::assignChildNodeCenter(INodeMortonCodePosition iteratorID)
{
	switch (iteratorID)
	{
		case INodeMortonCodePosition::TopFrontLeft:
			return (this->boxCenter + this->boxTopFrontLeft()) / 2.0f;

		case INodeMortonCodePosition::TopFrontRight:
			return (this->boxCenter + this->boxTopFrontRight()) / 2.0f;

		case INodeMortonCodePosition::TopBackRight:
			return (this->boxCenter + this->boxTopBackRight()) / 2.0f;

		case INodeMortonCodePosition::TopBackLeft:
			return (this->boxCenter + this->boxTopBackLeft()) / 2.0f;

		case INodeMortonCodePosition::BottomFrontLeft:
			return (this->boxCenter + this->boxBottomFrontLeft()) / 2.0f;

		case INodeMortonCodePosition::BottomFrontRight:
			return (this->boxCenter + this->boxBottomFrontRight()) / 2.0f;

		case INodeMortonCodePosition::BottomBackRight:
			return (this->boxCenter + this->boxBottomBackRight()) / 2.0f;

		case INodeMortonCodePosition::BottomBackLeft:
			return (this->boxCenter + this->boxBottomBackLeft()) / 2.0f;

		default:
			say "CRITICAL ERROR @ assignChildNodeCenter";
			return v3(0);
	}

}
/*
		TopFrontLeft = 0,
		TopFrontRight = 2,

		TopBackRight = 3,
		TopBackLeft = 1,

		BottomFrontLeft = 4,
		BottomFrontRight = 6,

		BottomBackRight = 7,
		BottomBackLeft = 5
*/