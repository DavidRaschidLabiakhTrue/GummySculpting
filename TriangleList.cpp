#include "TriangleList.hpp"

Usage TriangleListDefinition;

TriangleList::TriangleList()
{
}

TriangleList::~TriangleList()
{
}

const int TriangleList::triangleCountAsindiceCount() TRINOEXCEPT
{
    return (triangles.size()) * 3;
}

const int TriangleList::triangleMemorySize() TRINOEXCEPT
{
    return triangles.size() * (sizeof(IndexedTriangle));
}

const int TriangleListDefinition::TriangleList::totalTriangles() TRINOEXCEPT
{
    return triangles.size();
}

void TriangleList::printTriangleListToConsole() TRINOEXCEPT
{
    forall(tri, triangles)
    {
        tri.print();
    }
    say "\n";
}