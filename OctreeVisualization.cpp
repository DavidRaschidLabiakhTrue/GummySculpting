#include "OctreeVisualization.hpp"

using namespace OctreeVisualizationDefinition;

void OctreeVisualization::visualizeOctree(DepthColorMode depthColorMode)
{
    this->depthColorMode = depthColorMode;

    octreeWireframe.shouldDraw = true;
    octreeWireframe.octreeVertices.clear();
    octreeWireframe.octreeIndices.clear();

    octreeWireframe.octreeVertices.reserve(octants.size() * 8);    // Every octant has 8 vertices
    octreeWireframe.octreeIndices.reserve(octants.size() * 8 * 2); // Every vertex is repeated twice

    foreach (octant, octants)
    {
        generateOctantWireframe(octant.octantIndex);
    }
    colorTrianglePerOctant();
	refreshOctreeWireFrame();
	refresh();
}

void OctreeVisualization::generateOctantWireframe(OctantIndex octantID)
{
    OctantReference octant = octants[octantID];

    if ((octant.triangleIDs->size() == 0 && (drawMode == LeafOctants || drawMode == IntersectedLeafOctants)) ||
        (!octant.intersected && (drawMode == IntersectedLeafOctants || drawMode == AllIntersectedOctants)))
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

	refreshOctreeWireFrame();
}

void OctreeVisualizationDefinition::OctreeVisualization::refreshOctreeWireFrame()
{
	glBindVertexArray(gboOctreeWireframe.vao);

	// binding vertices
	glBindBuffer(GL_ARRAY_BUFFER, gboOctreeWireframe.vbo);
	glBufferData(GL_ARRAY_BUFFER, octreeWireframe.octreeVertices.size() * sizeof(V3D), octreeWireframe.octreeVertices.data(), GL_STATIC_DRAW);

	// binding indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gboOctreeWireframe.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, octreeWireframe.octreeIndices.size() * sizeof(KeyData), static_cast<void*>(octreeWireframe.octreeIndices.data()), GL_STATIC_DRAW);

	// enable position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)0);
	// enable color data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, OpenGLVertexAttributes::SizeOfVertex, (void*)offsetof(V3D, V3D::color)); // color data reserves 4 slots.
}

void OctreeVisualization::drawOctreeWireframe()
{
    if (octreeWireframe.shouldDraw)
    {
        GridShader.use(); // want it independent of wireframe
        gboOctreeWireframe.bindVAO();
        glDrawElements(GL_LINES, (GLsizei)octreeWireframe.octreeIndices.size(), GL_UNSIGNED_INT, NULL);
        unbindActiveVAO();
    }
}

random_device rd;
mt19937 e2(rd());
normal_distribution<> dist(50, 100);

void OctreeVisualization::colorTrianglePerOctant()
{
    v4 black(0.0f, 0.0f, 0.0f, 1.0f);
    colorDataUniformly(black);

    foreach (octant, octants)
    {
        v4 color = v4((float)dist(e2) / 100.0f,
                      (float)dist(e2) / 100.0f,
                      (float)dist(e2) / 100.0f,
                      1.0f);
        foreach (triangle, *(octant.triangleIDs))
        {
            for (int i = 0; i < 3; i++)
            {
                RV3D vertex = vertices[triangles[triangle][i]];

                if (vertex.color == black)
                {
                    vertex.color = color;
                }
                else
                {
                    vertex.color = 0.5f * (vertex.color + color);
                }
            }
        }
    }
}