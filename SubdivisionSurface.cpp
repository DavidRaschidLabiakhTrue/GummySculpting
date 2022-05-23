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
int SubdivisionSurface::simpleSubdivision4to1(int level, bool rebuildRefresh)
{
    // Loops for number of levels to subdivide
    for (int levelCounter = 0; levelCounter < level; levelCounter++)
    {
        // Clear edges and triangles of each vertex
        for (KeyData vertexID = 0; vertexID < vertices.size(); vertexID++)
        {
            edges[vertexID].vertexEdges.clear();
            vertices[vertexID].triangleIDs.clear();
            vertices[vertexID].ABCD.clear();
        }

        vertexOffset = (int)vertices.size();        // Offset to where new vertices are placed in the vertices vector.
        int vertexIndex = vertexOffset;             // Index for new vertices.
        int triangleOffset = (int)triangles.size(); // Offset to where new triangles are placed in the triangles vector.
        int triangleIndex = triangleOffset;         // Index for new triangles.
        unordered_map<v3, int> midpointMap;         // Map of midpoints to their index in the vertices vector.

        // For every original triangle in the mesh
        for (TriangleID tri = 0; tri < triangleOffset; tri++)
        {
            // Get the midpoints of the edges of the triangle
            vector<v3> triangleMidpoints = {
                getEdgeMidpoint(triangles[tri][0], triangles[tri][1]),
                getEdgeMidpoint(triangles[tri][1], triangles[tri][2]),
                getEdgeMidpoint(triangles[tri][2], triangles[tri][0])};

            KeyList vKeys;

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

                    // Add the original vertices of the triangle to the ABCD vector for loop subdivision
                    // The first two (A, B) are the original vertices of the edge
                    // The third is the opposing vertex of the triangles from the edge
                    vert.ABCD.emplace_back(triangles[tri][i]);
                    vert.ABCD.emplace_back(triangles[tri][(i + 1) % 3]);
                    vert.ABCD.emplace_back(triangles[tri][(i + 2) % 3]);

                    vertices.emplace_back(vert); // Add the vertex to the vertices array
                    vertexIndex++;               // Increment index
                }
                // Otherwise set the midpoint's key to the existing value
                else
                {
                    KeyData vertexID = midpointMap[triangleMidpoints[i]];              // VertexID of the midpoint
                    vKeys.emplace_back(vertexID);                                      // Set the key to the existing vertexID
                    vertices[vertexID].ABCD.emplace_back(triangles[tri][(i + 2) % 3]); // Add the edge's other triangle's opposing vertex (D) to the ABCD vector
                }
            }

            for (int i = 0; i < 3; i++)
            {
                KeyData vertexID = vKeys[i];
                int oneStepAhead = (i + 1) % 3;
                int twoStepsAhead = (i + 2) % 3; // Two steps ahead, see triangle diagram

                // Connect Edges for midpoint
                edges[vertexID].vertexEdges.insert(triangles[tri][i]);            // Add first vertex edge
                edges[vertexID].vertexEdges.insert(triangles[tri][oneStepAhead]); // Add second vertex edge
                edges[triangles[tri][i]].vertexEdges.insert(vertexID);            // Add the new vertex to the first vertex's edge
                edges[triangles[tri][oneStepAhead]].vertexEdges.insert(vertexID); // Add the new vertex to the second vertex's edge

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
                newTriangle[2] = vKeys[twoStepsAhead];

                // Add triangle to vertices
                vertices[newTriangle[0]].triangleIDs.emplace_back(triangleIndex);
                vertices[newTriangle[1]].triangleIDs.emplace_back(triangleIndex);
                vertices[newTriangle[2]].triangleIDs.emplace_back(triangleIndex);

                // newTriangles.emplace_back(newTriangle); // Add new triangle to the triangles vector
                triangles.emplace_back(newTriangle); // Add new triangle to the triangles vector
                triangleIndex++;
            }

            // Add middle triangle to vertices
            vertices[vKeys[0]].triangleIDs.emplace_back(triangleIndex);
            vertices[vKeys[1]].triangleIDs.emplace_back(triangleIndex);
            vertices[vKeys[2]].triangleIDs.emplace_back(triangleIndex);

            // Add edges between midpoints
            edges[vKeys[0]].vertexEdges.insert(vKeys[1]);
            edges[vKeys[0]].vertexEdges.insert(vKeys[2]);
            edges[vKeys[1]].vertexEdges.insert(vKeys[0]);
            edges[vKeys[1]].vertexEdges.insert(vKeys[2]);
            edges[vKeys[2]].vertexEdges.insert(vKeys[0]);
            edges[vKeys[2]].vertexEdges.insert(vKeys[1]);

            // Replace the original triangle with the middle triangle
            triangles[tri][0] = vKeys[0];
            triangles[tri][1] = vKeys[1];
            triangles[tri][2] = vKeys[2];
        }
    }

    if (rebuildRefresh)
    {
        rebuildOctree();
        refresh();
    }
    return vertexOffset;
}

