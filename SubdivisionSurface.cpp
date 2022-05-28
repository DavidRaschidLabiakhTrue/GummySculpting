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
void SubdivisionSurface::simpleSubdivision4to1(int level, bool octreeRebuild, bool refreshDisplay) SUBNOEXCEPT
{
    // Loops for number of levels to subdivide
    for (int levelCounter = 0; levelCounter < level; levelCounter++)
    {
        vertexOffset = (int)vertices.size(); // Offset to where new vertices are placed in the vertices vector.
        int vertexIndex = vertexOffset;      // Index for new vertices.
        const int trianglesSize = (int)triangles.size();

        IndexedTriangles oldTriangles = triangles;
        Edges oldEdges = edges;
        vertexOffsets.emplace_back(vertexIndex);
        triangleLists.emplace_back(oldTriangles);
        edgeLists.emplace_back(oldEdges);

        // int triangleOffset = (int)triangles.size(); // Offset to where new triangles are placed in the triangles vector.
        // int triangleIndex = triangleOffset;         // Index for new triangles.
        unordered_map<v3, KeyData> midpointMap; // Map of midpoints to their index in the vertices vector.
        vector<KeyList> triangleMidpointMap;

        // Fill midpoint map with all midpoints
        // Parallelizable
        for (KeyData vertexID = 0; vertexID < vertexOffset; vertexID++)
        {
            foreach (otherVertexID, edges[vertexID].vertexEdges)
            {
                if (vertexID < otherVertexID)
                {
                    v3 midpoint = (vertices[vertexID].position + vertices[otherVertexID].position) * 0.5f;
                    V3D newVert = midpoint;
                    newVert.color = (vertices[vertexID].color + vertices[otherVertexID].color) * 0.5f;
                    vertices.emplace_back(newVert);
                    midpointMap.emplace(midpoint, vertexIndex);
                    vertexIndex++;
                }
            }
        }

        // Clear edges, triangles, ABCD of each vertex
        // Easily Parallelizable
        for (int vertexID = 0; vertexID < vertexOffset; vertexID++)
        {
            edges[vertexID].vertexEdges.clear();
            vertices[vertexID].triangleIDs.clear();
            vertices[vertexID].ABCD.clear();
        }

        // Fill triangle midpoint map with all triangle midpoints
        // Parallelizable
        for (TriangleID tri = 0; tri < trianglesSize; tri++)
        {
            KeyList midpointIDs = {
                midpointMap[getEdgeMidpoint(triangles[tri][0], triangles[tri][1])],
                midpointMap[getEdgeMidpoint(triangles[tri][1], triangles[tri][2])],
                midpointMap[getEdgeMidpoint(triangles[tri][2], triangles[tri][0])]};
            triangleMidpointMap.push_back(midpointIDs);
        }

        int triangleIndex = 0;
        IndexedTriangles newTriangles;
        for (TriangleID tri = 0; tri < trianglesSize; tri++)
        {
            KeyList midpoints = triangleMidpointMap[tri];

            for (int i = 0; i < 3; i++)
            {
                IndexedTriangle newTriangle;
                newTriangle[0] = triangles[tri][i];
                newTriangle[1] = midpoints[i];
                newTriangle[2] = midpoints[(i + 2) % 3];
                vertices[newTriangle[0]].triangleIDs.emplace_back(triangleIndex);
                vertices[newTriangle[1]].triangleIDs.emplace_back(triangleIndex);
                vertices[newTriangle[2]].triangleIDs.emplace_back(triangleIndex);
                newTriangles.emplace_back(newTriangle);
                triangleIndex++;
            }

            IndexedTriangle midpointTriangle;
            midpointTriangle[0] = midpoints[0];
            midpointTriangle[1] = midpoints[1];
            midpointTriangle[2] = midpoints[2];
            vertices[midpointTriangle[0]].triangleIDs.emplace_back(triangleIndex);
            vertices[midpointTriangle[1]].triangleIDs.emplace_back(triangleIndex);
            vertices[midpointTriangle[2]].triangleIDs.emplace_back(triangleIndex);
            newTriangles.emplace_back(midpointTriangle);
            triangleIndex++;
        }

        for (TriangleID tri = 0; tri < trianglesSize; tri++)
        {
            IndexedTriangle triangle = triangles[tri];

            RV3D mp0 = vertices[triangleMidpointMap[tri][0]];
            RV3D mp1 = vertices[triangleMidpointMap[tri][1]];
            RV3D mp2 = vertices[triangleMidpointMap[tri][2]];

            mp0.ABCDmap.try_emplace('A', triangle[0]);
            mp0.ABCDmap.try_emplace('B', triangle[1]);
            if (!mp0.ABCDmap.try_emplace('C', triangle[2]).second)
            {
                mp0.ABCDmap.try_emplace('D', triangle[2]);
            }

            mp1.ABCDmap.try_emplace('A', triangle[1]);
            mp1.ABCDmap.try_emplace('B', triangle[2]);
            if (!mp1.ABCDmap.try_emplace('C', triangle[0]).second)
            {
                mp1.ABCDmap.try_emplace('D', triangle[0]);
            }

            mp2.ABCDmap.try_emplace('A', triangle[2]);
            mp2.ABCDmap.try_emplace('B', triangle[0]);
            if (!mp2.ABCDmap.try_emplace('C', triangle[1]).second)
            {
                mp2.ABCDmap.try_emplace('D', triangle[1]);
            }
        }

        triangles = newTriangles;
        generateEdges();
    }

    if (octreeRebuild)
    {
        // rebuildOctree();
        octreeReinsertTriangles();
    }
    if (refreshDisplay)
    {
        refresh();
    }
}

