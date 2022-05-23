#include "OctreeVisualization.hpp"

using namespace OctreeVisualizationDefinition;

void OctreeVisualization::generateOctreeVisualization(DrawMode drawMode, DepthColorMode depthColorMode)
{
    this->drawMode = drawMode;
    this->depthColorMode = depthColorMode;
    octreeWireframe.octreeVertices.clear();
    octreeWireframe.octreeIndices.clear();

    octreeWireframe.octreeVertices.reserve(octants.size() * 8);    // Every octant has 8 vertices
    octreeWireframe.octreeIndices.reserve(octants.size() * 8 * 2); // Every vertex is repeated twice

    foreach (octant, octants)
    {
        generateOCtantWireframe(octant.octantIndex);
    }
}

void OctreeVisualization::generateOCtantWireframe(OctantIndex octantID)
{
    Octant octant = octants[octantID];
    if (drawMode == LeafOctants && octant.triangleIDs.size() == 0)
    {
        return;
    }
    int currentIndex = (int)octreeWireframe.octreeVertices.size();

    OctantIndex curr = octantID;
    int octantDepth = 0;
    while (curr != root)
    {
        curr = octants[curr].parent;
        octantDepth++;
    }

    for (int i = 0; i < 8; i++)
    {
        V3D vertex = V3D(octant.octantCenter + octant.octantHalfSize * octantPositionVectors[(OctantPosition)i]);
        if (depthColorMode == EnableDepthColor)
        {
            vertex.color = DepthColors[(DepthColor)octantDepth];
        }
        octreeWireframe.octreeVertices.emplace_back(vertex);
    }

    Indices octantWireframe = octantWireframeBase;

    foreach (index, octantWireframe)
    {
        octreeWireframe.octreeIndices.emplace_back(currentIndex + index);
    }
}

void OctreeVisualization::bindOctreeWireframe()
{
    glGenVertexArrays(1, &gboOctreeWireframe.vao);
    glGenBuffers(1, &gboOctreeWireframe.vbo);
    glGenBuffers(1, &gboOctreeWireframe.ebo);

    glBindVertexArray(gboOctreeWireframe.vao);

    // binding vertices
    glBindBuffer(GL_ARRAY_BUFFER, gboOctreeWireframe.vbo);
    glBufferData(GL_ARRAY_BUFFER, octreeWireframe.octreeVertices.size() * sizeof(V3D), octreeWireframe.octreeVertices.data(), GL_STATIC_DRAW);

    // binding indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gboOctreeWireframe.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, octreeWireframe.octreeIndices.size() * sizeof(KeyData), static_cast<void *>(octreeWireframe.octreeIndices.data()), GL_STATIC_DRAW);

    // enable position data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void *)0);
    // enable color data
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void *)offsetof(V3D, V3D::color)); // color data reserves 4 slots.
}

void OctreeVisualization::drawOctreeWireframe()
{
    if (octreeWireframe.shouldDraw)
    {
        bindOctreeWireframe();
        StandardShader.use();
        gboOctreeWireframe.bindVAO();
        glDrawElements(GL_LINES, (GLsizei)octreeWireframe.octreeIndices.size(), GL_UNSIGNED_INT, NULL);
        unbindActiveVAO();
    }
}