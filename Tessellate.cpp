#include "Tessellate.hpp"

using namespace Sculpting;
using namespace Sculpting::Tessellate;

void Tessellate::applyTessellate(MeshReference cMesh, SculptPayloadReference payload)
{
    payload.last = -1;
    if (payload.wasRun)
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

    int innerVertexCount = (int)allVerticesInRange.size();

    // Get outer triangles (exactly 2 vertices in range)
    unordered_set<int> outerTriangleSet;

    foreach (tri, cMesh.affectedTriangles)
    {
        if (!innerTriangleSet.contains(tri))
        {
            int count = 0;
            if (allVerticesInRange.contains(triangles[tri][0]))
                count++;
            if (allVerticesInRange.contains(triangles[tri][1]))
                count++;
            if (allVerticesInRange.contains(triangles[tri][2]))
                count++;

            if (count == 2)
            {
                outerTriangleSet.insert(tri);
            }
        }
    }

    splitAdjacentOuterTriangles(cMesh, payload, outerTriangleSet, allVerticesInRange);

    unordered_map<v3, KeyData> midpointMap = createMidpointMap(cMesh, allVerticesInRange);

    subdivideInnerTriangles(cMesh, midpointMap, innerTriangleSet);

    splitOuterTriangles(cMesh, payload, outerTriangleSet, midpointMap, allVerticesInRange);

    cMesh.generateEdges();
    cMesh.updateAffectedTrianglesParallel();
    cMesh.computeNormals();
    cMesh.refresh();
}

unordered_map<v3, KeyData> Tessellate::createMidpointMap(MeshReference cMesh, std::unordered_set<int> &allVerticesInRange)
{
    unordered_map<v3, KeyData> midpointMap;
    int vertexIndex = (int)cMesh.vertices.size();

    foreach (vertexID, allVerticesInRange)
    {
        foreach (otherVertexID, cMesh.edges[vertexID].vertexEdges)
        {
            if (allVerticesInRange.contains(otherVertexID))
            {
                v3 midpoint = cMesh.getEdgeMidpoint(vertexID, otherVertexID);
                V3D newVert = midpoint;
                newVert.color = (cMesh.vertices[vertexID].color + cMesh.vertices[otherVertexID].color) * 0.5f;
                cMesh.vertices.emplace_back(newVert);
                midpointMap.emplace(midpoint, vertexIndex);

                vertexIndex++;
            }
        }
    }

    return midpointMap;
}

void Tessellate::splitAdjacentOuterTriangles(MeshReference cMesh, SculptPayloadReference payload, std::unordered_set<int> &outerTriangleSet, std::unordered_set<int> &allVerticesInRange)
{
    IndexedTriangles &triangles = cMesh.triangles;
    Vertices &vertices = cMesh.vertices;
    unordered_set<int> adjacentTriangleSet;

    foreach (tri, outerTriangleSet)
    {
        if (adjacentTriangleSet.contains(tri))
        {
            continue;
        }

        KeyData outsideVertex;
        KeyData insideVertexLeft;
        KeyData insideVertexRight;

        if (!allVerticesInRange.contains(triangles[tri][0]))
        {
            outsideVertex = triangles[tri][0];
            insideVertexLeft = triangles[tri][1];
            insideVertexRight = triangles[tri][2];
        }
        else if (!allVerticesInRange.contains(triangles[tri][1]))
        {
            outsideVertex = triangles[tri][1];
            insideVertexLeft = triangles[tri][2];
            insideVertexRight = triangles[tri][0];
        }
        else if (!allVerticesInRange.contains(triangles[tri][2]))
        {
            outsideVertex = triangles[tri][2];
            insideVertexLeft = triangles[tri][0];
            insideVertexRight = triangles[tri][1];
        }

        // Check if a neighboring outer triangle exists
        // Prefer neighbor with lower index
        KeyData neighborTri = std::numeric_limits<int>::max();
        bool noNeighborFound = true;

        foreach (otherTri, vertices[outsideVertex].triangleIDs)
        {
            if (otherTri != tri &&
                outerTriangleSet.contains(otherTri) &&
                (triangles[otherTri][0] == insideVertexLeft || triangles[otherTri][0] == insideVertexRight ||
                 triangles[otherTri][1] == insideVertexLeft || triangles[otherTri][1] == insideVertexRight ||
                 triangles[otherTri][2] == insideVertexLeft || triangles[otherTri][2] == insideVertexRight))
            {
                neighborTri = glm::min((int)neighborTri, otherTri);
                noNeighborFound = false;
                adjacentTriangleSet.insert(otherTri);
            }
        }

        if (noNeighborFound)
        {
            continue;
        }

        /*
         * Find shared vertex and set variables
         *
         *          outsideVertex
         *         /|\
         *        / | \
         *       /t2|t3\
         *      /   -mp \
         *     /    |    \
         *    / t0  |  t1 \
         *   /______|______\
         * v0     shared    v1
         *
         */
        KeyData sharedVertex;
        KeyData v0, v1;
        KeyData t0, t1;
        for (int i = 0; i < 3; i++)
        {
            if (triangles[neighborTri][i] == insideVertexLeft)
            {
                t0 = neighborTri;
                t1 = tri;
                sharedVertex = insideVertexLeft;
                v0 = (triangles[t0][(i + 1) % 3] != outsideVertex) ? triangles[t0][(i + 1) % 3] : triangles[t0][(i + 2) % 3];
                v1 = insideVertexRight;
                break;
            }

            if (triangles[neighborTri][i] == insideVertexRight)
            {
                t0 = tri;
                t1 = neighborTri;
                sharedVertex = insideVertexRight;
                v0 = insideVertexLeft;
                v1 = (triangles[t1][(i + 1) % 3] != outsideVertex) ? triangles[t1][(i + 1) % 3] : triangles[t1][(i + 2) % 3];
                break;
            }
        }

        // Create Midpoint
        v3 midpoint = cMesh.getEdgeMidpoint(outsideVertex, sharedVertex);
        V3D newVert = midpoint;
        KeyData midpointIndex = (KeyData)vertices.size();
        newVert.color = (vertices[outsideVertex].color + vertices[sharedVertex].color) * 0.5f;
        vertices.emplace_back(newVert);

        // Adjust old triangles
        triangles[t0] = IndexedTriangle(midpointIndex, v0, sharedVertex);
        triangles[t1] = IndexedTriangle(midpointIndex, sharedVertex, v1);

        // Remove old triangles from outside vertex
        vertices[outsideVertex].removeTriangle(t0);
        vertices[outsideVertex].removeTriangle(t1);

        // Add new triangles
        KeyData t2 = (KeyData)triangles.size();
        KeyData t3 = t2 + 1;
        triangles.emplace_back(IndexedTriangle(v0, midpointIndex, outsideVertex));
        triangles.emplace_back(IndexedTriangle(v1, outsideVertex, midpointIndex));
        cMesh.insertTriangle(t2);
        cMesh.insertTriangle(t3);

        // Add new triangles to their vertices
        vertices[v0].addTriangle(t2);
        vertices[outsideVertex].addTriangle(t2);

        vertices[v1].addTriangle(t3);
        vertices[outsideVertex].addTriangle(t3);

        // Add all triangles to midpoint
        vertices[midpointIndex].addTriangle(t0);
        vertices[midpointIndex].addTriangle(t1);
        vertices[midpointIndex].addTriangle(t2);
        vertices[midpointIndex].addTriangle(t3);
    }
}

