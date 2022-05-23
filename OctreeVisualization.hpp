#ifndef OctreeVisualization_HPP
#define OctreeVisualization_HPP

#include "Octree.hpp"
#include "Shader.hpp"

namespace OctreeVisualizationDefinition
{
    using namespace OctreeDefinition;
    using namespace ShaderDefinition;

    enum DrawMode
    {
        AllOctants = 0,
        LeafOctants = 1
    };

    enum DepthColorMode
    {
        NoDepthColor = 0,
        EnableDepthColor = 1,
        EnableColorWithTriangles = 2
    };

    enum DepthColor
    {
        White = 0,
        Red = 1,
        Cyan = 2,
        Green = 3,
        Yellow = 4,
        Magenta = 5,
        Blue = 6,
        Pink = 7,
        Orange = 8,
        Purple = 9
    };

    struct OctreeWireframe
    {
            Indices octreeIndices;
            Vertices octreeVertices;
            bool shouldDraw = true;
    };

    class OctreeVisualization : public Octree
    {
        public:
            void generateOctreeVisualization(DrawMode = AllOctants, DepthColorMode = NoDepthColor);
            void generateOCtantWireframe(OctantIndex octantID);
            void bindOctreeWireframe();
            void drawOctreeWireframe();
            DrawMode drawMode = AllOctants;
            DepthColorMode depthColorMode = NoDepthColor;
            OctreeWireframe octreeWireframe;
            GraphicsBufferObject gboOctreeWireframe;

            v4 DepthColors[20] = {
                v4(1.0f, 1.0f, 1.0f, 1.0f), // White
                v4(1.0f, 0.0f, 0.0f, 1.0f), // Red
                v4(0.0f, 1.0f, 1.0f, 1.0f), // Cyan
                v4(0.0f, 1.0f, 0.0f, 1.0f), // Green
                v4(1.0f, 1.0f, 0.0f, 1.0f), // Yellow
                v4(1.0f, 0.0f, 1.0f, 1.0f), // Magenta
                v4(0.0f, 0.0f, 1.0f, 1.0f), // Blue
                v4(1.0f, 0.5f, 0.5f, 1.0f), // Pink
                v4(1.0f, 0.5f, 0.0f, 1.0f), // Orange
                v4(0.5f, 0.5f, 1.0f, 1.0f), // Purple
                v4(1.0f, 1.0f, 1.0f, 1.0f), // White
                v4(1.0f, 0.0f, 0.0f, 1.0f), // Red
                v4(0.0f, 1.0f, 1.0f, 1.0f), // Cyan
                v4(0.0f, 1.0f, 0.0f, 1.0f), // Green
                v4(1.0f, 1.0f, 0.0f, 1.0f), // Yellow
                v4(1.0f, 0.0f, 1.0f, 1.0f), // Magenta
                v4(0.0f, 0.0f, 1.0f, 1.0f), // Blue
                v4(1.0f, 0.5f, 0.5f, 1.0f), // Pink
                v4(1.0f, 0.5f, 0.0f, 1.0f), // Orange
                v4(0.5f, 0.5f, 1.0f, 1.0f)  // Purple
            };
    };

    const Indices octantWireframeBase = {
        // Bottom
        BottomBackLeft, /*  */ BottomFrontLeft,  //
        BottomFrontLeft, /* */ BottomFrontRight, //
        BottomFrontRight, /**/ BottomBackRight,  //
        BottomBackRight, /* */ BottomBackLeft,   //

        // Top
        TopBackLeft, /*     */ TopFrontLeft,  //
        TopFrontLeft, /*    */ TopFrontRight, //
        TopFrontRight, /*   */ TopBackRight,  //
        TopBackRight, /*    */ TopBackLeft,   //

        // Left
        BottomBackLeft, /*  */ TopBackLeft,     //
        TopBackLeft, /*     */ TopFrontLeft,    //
        TopFrontLeft, /*    */ BottomFrontLeft, //
        BottomFrontLeft, /* */ BottomBackLeft,  //

        // Right
        BottomBackRight, /* */ TopBackRight,     //
        TopBackRight, /*    */ TopFrontRight,    //
        TopFrontRight, /*   */ BottomFrontRight, //
        BottomFrontRight, /**/ BottomBackRight,  //
    };
} // namespace OctreeVisualizationDefinition

#endif // !OctreeVisualization_HPP