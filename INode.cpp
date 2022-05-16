#include "INode.hpp"

using namespace INodeDefinition;

INodeDefinition::INode::INode()
{
}

INodeDefinition::INode::INode(v3 subdividedCenter, float subdividedHalfSize)
{
	this->boxCenter = subdividedCenter;
	this->boxHalfSize = subdividedHalfSize;
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

	this->boxCenter = center;
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

void INodeDefinition::INode::generateVisualVertices(Vertices& vertices, Indices& indices, int& counter)
{

	// these values **are not** MortonCode Values
	// these are just commenting on the way indices are ordered to draw a cube. **Nothing more**.
	vertices.emplace_back(V3D(boxTopFrontLeft())); // 0
	vertices.emplace_back(V3D(boxTopFrontRight())); // 1

	vertices.emplace_back(V3D(boxBottomFrontRight())); // 2
	vertices.emplace_back(V3D(boxBottomFrontLeft())); // 3

	vertices.emplace_back(V3D(boxBottomBackLeft())); // 4
	vertices.emplace_back(V3D(boxBottomBackRight())); // 5

	vertices.emplace_back(V3D(boxTopBackRight())); // 6
	vertices.emplace_back(V3D(boxTopBackLeft())); // 7


	// counter is synced up as counter == 0 // assuming the first box starts at 0 and ends at 7, then the next box is in that sequence

	int topfrontleft = ++counter;
	int topfrontright = ++counter;

	int bottomfrontright = ++counter;
	int bottomfrontleft = ++counter;

	int bottombackleft = ++counter;
	int bottombackright = ++counter;

	int topbackright = ++counter;
	int topbackleft = ++counter;

	// BEGINNING OF FRONT FACE

	indices.emplace_back(topfrontleft);
	indices.emplace_back(topfrontright);

	indices.emplace_back(topfrontright);
	indices.emplace_back(bottomfrontright);

	indices.emplace_back(bottomfrontright);
	indices.emplace_back(bottomfrontleft);

	indices.emplace_back(bottomfrontleft);
	indices.emplace_back(topfrontleft);

	// END OF FRONT FACE

	// BEGINNING OF RIGHT FACE

	indices.emplace_back(topfrontright);
	indices.emplace_back(topbackright);

	indices.emplace_back(topbackright);
	indices.emplace_back(bottombackright);

	indices.emplace_back(bottombackright);
	indices.emplace_back(bottomfrontright);

	// END OF RIGHT FACE

	// BEGINNING OF BACK FACE

	indices.emplace_back(topbackright);
	indices.emplace_back(topbackleft);

	indices.emplace_back(topbackleft);
	indices.emplace_back(bottombackleft);

	indices.emplace_back(bottombackleft);
	indices.emplace_back(bottombackright);

	// END OF BACK FACE

	// BEGINNING OF LEFT FACE

	indices.emplace_back(topbackleft);
	indices.emplace_back(topfrontleft);

	indices.emplace_back(bottombackleft);
	indices.emplace_back(bottomfrontleft);

	// END OF LEFT FACE


	return;
}