void Tessellate::subdivideInnerTriangles(MeshReference cMesh, unordered_map<v3, KeyData> &midpointMap, std::unordered_set<int> &innerTriangleSet)
{
    IndexedTriangles &triangles = cMesh.triangles;
    Vertices &vertices = cMesh.vertices;
    int triangleIndex = (int)triangles.size();

    // Generate new triangles
    foreach (tri, innerTriangleSet)
    {
        KeyList midpoints = {
            midpointMap[cMesh.getEdgeMidpoint(triangles[tri][0], triangles[tri][1])],
            midpointMap[cMesh.getEdgeMidpoint(triangles[tri][1], triangles[tri][2])],
            midpointMap[cMesh.getEdgeMidpoint(triangles[tri][2], triangles[tri][0])]};

        for (int i = 0; i < 3; i++)
        {
            vertices[triangles[tri][i]].removeTriangle(tri);
            IndexedTriangle newTriangle(triangles[tri][i], midpoints[i], midpoints[(i + 2) % 3]);
            vertices[newTriangle[0]].addTriangle(triangleIndex);
            vertices[newTriangle[1]].addTriangle(triangleIndex);
            vertices[newTriangle[2]].addTriangle(triangleIndex);
            triangles.emplace_back(newTriangle);
            cMesh.insertTriangle(triangleIndex);
            triangleIndex++;
        }

        triangles[tri][0] = midpoints[0];
        triangles[tri][1] = midpoints[1];
        triangles[tri][2] = midpoints[2];
        vertices[midpoints[0]].addTriangle(tri);
        vertices[midpoints[1]].addTriangle(tri);
        vertices[midpoints[2]].addTriangle(tri);
    }
}

void Tessellate::splitOuterTriangles(MeshReference cMesh, SculptPayloadReference payload, std::unordered_set<int> &outerTriangleSet, unordered_map<v3, KeyData> &midpointMap, unordered_set<int> &allVerticesInRange)
{
    IndexedTriangles &triangles = cMesh.triangles;
    Vertices &vertices = cMesh.vertices;
    int triangleIndex = (int)triangles.size();

    foreach (tri, outerTriangleSet)
    {
        KeyData outsideVertex = triangles[tri][0];
        KeyData insideVertexLeft = triangles[tri][1];
        KeyData insideVertexRight = triangles[tri][2];

        if (!allVerticesInRange.contains(triangles[tri][1]))
        {
            outsideVertex = triangles[tri][1];
            insideVertexLeft = triangles[tri][2];
            insideVertexRight = triangles[tri][0];
        }
        else if (!allVerticesInRange.contains(triangles[tri][2]))
        {
            outsideVertex = triangles[tri][2];
            insideVertexLeft = triangles[tri][0];
            insideVertexRight = triangles[tri][1];
        }

        KeyData midpointVertex = midpointMap[cMesh.getEdgeMidpoint(insideVertexLeft, insideVertexRight)];
        IndexedTriangle leftTri(outsideVertex, insideVertexLeft, midpointVertex);
        triangles[tri] = IndexedTriangle(outsideVertex, midpointVertex, insideVertexRight);

        vertices[insideVertexLeft].removeTriangle(tri);

        vertices[midpointVertex].addTriangle(tri);
        vertices[midpointVertex].addTriangle(triangleIndex);
        vertices[insideVertexLeft].addTriangle(triangleIndex);
        vertices[outsideVertex].addTriangle(triangleIndex);

        triangles.emplace_back(leftTri);
        cMesh.insertTriangle(triangleIndex);
        triangleIndex++;
    }
}