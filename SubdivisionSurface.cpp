#include "SubdivisionSurface.hpp"

using namespace Subdivision;

/**
 * @brief Performs simple 4:1 subdivision of the mesh.
 *  - Creates new vertices at the midpoints of each edge.
 *  - Creates 3 new triangles, using one old vertex and two midpoints.
 *  - Replaces the original triangles with triangles created from the midpoints.
 *  - Removes the edges and connects the old vertices to the midpoints.
 *  - Assigns the new Triangles and Edges to every vertex.
 *
 */
void SubdivisionSurface::simpleSubdivision4to1()
{
    // Clear edges and triangles of each vertex
    for (KeyData vertexID = 0; vertexID < vertices.size(); vertexID++)
    {
        edges[vertexID].vertexEdges.clear();
        vertices[vertexID].triangleIDs.clear();
    }

    int vertexOffset = (int) vertices.size();    // Offset to where new vertices are placed in the vertices vector.
    int vertexIndex = vertexOffset;        // Index for new vertices.
    int triangleOffset = (int) triangles.size(); // Offset to where new triangles are placed in the triangles vector.
    int triangleIndex = triangleOffset;    // Index for new triangles.
    unordered_map<v3, int> midpointMap;    // Map of midpoints to their index in the vertices vector.

    // For every original triangle in the mesh
    for (TriangleID tri = 0; tri < triangleOffset; tri++)
    {
        // Get the midpoints of the edges of the triangle
        vector<v3> triangleMidpoints = {
            getEdgeMidpoint(triangles[tri][0], triangles[tri][1]),
            getEdgeMidpoint(triangles[tri][1], triangles[tri][2]),
            getEdgeMidpoint(triangles[tri][2], triangles[tri][0])};

        KeyList vKeys(3);

        // For every midpoint of the triangle's edges
        // Fill out vKeys
        for (int i = 0; i < 3; i++)
        {
            // If the midpoint of the edge has not been created yet...
            // This is to avoid creating duplicate midpoints
            if (midpointMap.find(triangleMidpoints[i]) == midpointMap.end())
            {
                vKeys.emplace_back(vertexIndex);                 // Set the key to the current index
                midpointMap[triangleMidpoints[i]] = vertexIndex; // Add the vertex vector (key) and key (value) to the map

                edges.emplace_back(Edge()); // Add new Edge object to the edges vector

                V3D vert = triangleMidpoints[i]; // Create V3D object for vertex
                vertices.emplace_back(vert);     // Add the vertex to the vertices array
                vertexIndex++;                   // Increment index
            }
            // Otherwise set the midpoint's key to the existing value
            else
            {
                vKeys.emplace_back(midpointMap[triangleMidpoints[i]]);
            }
        }

        for (int i = 0; i < 3; i++)
        {
            KeyData vertexID = vKeys[i];
            int stepAhead = (i + 1) % 3;

            // Connect Edges for midpoint
            edges[vertexID].vertexEdges.emplace_back(triangles[tri][i]);         // Add first vertex edge
            edges[vertexID].vertexEdges.emplace_back(triangles[tri][stepAhead]); // Add second vertex edge
            edges[triangles[tri][i]].vertexEdges.emplace_back(vertexID);         // Add the new vertex to the first vertex's edge
            edges[triangles[tri][stepAhead]].vertexEdges.emplace_back(vertexID); // Add the new vertex to the second vertex's edge

            /**
             *   Creating new triangles
             *
             *        v0
             *        /\
             *   mp0 /__\ mp2
             *      /\  /\
             *     /__\/__\
             *   v1   mp1  v2
             *
             *  v_ = original vertex
             *  mp_ = midpoint
             *
             *   New Triangles are:
             *       <v0,  mp0, mp2>
             *       <v1,  mp1, mp0>
             *       <v2,  mp2, mp1>
             *       <mp0, mp1, mp2> // This replaces the original triangle
             */

            IndexedTriangle newTriangle;
            newTriangle[0] = triangles[tri][i];
            newTriangle[1] = vKeys[i];
            newTriangle[2] = vKeys[stepAhead];

            // Add triangle to vertices
            vertices[newTriangle[0]].triangleIDs.emplace_back(triangleIndex);
            vertices[newTriangle[1]].triangleIDs.emplace_back(triangleIndex);
            vertices[newTriangle[2]].triangleIDs.emplace_back(triangleIndex);

            triangles.emplace_back(newTriangle); // Add new triangle to the triangles vector
            triangleIndex++;
        }

        // Replace the original triangle with the middle triangle
        triangles[tri][0] = vKeys[0];
        triangles[tri][1] = vKeys[1];
        triangles[tri][2] = vKeys[2];

        // Add middle triangle to vertices
        vertices[vKeys[0]].triangleIDs.emplace_back(tri);
        vertices[vKeys[1]].triangleIDs.emplace_back(tri);
        vertices[vKeys[2]].triangleIDs.emplace_back(tri);

        // Add edges between midpoints
        edges[vKeys[0]].vertexEdges.emplace_back(vKeys[1]);
        edges[vKeys[0]].vertexEdges.emplace_back(vKeys[2]);
        edges[vKeys[1]].vertexEdges.emplace_back(vKeys[0]);
        edges[vKeys[1]].vertexEdges.emplace_back(vKeys[2]);
        edges[vKeys[2]].vertexEdges.emplace_back(vKeys[0]);
        edges[vKeys[2]].vertexEdges.emplace_back(vKeys[1]);
    }

    rebuildOctree();
    refresh();
}

v3 SubdivisionSurface::getEdgeMidpoint(KeyData v1, KeyData v2)
{
    return (vertices[v1].position + vertices[v2].position) / 2.0f;
}

void SubdivisionSurface::loopSubdivision()
{
}

void SubdivisionSurface::subdivisionTest(){
    simpleSubdivision4to1();
        octreePrintStats();
}