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

void Remesh::computeNormalsRemesh() REMNOEXCEPT
{
    // computeNormalsParallel();
    normalList.clear();
    const int totalTri = this->totalTriangles();
    normalList.reserve(totalTri);

    KeyList degenTriangles;
    // first calculate all the normals
    for (int i = 0; i < totalTri; i++)
    {
        normalList.emplace_back(this->getTriangleNormal(i));

        if (glm::any(glm::isnan(normalList[i])))
        {
            degenTriangles.emplace_back(i);
            say "Degenerate Triangle Found" done;
            say "Triangle" spc i spc "Normal: " spc to_string(normalList[i]) done;
            say "v0" spc triangles[i][0] spc to_string(vertices[triangles[i][0]].position) done;
            say "v1" spc triangles[i][1] spc to_string(vertices[triangles[i][1]].position) done;
            say "v2" spc triangles[i][2] spc to_string(vertices[triangles[i][2]].position) done;
            say "---------------------------------" done;
        }
    }

    // Calculate normals for degenerate triangles
    for (int i = 0; i < degenTriangles.size(); i++)
    {
        // Gather non-degenerate neighbors
        KeyList neighbors = getTriangleNeighborsRemesh(degenTriangles[i]);
        KeyList nonDegen;
        foreach (nbor, neighbors)
        {
            if (!glm::any(glm::isnan(normalList[i])))
            {
                nonDegen.emplace_back(nbor);
            }
        }

        // Place this at the end of the list to check again when it should have a non degenerate neighbor
        if (nonDegen.size() == 0)
        {
            degenTriangles.emplace_back(degenTriangles[i]);
            continue;
        }

        // Average the normals of the neighbors
        normalList[degenTriangles[i]] = v3(0);
        foreach (nbor, nonDegen)
        {
            normalList[degenTriangles[i]] += normalList[nbor];
        }
        normalList[degenTriangles[i]] = normalize(normalList[degenTriangles[i]] / (float)nonDegen.size());
    }

    forall(vert, this->vertices)
    {
        v3 tempNorm = v3(0);
        forall(id, vert.triangleIDs)
        {
            tempNorm += normalList[id]; // add them up
        }

        vert.normal = normalize(tempNorm / ((float)vert.triangleIDs.size())); // average them
    }
    // say "Normals Calculated" done;
}

KeyList Remesh::getTriangleNeighborsRemesh(KeyData tri) REMNOEXCEPT
{
    KeyList res, tmp;
    tmp = getEdgeTriangles(triangles[tri][0], triangles[tri][1]);
    if (tmp.size() == 2)
    {
        res.emplace_back((tmp[0] == tri) ? tmp[1] : tmp[0]);
    }
    tmp = getEdgeTriangles(triangles[tri][0], triangles[tri][2]);
    if (tmp.size() == 2)
    {
        res.emplace_back((tmp[0] == tri) ? tmp[1] : tmp[0]);
    }
    tmp = getEdgeTriangles(triangles[tri][1], triangles[tri][2]);
    if (tmp.size() == 2)
    {
        res.emplace_back((tmp[0] == tri) ? tmp[1] : tmp[0]);
    }

    return res;
}