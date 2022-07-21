#include "Decimation.hpp"

using namespace _Decimation;
// TODO: fix to not leave stray vertex in special case of deleting triangle with one vertex hanging out
void Decimation::decimateMesh(float percentage) DECNOEXCEPT
{
    EdgePQ edgePQ = parameterizeEdges();
    int cullTarget = (int)(triangles.size() * percentage);
    int numCulled = 0;

    do
    {
        if (triangles.size() == 0)
        {
            return;
        }
        else if (triangles.size() == 1)
        {
            deleteTriangle(0);
            break;
        }
        else if (triangles.size() == 2)
        {
            deleteTriangle(1);
            break;
        }

        DistEdgePair distEdgePair = edgePQ.top();
        edgePQ.pop();
        EdgePair edge = distEdgePair.second;

        if (edge.first >= vertices.size() ||
            edge.second >= vertices.size() ||
            !edges[edge.first].vertexEdges.contains(edge.second) ||
            distance(vertices[edge.first].position, vertices[edge.second].position) != distEdgePair.first)
        {
            continue;
        }

        collapseEdge(edge);
        parameterizeVertexEdges(edge.first, edgePQ);
        numCulled += 2;
    } while (numCulled < cullTarget && !edgePQ.empty());

    octreeReinsertTrianglesParallel();
}

void Decimation::collapseEdge(EdgePair edge) DECNOEXCEPT
{
    // average the two vertices
    vertices[edge.first] = (vertices[edge.first].position + vertices[edge.second].position) * 0.5f;
    vertices[edge.first] = (vertices[edge.first].color + vertices[edge.second].color) * 0.5f;

    //

    KeyList sharedTriangles = getEdgeTriangles(edge);
    std::sort(sharedTriangles.begin(), sharedTriangles.end(), greater<int>());

    // Delete shared triangles
    foreach (tri, sharedTriangles)
    {
        deleteTriangle(tri);
    }

    //

    // swap the indices of the second vertex's triangles to the first
    foreach (tri, vertices[edge.second].triangleIDs)
    {
        triangles[tri].swapVertexIndex(edge.second, edge.first);
    }

    // Add second vertices triangles to the first
    vertices[edge.first].triangleIDs.insert(vertices[edge.second].triangleIDs.begin(),
                                            vertices[edge.second].triangleIDs.end());

    //

    // clear its triangles (avoids deleting triangles from deleteVertex)
    vertices[edge.second].triangleIDs.clear();

    // Delete the edge
    edges[edge.first].vertexEdges.erase(edge.second);
    edges[edge.second].vertexEdges.erase(edge.first);

    // insert the second vertex's edges into the first vertex's edge list
    edges[edge.first].vertexEdges.insert(edges[edge.second].vertexEdges.begin(),
                                         edges[edge.second].vertexEdges.end());

    // add first vertex to the second vertex's connected vertices
    foreach (otherVertex, edges[edge.second].vertexEdges)
    {
        edges[otherVertex].vertexEdges.insert(edge.first);
    }

    // delete the second vertex from vertices
    deleteVertex(edge.second);
}

EdgePQ Decimation::parameterizeEdges() DECNOEXCEPT
{
    EdgePQ pq;

    int numverts = vertices.size();
    for (int vertexID = 0; vertexID < numverts; vertexID++)
    {
        parameterizeVertexEdges(vertexID, pq);
    }

    return pq;
}

void Decimation::parameterizeVertexEdges(KeyData vertexID, EdgePQ &pq) DECNOEXCEPT
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

void Decimation::swapTriangles(KeyData tri1, KeyData tri2) DECNOEXCEPT
{
    for (int i = 0; i < 3; i++)
    {
        vertices[triangles[tri1][i]].removeTriangle(tri1);
        vertices[triangles[tri2][i]].removeTriangle(tri2);
    }

    for (int i = 0; i < 3; i++)
    {
        vertices[triangles[tri1][i]].addTriangle(tri2);
        vertices[triangles[tri2][i]].addTriangle(tri1);
    }

    IndexedTriangle temp = triangles[tri1];
    triangles[tri1] = triangles[tri2];
    triangles[tri2] = temp;

    // reinsert triangles to octree
    removeTriangleFromOctreeParallel(tri1);
    insertTriangleParallel(tri1);
    removeTriangleFromOctreeParallel(tri2);
    insertTriangleParallel(tri2);
}

bool Decimation::doesEdgeExist(KeyData v1, KeyData v2) DECNOEXCEPT
{
    foreach (tri, vertices[v1].triangleIDs)
    {
        if (vertices[v2].triangleIDs.contains(tri))
        {
            return true;
        }
    }
    return false;
}

