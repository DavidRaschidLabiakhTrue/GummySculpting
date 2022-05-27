#include "IndexedTriangle.hpp"
using namespace IndexedTriangleDefinition;

IndexedTriangle::IndexedTriangle()
{
}

IndexedTriangle::~IndexedTriangle()
{
}

KeyData& IndexedTriangleDefinition::IndexedTriangle::operator[](const int pos) TRINOEXCEPT
{
	return indice[pos];
}

void IndexedTriangle::print()
{
	say indice[0] spc indice[1] spc indice[2] << ' ';
}