inline v3 SubdivisionSurface::getEdgeMidpoint(KeyData v1, KeyData v2)
{
    return (vertices[v1].position + vertices[v2].position) * 0.5f;
}

// TODO: Need to adapt to include calculation for boundary vertices
// Currently Assumes that all vertices are interior
// Can Optimize with precomputed constants
void SubdivisionSurface::loopSubdivision(int level, bool rebuildRefresh)
{
    for (int levelCounter = 0; levelCounter < level; levelCounter++)
    {
        simpleSubdivision4to1(1, false);   // 4:1 subdivision. First step of loop subdivision
        Vertices newVertexList = vertices; // New vertex list

        // Calculate new position for every original vertex before subdivision
        for (int vertexID = 0; vertexID < vertexOffset; vertexID++)
        {
            int k = (int)edges[vertexID].vertexEdges.size();     // Number of neighboring vertices
            float beta = getBeta(k);                             // Get Beta
            v3 ksum = sumNeighbors(edges[vertexID].vertexEdges); // Sum of neighboring vertices

            newVertexList[vertexID] = (vertices[vertexID].position * (1.0f - (k * beta))) + (ksum * beta);

            // Boundary/crease Condition
            // if (isVertexOnCrease(vertexID))
            // if(false)
            // {
            //     vector<int> ABCD = vertices[vertexID].ABCD;
            //     newVertexList[vertexID] = (1.0f / 8.0f) * (vertices[ABCD[0]].position + vertices[ABCD[1]].position) +
            //                               (3.0f / 4.0f) * vertices[vertexID].position;
            // }
            // else
            // {
            // newVertexList[vertexID] = (vertices[vertexID].position * (1.0f - (k * beta)) + (ksum * beta));
            // }
        }

        // Calculate new position for every vertex that was created during subdivision
        for (KeyData vertexID = vertexOffset; vertexID < vertices.size(); vertexID++)
        {
            vector<int> ABCD = vertices[vertexID].ABCD; // Get the ABCD vector for the vertex

            newVertexList[vertexID] = (0.375f * (vertices[ABCD[0]].position + vertices[ABCD[1]].position)) +
                                      (0.125f * (vertices[ABCD[2]].position + vertices[ABCD[3]].position));

            // Boundary/crease Condition
            // if (isVertexOnCrease(vertexID))
            // if(false)
            // {
            //     newVertexList[vertexID] = 0.5f * (vertices[ABCD[0]].position + vertices[ABCD[1]].position);
            // }
            // // Interior Condition
            // else
            // {
            // newVertexList[vertexID] = (3.0f / 8.0f) * (vertices[ABCD[0]].position + vertices[ABCD[1]].position) +
            //                           (1.0f / 8.0f) * (vertices[ABCD[2]].position + vertices[ABCD[3]].position);
            // }
        }

        vertices = newVertexList;
    }
    if (rebuildRefresh)
    {
        rebuildOctree();
        refresh();
    }
}