void Decimation::deleteTriangle(KeyData tri) DECNOEXCEPT
{
    if (triangles.empty())
    {
        return;
    }

    KeyData lastTri = triangles.size() - 1;
    if (tri != lastTri)
    {
        swapTriangles(tri, lastTri);
    }

    vertices[triangles[lastTri][0]].removeTriangle(lastTri);
    vertices[triangles[lastTri][1]].removeTriangle(lastTri);
    vertices[triangles[lastTri][2]].removeTriangle(lastTri);

    // // erase edge if it doesn't connect to a neighboring triangle
    // for (int i = 0; i < 3; i++)
    // {
    //     if (!doesEdgeExist(triangles[lastTri][i], triangles[lastTri][(i + 1) % 3]))
    //     {
    //         edges[triangles[lastTri][i]].vertexEdges.erase(triangles[lastTri][(i + 1) % 3]);
    //         edges[triangles[lastTri][(i + 1) % 3]].vertexEdges.erase(triangles[lastTri][i]);
    //     }
    // }

    removeTriangleFromOctreeParallel(lastTri);
    triangleToOctantList.resize(lastTri);
    triangles.pop_back();
}

void Decimation::swapVertices(KeyData v1, KeyData v2) DECNOEXCEPT
{
    // Triangles
    // Need to avoid reversing normals if vertices are connected...
    vector<int> sharedTris;
    foreach (tri, vertices[v1].triangleIDs)
    {
        if (vertices[v2].triangleIDs.contains(tri))
        {
            sharedTris.emplace_back(tri);
            vertices[v2].removeTriangle(tri);
            continue;
        }
        triangles[tri].swapVertexIndex(v1, v2);
    }

    foreach (tri, vertices[v2].triangleIDs)
    {
        triangles[tri].swapVertexIndex(v2, v1);
    }

    foreach (tri, sharedTris)
    {
        for (int i = 0; i < 3; i++)
        {
            if (triangles[tri][i] == v1)
            {
                triangles[tri][i] = v2;
            }
            else if (triangles[tri][i] == v2)
            {
                triangles[tri][i] = v1;
            }
        }
        vertices[v2].addTriangle(tri);
    }

    // Edges
    VertexEdges v2copy = edges[v2].vertexEdges; // need copy if v1 v2 are connected
    foreach (otherVertex, edges[v1].vertexEdges)
    {
        edges[otherVertex].vertexEdges.erase(v1);
        edges[otherVertex].vertexEdges.insert(v2);
    }
    foreach (otherVertex, v2copy)
    {
        edges[otherVertex].vertexEdges.erase(v2);
        edges[otherVertex].vertexEdges.insert(v1);
    }

    // Swap
    Edge tempEdge = edges[v1];
    edges[v1] = edges[v2];
    edges[v2] = tempEdge;

    V3D temp = vertices[v1];
    vertices[v1] = vertices[v2];
    vertices[v2] = temp;
}

void Decimation::deleteVertex(KeyData vertexID) DECNOEXCEPT
{
    if (vertices.empty())
    {
        return;
    }

    KeyData lastVertex = vertices.size() - 1;
    if (vertexID != lastVertex)
    {
        swapVertices(vertexID, lastVertex);
    }

    // triangles cannot exist without this vertex
    while (!vertices[lastVertex].triangleIDs.empty())
    {
        deleteTriangle(*(vertices[lastVertex].triangleIDs.begin()));
    }

    foreach (otherVertex, edges[lastVertex].vertexEdges)
    {
        edges[otherVertex].vertexEdges.erase(lastVertex);
    }

    vertices.pop_back();
    edges.pop_back();
}

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
    unordered_set<tuple<int, int, int>, hash_tuple> triangleSet;
    int trix = 0;
    foreach (tri, triangles)
    {
        vector<int> triVertices(begin(tri.indice), end(tri.indice));
        sort(triVertices.begin(), triVertices.end());
        tuple<int, int, int> triTuple = make_tuple(triVertices[0], triVertices[1], triVertices[2]);
        if (triangleSet.contains(triTuple))
        {
            "duplicate triangle found";
        }
        else
        {
            triangleSet.insert(triTuple);
        }

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
                badConnections++; // this
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
                badConnections++; // this
                continue;
            }

            // check if vertex edges contain the other vertices in triangle
            if (!edges[vertexID].vertexEdges.contains(otherV1) || !edges[vertexID].vertexEdges.contains(otherV2))
            {
                badConnections++;
            }

            // pair<KeyData, KeyData> triPair = make_pair(glm::min(otherV1, otherV2), glm::max(otherV1, otherV2));
            // if (triangleSet.contains(triPair))
            // {
            //     say "Duplicate triangle found" done;
            // }
            // else
            // {
            //     triangleSet.insert(triPair);
            // }
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
                badConnections++;
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