#include "Decimation.hpp"

using namespace _Decimation;

void Decimation::decimateMesh(float percentage) DECNOEXCEPT
{
    EdgePQ edgePQ = parameterizeEdges();
    set<KeyData, greater<KeyData>> vertexSet;
    set<KeyData, greater<KeyData>> visitedVertices;
    int cullTarget = (int)(triangles.size() * percentage);
    int numCulled = 0;

    while (numCulled < cullTarget)
    {
        EdgeDistPair edgeDistPair = edgePQ.top();
        edgePQ.pop();
        EdgePair edge = edgeDistPair.second;

        if (edge.first >= vertices.size() || edge.first < 0 ||
            edge.second >= vertices.size() || edge.second < 0 ||
            !edges[edge.first].vertexEdges.contains(edge.second) ||
            !edges[edge.second].vertexEdges.contains(edge.first))
        {
            continue;
        }

        // Verify edge, push if distance is different
        float dist = glm::distance(vertices[edge.first].position, vertices[edge.second].position);
        if (dist != edgeDistPair.first)
        {
            edgePQ.push(EdgeDistPair(dist, edge));
            continue;
        }

        collapseEdge(edge);
        numCulled += 2;
    }

    say "Verifying after decimation";
    verifyMesh();
}

struct pair_hash
{
        inline std::size_t operator()(const std::pair<int, int> &v) const
        {
            return v.first * 31 + v.second;
        }
};

void Decimation::verifyMesh()
{
    int numTriangles = triangles.size();
    int numVertices = vertices.size();

    int badTriangles = 0;
    int badVertices = 0;
    int badEdges = 0;
    int badOctants = 0;
    int badConnections = 0;

    // Check for bad triangles
    int trix = 0;
    foreach (tri, triangles)
    {
        // Check for bad vertex indices
        if (tri[0] >= numVertices || tri[1] >= numVertices || tri[2] >= numVertices ||
            tri[0] < 0 || tri[1] < 0 || tri[2] < 0)
        {
            badTriangles++;
            trix++;
            continue;
        }

        v3 triNormal = getTriangleNormal(trix);

        if (isnan(triNormal.x) || isnan(-triNormal.x) ||
            isnan(triNormal.y) || isnan(-triNormal.y) ||
            isnan(triNormal.z) || isnan(-triNormal.z))
        {
            say "NAN triangle normal found" done;
            break;
        }

        // check if vertex contains the triangle
        for (int i = 0; i < 3; i++)
        {
            if (!vertices[tri[i]].triangleIDs.contains(trix))
            {
                // badConnections++;
                break;
            }

            if (vertices[tri[i]].position == vertices[tri[(i + 1) % 3]].position ||
                vertices[tri[i]].position == vertices[tri[(i + 2) % 3]].position)
            {
                badVertices++;
                break;
            }
        }

        // check if octant contains the triangle
        if (!octants[triangleToOctantList[trix]].triangleIDs->contains(trix))
        {
            badOctants++;
        }

        trix++;
    }

    // Check for bad vertices
    int emptyVertexTriangleList = 0;
    int vertexID = 0;
    foreach (vertex, vertices)
    {
        // check for empty triangle list
        if (vertex.triangleIDs.size() == 0)
        {
            emptyVertexTriangleList++;
        }

        // check for bad positions
        if (isnan(vertex.position.x) || isnan(-vertex.position.x) || isnan(vertex.position.y) || isnan(-vertex.position.y) || isnan(vertex.position.z) || isnan(-vertex.position.z))
        {
            say "NAN vertex found" done;
        }
        if (isinf(vertex.position.x) || isinf(-vertex.position.x) ||
            isinf(vertex.position.y) || isinf(-vertex.position.y) ||
            isinf(vertex.position.z) || isinf(-vertex.position.z))
        {
            say "inf vertex found" done;
        }

        unordered_set<pair<int, int>, pair_hash> triangleSet;

        foreach (triD, vertex.triangleIDs)
        {
            // check bad triangle indices
            if (triD >= numTriangles || triD < 0)
            {
                // badConnections++;
                continue;
            }

            // check if triangle contains vertex
            KeyData otherV1;
            KeyData otherV2;
            if (triangles[triD][0] == vertexID)
            {
                otherV1 = triangles[triD][1];
                otherV2 = triangles[triD][2];
            }
            else if (triangles[triD][1] == vertexID)
            {
                otherV1 = triangles[triD][0];
                otherV2 = triangles[triD][2];
            }
            else if (triangles[triD][2] == vertexID)
            {
                otherV1 = triangles[triD][0];
                otherV2 = triangles[triD][1];
            }
            else
            {
                badConnections++;
                continue;
            }

            // check if vertex edges contain the other vertices in triangle
            if (!edges[vertexID].vertexEdges.contains(otherV1) || !edges[vertexID].vertexEdges.contains(otherV2))
            {
                badConnections++;
            }

            pair<KeyData, KeyData> triPair = make_pair(glm::min(otherV1, otherV2), glm::max(otherV1, otherV2));
            if (triangleSet.contains(triPair))
            {
                say "Duplicate triangle found" done;
            }
            else
            {
                triangleSet.insert(triPair);
            }
        }

        vertexID++;
    }

    // Edges
    int eix = 0;
    foreach (edgeList, edges)
    {
        // check for empty edge list
        if (edgeList.vertexEdges.size() == 0)
        {
            badEdges++;
        }

        // check for bad vertex indices
        foreach (otherVertex, edgeList.vertexEdges)
        {
            if (otherVertex >= numVertices || otherVertex < 0)
            {
                badEdges++;
            }

            if (!edges[otherVertex].vertexEdges.contains(eix))
            {
                badEdges++;
            }

            if (glm::epsilonEqual(distance(vertices[eix].position, vertices[otherVertex].position), 0.0f, 0.00001f))
            {
                say "degenerate triangle found" done;
                badEdges++;
            }
        }

        eix++;
    }

    // octants
    int oix = 0;
    foreach (octant, octants)
    {
        foreach (tri, *(octant.triangleIDs))
        {
            // check for bad triangle indices
            if (tri >= numTriangles || tri < 0)
            {
                badOctants++;
            }

            // check connection of triangle to octant
            if (triangleToOctantList[tri] != oix)
            {
                // badConnections++;
            }
        }

        oix++;
    }

    if (badTriangles || badVertices || badEdges || badOctants || badConnections || emptyVertexTriangleList)
    {

        say "Bad triangles: " << badTriangles done;
        say "Bad vertices: " << badVertices done;
        say "Bad edges: " << badEdges done;
        say "Bad octants: " << badOctants done;
        say "Bad connections: " << badConnections done;
        say "Empty vertex triangle list: " << emptyVertexTriangleList done;
        say "-----------------------------------------------------" done;
    }
}

