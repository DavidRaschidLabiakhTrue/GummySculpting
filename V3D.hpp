#ifndef V3D_HPP
#define V3D_HPP

#include "MathDefinitions.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define NOTUSINGNORMALORUV

namespace VertexDefinition
{
    Usage MathTypeDefinitions::CoordinateDefine;
    using std::unordered_map;
    using std::unordered_set;
    using std::vector;

    // formal definition of a vertex structure
    typedef unsigned int BitData; // used to clarify this data will only ever be accessed with bits.

    namespace GlobalVertexParameters
    {
        extern const float DefaultAlphaValue;
        extern const v4 DefaultColorLoader;
        extern const BitData DefaultBinaryWeightData;
    } // namespace GlobalVertexParameters

    struct V3D
    {
        public:
            Construct V3D();
            V3D(v3 pos);
            Construct V3D(float x, float y, float z);
            Construct V3D(float x, float y, float z, float r, float g, float b);
            Deconstruct ~V3D();

            void operator=(v3 newPosition);  // can be used to load a position directly into the vertex
            void operator=(rv3 newPosition); // can be used to load a position directly into the vertex
            void operator=(v4 newColor);     // can be used to load a color directly into the vertex
            void operator=(rv4 newColor);    // can be used to load a color directly into the vertex

            void operator+=(v3 positionOffset); // shift vertices
            void operator-=(v3 positionOffset); // shift vertices

            void operator+=(v4 addColor);       // shift colot
            void operator-=(rv4 subtractColor); // shift colot

            void setPositionToCenter(); // forces the position to go to (0,0,0) - debugging only.

            void loadColorAs255(int r, int g, int b); // load in a color by a 255 color scale(easier to understand wtf is happening)
            void loadColorDirectly(rv4 colorVector);
            void printPosition(); // print position to console
            void printColor();    // print color to console - excludes alpha which is assumed 1.0

            void printSlots();                      // print all slot data.
            void removeTriangle(int triangleIndex); // erase a triangle from the vertex
            void addTriangle(int triangleIndex);    // add a triangle to the vertex

            v3 position;
            v4 color; // shrink to v3 eventually.
            v3 normal = v3(0);


            unordered_set<int> triangleIDs; // Triangles that this vertex is a part of.  - 100% SUSSY 

            unordered_map<char, int> ABCDmap; // Reserved for subdivision to keep track of which vertices to use for Loop's equation. - not sussy, trust - COMPLETEY FUCKING SUSSY BRO - 100% SUSSY 
#ifndef NOTUSINGNORMALORUV
            // Don't use these unless specified. They aren't needed.

            v2 uv;
#endif // !NOTUSINGNORMALORUV
    };

    typedef V3D &RV3D;
    typedef vector<V3D> Vertices;

} // namespace VertexDefinition

#endif // !V3D_HPP
