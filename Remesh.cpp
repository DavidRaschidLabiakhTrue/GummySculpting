#include "Remesh.hpp"

using namespace _Remesh;

void Remesh::remesh(int nTimes) REMNOEXCEPT
{
    say triangles.size() done;
    for (int i = 0; i < nTimes; i++)
    {
        loopSubdivision(1, true);
        decimateMesh(0.36);
        decimateMesh(0.36);
        decimateMesh(0.36);
    }

    // Remove low-valence vertices
    vector<KeyData> temp;
    for (int i = vertices.size() - 1; i >= 0; i--)
    {
        if (edges[i].vertexEdges.size() == 3)
        {
            temp.emplace_back(i);
        }
    }

    foreach (vertexID, temp)
    {
        KeyData shortestEdge;
        float shortestEdgeLength = FLT_MAX;

        // get edges vectors
        foreach (otherVertex, edges[vertexID].vertexEdges)
        {
            float temp = distance(vertices[vertexID].position, vertices[otherVertex].position);
            if (temp < shortestEdgeLength)
            {
                shortestEdgeLength = temp;
                shortestEdge = otherVertex;
            }
            vertices[otherVertex].position += 0.25f * (vertices[vertexID].position - vertices[otherVertex].position);
            vertices[otherVertex].color = ((3.0f * vertices[otherVertex].color) + vertices[vertexID].color) * 0.25f;
        }
        KeyData v1, v2;
        if (shortestEdge < vertexID)
        {
            v1 = shortestEdge;
            v2 = vertexID;
        }
        else
        {
            v1 = vertexID;
            v2 = shortestEdge;
        }
        collapseEdge(EdgePair(v1, v2));

        foreach (tri, vertices[v1].triangleIDs) {
            updateTriangleInOctreeParallel(tri);
        }
    }
    say triangles.size() done;
}