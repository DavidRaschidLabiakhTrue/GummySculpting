#include "IndexedTriangle.hpp"
using namespace IndexedTriangleDefinition;

IndexedTriangle::IndexedTriangle()
{
}

IndexedTriangle::~IndexedTriangle()
{
}

KeyData &IndexedTriangleDefinition::IndexedTriangle::operator[](const int pos) TRINOEXCEPT
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

void IndexedTriangleDefinition::IndexedTriangle::swapVertexIndex(int oldIndex, int newIndex) TRINOEXCEPT
{
    if (indice[0] == oldIndex)
    {
        indice[0] = newIndex;
    }
    else if (indice[1] == oldIndex)
    {
        indice[1] = newIndex;
    }
    else if (indice[2] == oldIndex)
    {
        indice[2] = newIndex;
    }
    else
    {
        say "Error:\tCannot swap vertex '" << oldIndex << "' for '" << newIndex << "'"
                                          << "\n\tValid indices:" spc indice[0] spc indice[1] spc indice[2] done;
    }
}