// Ignore for now

// bool SubdivisionSurface::isVertexOnCrease(KeyData vertexID)
// {
//     V3D vertex = vertices[vertexID];
//     // Differentiate between new and old vertices
//     if ((int)vertexID > vertexOffset) // New Vertex
//     {
//         return getCreaseAngleOfNewVertex(vertexID) <= angleLimit; // Return true if angle is less than the limit
//     }
//     else // Old Vertex
//     {
//         int count = 0;
//         unordered_map<int, float> creaseAngles;
//         creaseAngles[0] = InfiniteCreaseAngle;
//         creaseAngles[1] = InfiniteCreaseAngle;
//         vertices[vertexID].ABCD.push_back(0); // Add a dummy value to the ABCD vector
//         vertices[vertexID].ABCD.push_back(0); // Add a dummy value to the ABCD vector
//         // Check the surrounding vertices, which are all new vertices
//         foreach (otherVertexID, edges[vertexID].vertexEdges)
//         {
//             float neighborCreaseAngle = getCreaseAngleOfNewVertex(otherVertexID);
//             // Record neighboring vertices are on a crease
//             if (neighborCreaseAngle <= angleLimit)
//             {
//                 vertices[vertexID].ABCD.push_back(otherVertexID);
//                 // Replace values if the angle is less than the previous one
//                 // if (neighborCreaseAngle < creaseAngles[0])
//                 // {
//                 //     creaseAngles[0] = neighborCreaseAngle;
//                 //     vertices[vertexID].ABCD[0] = otherVertexID;
//                 // }
//                 // else if (neighborCreaseAngle < creaseAngles[1])
//                 // {
//                 //     creaseAngles[1] = neighborCreaseAngle;
//                 //     vertices[vertexID].ABCD[1] = otherVertexID;
//                 // }
//                 count++;
//             }
//         }
//         if (count < 2)
//         {
//             vertices[vertexID].ABCD.clear();
//             return false;
//         }
//         return true; // Return true if there are at least 2 neighboring vertices on a crease
//     }
// }

// float SubdivisionSurface::getCreaseAngleOfNewVertex(KeyData vertexID)
// {
//     V3D vertex = vertices[vertexID];
//     if (vertex.ABCD.size() == 4)
//     {
//         return abs(angle(vertices[vertex.ABCD[2]].position - vertex.position,
//                          vertices[vertex.ABCD[3]].position - vertex.position));
//     }
//     else
//     {
//         return 0.0f;
//     }
// }

float SubdivisionSurface::getBeta(int nEdges)
{
    float n = (float)nEdges;
    // nEdges = 1;
    if (nEdges == 3)
    {
        return 0.375f; // 3.0f / 8.0f; should be 3/16
    }
    else if (nEdges > 3)
    {
        return 0.75f * (1.0f / n); // 3.0f / (4.0f * n); should be 3/(8n)
    }
    else
    {
        // Original loop equation for beta with modifier
        // Shouldn't be unused, only here as backup for borderline cases for now
        // float temp = (3.0f / 8.0f) + (1.0f / 4.0f) * cos(TWO_PI / nEdges);
        // return (1.0f / nEdges) * ((5.0f / 8.0f) - temp * temp);
        float temp = 0.375f + (0.25f * cos(TWO_PI / nEdges));
        return (1.0f / n) * (0.625f - (temp * temp));
    }
}

v3 SubdivisionSurface::sumNeighbors(unordered_set<KeyData> neighbors)
{
    v3 sum = v3(0);
    for (KeyData neighbor : neighbors)
    {
        sum += vertices[neighbor].position;
    }
    return sum;
}

void SubdivisionSurface::subdivisionTest()
{
    loopSubdivision(2);
    octreePrintStats();
}