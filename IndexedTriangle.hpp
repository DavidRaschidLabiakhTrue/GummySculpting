#ifndef IndexedTriangle_HPP
#define IndexedTriangle_HPP

#include "Indices.hpp"

namespace IndexedTriangleDefinition
{
    using namespace IndicesDefinition;

#define USING_NOEXCEPT_TRIANGLE

#ifndef USING_NOEXCEPT_TRIANGLE
#define TRINOEXCEPT
#else
#define TRINOEXCEPT noexcept
#endif
    // Implementation of an Indexed Triangle meant for structured face look ups
    struct IndexedTriangle
    {
        public:
            IndexedTriangle();
            ~IndexedTriangle();

            IndexedTriangle(KeyData v0, KeyData v1, KeyData v2)
            {
                indice[0] = v0;
                indice[1] = v1;
                indice[2] = v2;
            }

            KeyData &operator[](const int pos) TRINOEXCEPT; // look up operator to directly access the underlying component of the indices

            void print();      // print the 3 indices in order to console
            KeyData indice[3]; // the actual key components - these values are fed straight into opengl to draw meshes by indice
            void delevel();
            bool swapVertexIndex(int oldIndex, int newIndex) TRINOEXCEPT; // swap out a vertex with a new one.
    };

    typedef IndexedTriangle &RIndexTriangle;

    typedef int TriangleID;
    typedef vector<int> TriangleIDList;

} // namespace IndexedTriangleDefinition

#endif
