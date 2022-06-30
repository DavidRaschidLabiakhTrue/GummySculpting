#include "Decimation.hpp"

using namespace _Decimation;

void Decimation::decimateMesh(float percentage) DECNOEXCEPT
{
    EdgePQ edgePQ = parameterizeEdges();
    set<KeyData, greater<KeyData>> vertexSet;
    int cullTarget = (int)(triangles.size() * percentage);
    int numCulled = 0;
    // cullTarget = 1;
    while (numCulled < cullTarget)
    {
        EdgeTuple edge = edgePQ.top();
        edgePQ.pop();

        if (!edges[get<1>(edge)].vertexEdges.contains(get<2>(edge)))
        {
            continue;
        }

        // Verify edge, push if distance is different
        float dist = glm::distance(vertices[get<1>(edge)].position, vertices[get<2>(edge)].position);
        if (get<0>(edge) != dist)
        {
            edgePQ.push(make_tuple(dist, get<1>(edge), get<2>(edge)));
            continue;
        }

        removeTriangles(collapseEdge(make_pair(get<1>(edge), get<2>(edge))));
        vertexSet.insert(get<2>(edge));
        numCulled += 2;
    }

    removeVertices(vertexSet);

    refresh();
    verifyMesh();
    // rebuildOctree();
}

void Decimation::verifyMesh()
{
    int numTriangles = triangles.size();
    int numVertices = vertices.size();

    int badTriangles = 0;
    int badVertices = 0;
    int badEdges = 0;
    int badOctants = 0;

    foreach (tri, triangles)
    {
        if (tri[0] >= numVertices || tri[1] >= numVertices || tri[2] >= numVertices)
        {
            badTriangles++;
        }
    }

    foreach (vertex, vertices)
    {
        if (vertex.triangleIDs.size() == 0)
        {
            badVertices++;
        }
        foreach (triD, vertex.triangleIDs)
        {
            if (triD >= numTriangles)
            {
                badVertices++;
                break;
            }
        }
    }

    foreach (edgeList, edges)
    {
        if (edgeList.vertexEdges.size() == 0)
        {
            badEdges++;
        }
        foreach (otherVertex, edgeList.vertexEdges)
        {
            if (otherVertex >= numVertices)
            {
                badEdges++;
                break;
            }
        }
    }

    foreach(octant, octants) {
        foreach(tri, *(octant.triangleIDs)) {
            if(tri >= numTriangles) {
                badOctants++;
            }
        }
    }

    say "Bad triangles: " << badTriangles done;
    say "Bad vertices: " << badVertices done;
    say "Bad edges: " << badEdges done;
    say "Bad octants: " << badOctants done;
    say "-----------------------------------------------------" done;
}

EdgePQ Decimation::parameterizeEdges() DECNOEXCEPT
{
    EdgePQ pq;

    int numverts = vertices.size();
    for (int vertexID = 0; vertexID < numverts; vertexID++)
    {
        foreach (otherVertexID, edges[vertexID].vertexEdges)
        {
            if (otherVertexID < vertexID)
            {
                continue;
            }

            pq.push(make_tuple(glm::distance(vertices[vertexID].position, vertices[otherVertexID].position),
                               vertexID,
                               otherVertexID));
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
 * @return KeyList
 */
KeyList Decimation::collapseEdge(EdgePair edge) DECNOEXCEPT
{
    KeyList sharedTriangles = getEdgeTriangles(edge);

    vertices[edge.first] = getEdgeMidpoint(edge.first, edge.second);
    vertices[edge.first].color = (vertices[edge.first].color + vertices[edge.second].color) * 0.5f;

    // Remove shared triangles from their vertices
    foreach (tri, sharedTriangles)
    {
        for (int i = 0; i < 3; i++)
        {
            RV3D vertex = vertices[triangles[tri][i]];
            vertex.triangleIDs.erase(find(vertex.triangleIDs.begin(), vertex.triangleIDs.end(), tri));
        }
    }

    // Add the other triangles connected to the second vertex to the first and replace the second vertex with the first
    foreach (tri, vertices[edge.second].triangleIDs)
    {
        vertices[edge.first].triangleIDs.emplace_back(tri);

        if (triangles[tri][0] == edge.second)
        {
            triangles[tri][0] = edge.first;
        }
        else if (triangles[tri][1] == edge.second)
        {
            triangles[tri][1] = edge.first;
        }
        else
        {
            triangles[tri][2] = edge.first;
        }
    }

    // Replace the second vertex with the first in all the edges connected to the second vertex
    foreach (otherVertex, edges[edge.second].vertexEdges)
    {
        edges[otherVertex].vertexEdges.erase(edge.second);
        if (otherVertex != edge.first)
        {
            edges[otherVertex].vertexEdges.insert(edge.first);
            edges[edge.first].vertexEdges.insert(otherVertex);
        }
    }

    edges[edge.second].vertexEdges.clear();
    vertices[edge.second].triangleIDs.clear();

    return sharedTriangles;
}

void Decimation::collapseTriangle(KeyData tri) DECNOEXCEPT
{
    IndexedTriangle triangle = triangles[tri];
    removeTriangles(collapseEdge(make_pair(triangle[0], triangle[1])));
    removeTriangles(collapseEdge(make_pair(triangle[0], triangle[2])));
}

void Decimation::removeVertex(KeyData vertexID) DECNOEXCEPT
{
    KeyData replacement = vertices.size() - 1;

    if (vertexID != replacement)
    {
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
            if (triangles[tri][0] == replacement)
            {
                triangles[tri][0] = vertexID;
            }
            else if (triangles[tri][1] == replacement)
            {
                triangles[tri][1] = vertexID;
            }
            else
            {
                triangles[tri][2] = vertexID;
            }
        }

        vertices[vertexID] = vertices[replacement];
    }

    vertices.resize(replacement);
    edges.resize(edges.size() - 1);
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
 * @param skipResize
 * @param replacement
 */
void Decimation::removeTriangle(KeyData tri, bool skipResize, int replacement) TRINOEXCEPT
{
    if (replacement == -1)
    {
        replacement = triangles.size() - 1;
    }

    removeTriangleFromOctreeParallel(tri);

    if (replacement != tri)
    {
        removeTriangleFromOctreeParallel(replacement);
        triangles[tri] = triangles[replacement];

        for (int i = 0; i < 3; i++)
        {
            auto iter = find(vertices[triangles[replacement][i]].triangleIDs.begin(),
                               vertices[triangles[replacement][i]].triangleIDs.end(),
                               replacement);
            if (iter != vertices[triangles[replacement][i]].triangleIDs.end())
            {
                *iter = tri;
            }
        }
        insertTriangleParallel(tri);
    }

    if (!skipResize)
    {
        triangles.resize(replacement);
        triangleToOctantList.resize(replacement);
    }
}

/**
 * @brief Remove the given triangles from the list by replacing them with triangles from the end of the list.
 * NOTE:    Not the most efficient way for removing large numbers of triangles.
 *          Use resetTriangleList() for better performance.
 * @param triangles
 */
void Decimation::removeTriangles(KeyList triList) TRINOEXCEPT
{
    // Largest key first to avoid using larger indices as replacements
    sort(triList.begin(), triList.end(), greater<int>());

    int triListSize = triList.size();
    int trianglesSize = triangles.size();

    if (triListSize == trianglesSize)
    {
        triangles.clear();
        return;
    }

    KeyData replacement = trianglesSize - 1;
    foreach (tri, triList)
    {
        removeTriangle(tri, true, replacement--);
    }

    triangles.resize(trianglesSize - triListSize);
    triangleToOctantList.resize(trianglesSize - triListSize);
}