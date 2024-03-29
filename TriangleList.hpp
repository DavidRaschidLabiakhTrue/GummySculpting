#ifndef TriangleList_HPP
#define TriangleList_HPP

#include "IndexedTriangle.hpp"
#include "Indices.hpp"

namespace TriangleListDefinition
{
    using namespace IndicesDefinition;
    using namespace IndexedTriangleDefinition;

    using std::vector;

    typedef vector<IndexedTriangle> IndexedTriangles;

    /*
     *	OOP encapsulated format of indices to create triangles in a look up format.
     *	Inherited by - Graphics Data -> Mesh Stats -> Mesh
     *	Used to draw meshes via indices in opengl as well as provide direct look ups
     */
    class TriangleList
    {
        public:
            TriangleList();
            ~TriangleList();

            void printTriangleListToConsole() TRINOEXCEPT; // accesses each triangle and prints it's indices to console - debugging only.

            const int triangleCountAsindiceCount() TRINOEXCEPT; // number of triangles * 3 == number of indices used to render
            const int triangleMemorySize() TRINOEXCEPT;         // returns the memory size of triangles allocated
            const int totalTriangles() TRINOEXCEPT;             // a wrapper for triangles.size() as triangle.size() is ambiguous to read.
            IndexedTriangles triangles;
    };

    typedef int IndexedTriangleID; // value meant to refer to a position in the IndexedTriangle List.
} // namespace TriangleListDefinition

#endif // TriangleList_HPP