EdgePQ Decimation::parameterizeEdges() DECNOEXCEPT
{
    EdgePQ pq;

    int numverts = vertices.size();
    for (int vertexID = 0; vertexID < numverts; vertexID++)
    {
        foreach (otherVertexID, edges[vertexID].vertexEdges)
        {
            // Avoid recreating the same edge
            if (otherVertexID < vertexID)
            {
                continue;
            }

            pq.push(make_pair(glm::distance(vertices[vertexID].position, vertices[otherVertexID].position),
                              make_pair(vertexID, otherVertexID)));
        }
    }

    return pq;
}

/**
 * @brief Collapse an edge by:
 *          1. disconnecting the triangles which share the edge,
 *          2. connecting the triangles and edges of the second vertex to the first vertex
 *          3. disconnecting the second vertex
 *
 * NOTE: This function does not update the vertices list or triangles list;
 * Instead, it creates degenerate triangles in place.
 *
 * NOTE: This function performs no safety checks.
 *
 * @param edge
 */
void Decimation::collapseEdge(EdgePair edge) DECNOEXCEPT
{
    // Get Triangles that share this edge
    KeyList sharedTriangles = getEdgeTriangles(edge);
    removeTriangles(sharedTriangles);

    vertices[edge.first] = getEdgeMidpoint(edge.first, edge.second);                                // Move v1 to the midpoint of the edge
    vertices[edge.first].color = (vertices[edge.first].color + vertices[edge.second].color) * 0.5f; // Average the colors of the two vertices

    // Add the second vertex's triangles to the first vertex's triangles
    vertices[edge.first].triangleIDs.insert(vertices[edge.second].triangleIDs.begin(), vertices[edge.second].triangleIDs.end());

    // Update the triangles of the the second vertex to point to the first vertex
    foreach (tri, vertices[edge.second].triangleIDs)
    {
        triangles[tri].swapVertexIndex(edge.second, edge.first);
    }

    // Erase this edge from both vertices' edge lists
    edges[edge.first].vertexEdges.erase(edge.second);
    edges[edge.second].vertexEdges.erase(edge.first);

    // Replace the second vertex with the first in all the edges connected to the second vertex
    foreach (otherVertex, edges[edge.second].vertexEdges)
    {
        edges[otherVertex].vertexEdges.erase(edge.second);
        edges[otherVertex].vertexEdges.insert(edge.first);
        edges[edge.first].vertexEdges.insert(otherVertex);
    }

    edges[edge.second].vertexEdges.clear();
    vertices[edge.second].triangleIDs.clear();

    removeVertex(edge.second);
}

