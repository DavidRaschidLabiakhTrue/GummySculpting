#include "Tessellate.hpp"

using namespace Sculpting;
using namespace Sculpting::Tessellate;

void Tessellate::applyTessellate(MeshReference cMesh, SculptPayloadReference payload)
{
    payload.last = -1;
    if(payload.wasRun)
    {
        return;
    }

    IndexedTriangles &triangles = cMesh.triangles;
    Vertices &vertices = cMesh.vertices;

    int tessLevel = 1; // TODO: get this from the UI/payload

    // Collect triangles
    cMesh.collectAroundCollision(payload.radius, true, true);

    // Combine symmetry
    unordered_set<int> innerTriangleSet(make_move_iterator(cMesh.trianglesInRange.begin()), make_move_iterator(cMesh.trianglesInRange.end()));
    innerTriangleSet.insert(cMesh.reflectedTrianglesInRange.begin(), cMesh.reflectedTrianglesInRange.end());

    unordered_set<int> allVerticesInRange(make_move_iterator(cMesh.verticesInRange.begin()), make_move_iterator(cMesh.verticesInRange.end()));
    allVerticesInRange.insert(cMesh.reflectedVerticesInRange.begin(), cMesh.reflectedVerticesInRange.end());

    int innerVertexCount = (int) allVerticesInRange.size();

    // Get outer triangles (exactly 2 vertices in range)
    TriangleIDList outerTriangleList;

    foreach (tri, cMesh.affectedTriangles)
    {
        int count = 0;
        if (!innerTriangleSet.contains(tri))
        {
            if (abs(distance(vertices[triangles[tri][0]].position, cMesh.collision.position)) <= payload.radius)
                count++;
            if (abs(distance(vertices[triangles[tri][1]].position, cMesh.collision.position)) <= payload.radius)
                count++;
            if (abs(distance(vertices[triangles[tri][2]].position, cMesh.collision.position)) <= payload.radius)
                count++;

            if (count == 2)
            {
                outerTriangleList.emplace_back(tri);
            }
        }
    }

    // Generate midpoints
    unordered_map<v3, KeyData> midpointMap;
    int vertexIndex = (int)vertices.size();

    foreach (vertexID, allVerticesInRange)
    {
        foreach (otherVertexID, cMesh.edges[vertexID].vertexEdges)
        {
            if (allVerticesInRange.contains(otherVertexID))
            {
                v3 midpoint = getEdgeMidpoint(cMesh, vertexID, otherVertexID);
                V3D newVert = midpoint;
                newVert.color = (vertices[vertexID].color + vertices[otherVertexID].color) * 0.5f;
                vertices.emplace_back(newVert);
                midpointMap.emplace(midpoint, vertexIndex);

                vertexIndex++;
            }
        }
    }

    // Generate new triangles
    int triangleIndex = (int)triangles.size();

    foreach (tri, innerTriangleSet)
    {
        KeyList midpoints = {
            midpointMap[getEdgeMidpoint(cMesh, triangles[tri][0], triangles[tri][1])],
            midpointMap[getEdgeMidpoint(cMesh, triangles[tri][1], triangles[tri][2])],
            midpointMap[getEdgeMidpoint(cMesh, triangles[tri][2], triangles[tri][0])]};

        for (int i = 0; i < 3; i++)
        {
            vertices[triangles[tri][i]].triangleIDs.erase(find(vertices[triangles[tri][i]].triangleIDs.begin(), vertices[triangles[tri][i]].triangleIDs.end(), tri));
            IndexedTriangle newTriangle(triangles[tri][i], midpoints[i], midpoints[(i + 2) % 3]);
            vertices[newTriangle[0]].triangleIDs.emplace_back(triangleIndex);
            vertices[newTriangle[1]].triangleIDs.emplace_back(triangleIndex);
            vertices[newTriangle[2]].triangleIDs.emplace_back(triangleIndex);
            triangles.emplace_back(newTriangle);
            triangleIndex++;
        }

        triangles[tri][0] = midpoints[0];
        triangles[tri][1] = midpoints[1];
        triangles[tri][2] = midpoints[2];
        vertices[midpoints[0]].triangleIDs.emplace_back(tri);
        vertices[midpoints[1]].triangleIDs.emplace_back(tri);
        vertices[midpoints[2]].triangleIDs.emplace_back(tri);
    }

    // Divide outer triangles
    foreach (tri, outerTriangleList)
    {
        KeyData outsideVertex;
        KeyData insideVertexLeft;
        KeyData insideVertexRight;

        if (abs(distance(cMesh.vertices[triangles[tri][0]].position, cMesh.collision.position)) > payload.radius)
        {
            outsideVertex = triangles[tri][0];
            insideVertexLeft = triangles[tri][1];
            insideVertexRight = triangles[tri][2];
        }
        else if (abs(distance(cMesh.vertices[triangles[tri][1]].position, cMesh.collision.position)) > payload.radius)
        {
            outsideVertex = triangles[tri][1];
            insideVertexLeft = triangles[tri][2];
            insideVertexRight = triangles[tri][0];
        }
        else if (abs(distance(cMesh.vertices[triangles[tri][2]].position, cMesh.collision.position)) > payload.radius)
        {
            outsideVertex = triangles[tri][2];
            insideVertexLeft = triangles[tri][0];
            insideVertexRight = triangles[tri][1];
        }

        KeyData midpointVertex = midpointMap[getEdgeMidpoint(cMesh, insideVertexLeft, insideVertexRight)];
        IndexedTriangle leftTri(outsideVertex, insideVertexLeft, midpointVertex);
        triangles[tri] = IndexedTriangle(outsideVertex, midpointVertex, insideVertexRight);

        vertices[insideVertexLeft].triangleIDs.erase(find(vertices[insideVertexLeft].triangleIDs.begin(), vertices[insideVertexLeft].triangleIDs.end(), tri));

        vertices[midpointVertex].triangleIDs.emplace_back(tri);
        vertices[midpointVertex].triangleIDs.emplace_back(triangleIndex);
        vertices[insideVertexLeft].triangleIDs.emplace_back(triangleIndex);
        vertices[outsideVertex].triangleIDs.emplace_back(triangleIndex);

        triangles.emplace_back(leftTri);
        triangleIndex++;
    }

    cMesh.generateEdges();
    cMesh.octreeReinsertTrianglesParallel();
}

inline v3 Tessellate::getEdgeMidpoint(MeshReference cMesh, KeyData v1, KeyData v2)
{
    return (cMesh.vertices[v1].position + cMesh.vertices[v2].position) * 0.5f;
}