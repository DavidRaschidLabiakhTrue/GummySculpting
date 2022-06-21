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

void IndexedTriangleDefinition::IndexedTriangle::delevel()
{
	indice[0] = indice[0] - 1;
	indice[1] = indice[1] - 1;
	indice[2] = indice[2] - 1;

}