void Decimation::collapseTriangle(KeyData tri) DECNOEXCEPT
{
    IndexedTriangle triangle = triangles[tri];
    collapseEdge(make_pair(triangle[0], triangle[1]));
    collapseEdge(make_pair(triangle[0], triangle[2]));
}

void Decimation::removeVertex(KeyData vertexID) DECNOEXCEPT
{
    if (!vertices[vertexID].triangleIDs.empty())
    {
        say "Error: vertex needs to be disconnected before it can be removed" done;
        return;
    }

    if (!edges[vertexID].vertexEdges.empty())
    {
        say "Error: vertex needs to be disconnected before it can be removed" done;
        return;
    }

    KeyData replacement = vertices.size() - 1;

    if (vertexID == replacement)
    {
        vertices.resize(replacement);
        edges.resize(replacement);
        return;
    }

    // Replace the vertex's edges with the replacements
    edges[vertexID].vertexEdges = edges[replacement].vertexEdges;

    // Update the replacement's edges to point to its new index
    foreach (otherVertex, edges[replacement].vertexEdges)
    {
        edges[otherVertex].vertexEdges.erase(replacement);
        edges[otherVertex].vertexEdges.insert(vertexID);
    }

    // Update the replacement's triangles to point to its new index
    foreach (tri, vertices[replacement].triangleIDs)
    {
        triangles[tri].swapVertexIndex(replacement, vertexID);
    }

    // Replace the vertex with the replacement
    vertices[vertexID] = vertices[replacement];

    vertices.resize(replacement);
    edges.resize(replacement);
}

void Decimation::removeVertices(set<KeyData, greater<KeyData>> vertexSet) DECNOEXCEPT
{
    foreach (vertexID, vertexSet)
    {
        removeVertex(vertexID);
    }
}

/**
 * @brief Replace the given triangle with the last triangle in the list.
 * 		  If the triangle to be removed is the last triangle in the list,
 * 		  then just resize the list.
 *
 * NOTE:    Using skipResize and replacement parameters assumes these are
 *          handled correctly outside this function.
 *
 * @param tri
 */
void Decimation::removeTriangle(KeyData tri) TRINOEXCEPT
{
    removeTriangleFromOctreeParallel(tri); // Remove the triangle from the octree

    // Remove triangle from its vertices' triangle lists
    vertices[triangles[tri][0]].removeTriangle(tri);
    vertices[triangles[tri][1]].removeTriangle(tri);
    vertices[triangles[tri][2]].removeTriangle(tri);

    KeyData replacement = triangles.size() - 1;

    // If the triangle to be removed is the last triangle in the list, then just resize the list.
    if (replacement == tri)
    {
        triangles.resize(replacement);
        triangleToOctantList.resize(replacement);
        return;
    }

    // Remove the replacement from the octree
    removeTriangleFromOctreeParallel(replacement);

    // Update the vertices of the replacement to point to its new index
    vertices[triangles[replacement][0]].removeTriangle(replacement);
    vertices[triangles[replacement][1]].removeTriangle(replacement);
    vertices[triangles[replacement][2]].removeTriangle(replacement);
    vertices[triangles[replacement][0]].addTriangle(tri);
    vertices[triangles[replacement][1]].addTriangle(tri);
    vertices[triangles[replacement][2]].addTriangle(tri);

    triangles[tri] = triangles[replacement]; // Replace the triangle with the replacement
    insertTriangleParallel(tri);             // Insert the replacement into the octree

    // Resize the lists
    triangles.resize(replacement);
    triangleToOctantList.resize(replacement);
}

/**
 * @brief Remove the given triangles from the list by replacing them with triangles from the end of the list.
 * NOTE:    Not the most efficient way for removing large numbers of triangles.
 *          Use resetTriangleList() for better performance.
 * @param triangles
 */
void Decimation::removeTriangles(KeyList triList) TRINOEXCEPT
{
    sort(triList.begin(), triList.end(), greater<KeyData>()); // Sort the list so that we can remove the triangles in order
    foreach (tri, triList)
    {
        removeTriangle(tri);
    }
}