inline v3 SubdivisionSurface::getEdgeMidpoint(KeyData v1, KeyData v2) SUBNOEXCEPT
{
    return (vertices[v1].position + vertices[v2].position) * 0.5f;
}

// TODO: Need to adapt to include calculation for boundary vertices
// Currently Assumes that all vertices are interior
// Can Optimize with precomputed constants
void SubdivisionSurface::loopSubdivision(int level, bool rebuildRefresh) SUBNOEXCEPT
{
    for (int levelCounter = 0; levelCounter < level; levelCounter++)
    {
        simpleSubdivision4to1(1, false, false); // 4:1 subdivision. First step of loop subdivision
        Vertices newVertexList = vertices;      // New vertex list

        // Calculate new position for every original vertex before subdivision
        for (int vertexID = 0; vertexID < vertexOffset; vertexID++)
        {
            int k = (int)edges[vertexID].vertexEdges.size();     // Number of neighboring vertices
            float beta = getBeta(k);                             // Get Beta
            v3 ksum = sumNeighbors(edges[vertexID].vertexEdges); // Sum of neighboring vertices

            newVertexList[vertexID] = (vertices[vertexID].position * (1.0f - (k * beta))) + (ksum * beta);
        }

        // Calculate new position for every vertex that was created during subdivision
        int verticesSize = vertices.size();
        for (int vertexID = vertexOffset; vertexID < verticesSize; vertexID++)
        {
            // vector<int> ABCD = vertices[vertexID].ABCD;                    // Get the ABCD vector for the vertex
            unordered_map<char, int> ABCDmap = vertices[vertexID].ABCDmap; // Map of ABCD vector

            newVertexList[vertexID] = (0.375f * (vertices[ABCDmap['A']].position + vertices[ABCDmap['B']].position)) +
                                      (0.125f * (vertices[ABCDmap['C']].position + vertices[ABCDmap['D']].position));
        }

        // Calculate new position for every original vertex before subdivision
        // for (int vertexID = 0; vertexID < vertexOffset; vertexID++)
        // {
        //     int k = (int)edges[vertexID].vertexEdges.size();     // Number of neighboring vertices
        //     float beta = getBeta(k);                             // Get Beta
        //     v3 ksum = sumNeighbors(edges[vertexID].vertexEdges); // Sum of neighboring vertices
        //     newVertexList[vertexID] = (vertices[vertexID].position * (1.0f - (k * beta))) + (ksum * beta);
        //     Boundary/crease Condition
        //     if (isVertexOnCrease(vertexID))
        //     if(false)
        //     {
        //         vector<int> ABCD = vertices[vertexID].ABCD;
        //         newVertexList[vertexID] = (1.0f / 8.0f) * (vertices[ABCD[0]].position + vertices[ABCD[1]].position) +
        //                                   (3.0f / 4.0f) * vertices[vertexID].position;
        //     }
        //     else
        //     {
        //     newVertexList[vertexID] = (vertices[vertexID].position * (1.0f - (k * beta)) + (ksum * beta));
        //     }
        // }
        // Calculate new position for every vertex that was created during subdivision
        // for (KeyData vertexID = vertexOffset; vertexID < vertices.size(); vertexID++)
        // {
        //     vector<int> ABCD = vertices[vertexID].ABCD; // Get the ABCD vector for the vertex
        //     newVertexList[vertexID] = (0.375f * (vertices[ABCD[0]].position + vertices[ABCD[1]].position)) +
        //                               (0.125f * (vertices[ABCD[2]].position + vertices[ABCD[3]].position));
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
        // }

        vertices = newVertexList;
    }
    if (rebuildRefresh)
    {
        // rebuildOctree();
        octreeReinsertTriangles();
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

float SubdivisionSurface::getBeta(int nEdges) SUBNOEXCEPT
{
    float n = (float)nEdges;
    // nEdges = 1;
    if (nEdges == 3)
    {
        return 0.375f; // 3.0f / 8.0f; should be 3/16
        // return 3.0f/16.0f;
    }
    else if (nEdges > 3)
    {
        return 0.75f * (1.0f / n); // 3.0f / (4.0f * n); should be 3/(8n)
        // return 3.0f/(8.0f*n);
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

v3 SubdivisionSurface::sumNeighbors(unordered_set<KeyData> neighbors) SUBNOEXCEPT
{
    v3 sum = v3(0);
    for (KeyData neighbor : neighbors)
    {
        sum += vertices[neighbor].position;
    }
    return sum;
}

void SubdivisionSurface::subdivisionTest() SUBNOEXCEPT
{
    loopSubdivision(2);
    octreePrintStats();
}

void SubdivisionSurface::gotoSubdivisionLevel(int subdLevel) SUBNOEXCEPT
{
    if (subdLevel > currentSubdivisionLevel)
    {
        loopSubdivision(subdLevel - currentSubdivisionLevel);
    }
    else if (subdLevel < currentSubdivisionLevel)
    {
        vertices.erase(vertices.begin() + vertexOffsets[subdLevel], vertices.end());
        edges = edgeLists[subdLevel];
        edgeLists.erase(edgeLists.begin() + subdLevel + 1, edgeLists.end());
        triangles = triangleLists[subdLevel];
        triangleLists.erase(triangleLists.begin() + subdLevel + 1, triangleLists.end());
        rebuildOctree();
        refresh();
    }

    currentSubdivisionLevel = subdLevel;
}