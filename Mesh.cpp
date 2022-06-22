#include "Mesh.hpp"
#include <limits>

namespace MeshDefinition
{
    int MeshIDTracker = 0;
}

using namespace MeshDefinition;

Mesh::Mesh()
{
    this->meshID = MeshIDTracker++;
}

Mesh::~Mesh()
{
}

void Mesh::createVariableMap()
{
    meshVariables.emplace("octreedepthlimit", ref(octreeDepthLimit));
    meshVariables.emplace("octanttrianglelimit", ref(octantTriangleLimit));
    meshVariables.emplace("octreebuffer", ref(octreeBuffer));
    meshVariables.emplace("octreelooseness", ref(octreeLooseness));
}

void MeshDefinition::Mesh::computeNormals()
{
    normalList.clear();
    const int totalTri = this->totalTriangles();
    normalList.reserve(totalTri);
    // first calculate all the normals
    for (int i = 0; i < totalTri; i++)
    {
        normalList.emplace_back(this->getTriangleNormal(i));
    }

    forall(vert, this->vertices)
    {
        v3 tempNorm = v3(0);
        forall(id, vert.triangleIDs)
        {
            tempNorm += normalList[id]; // add them up
        }
        vert.normal = normalize(tempNorm / (float)vert.triangleIDs.size()); // average them
    }
    say "Normals Calculated" done;
}

void MeshDefinition::Mesh::computeNormalsFromMatrix()
{
    m4 i = inverse(model);
    m4 t = glm::transpose(i);

    for (int i = 0; i < vertices.size(); i++)
    {
        v3 tempNorm = v3(0);
        forall(id, this->vertices[i].triangleIDs)
        {
            tempNorm += normalList[id];
        }

        vertices[i].normal = normalize(tempNorm / (float)this->vertices[i].triangleIDs.size()); // average them
        vertices[i].normal = v3(v4(vertices[i].normal, 1) * t);
    }
    needToRefresh = true;
}

void Mesh::applyModelMatrix()
{
    const auto totalvert = this->verticeCount();
    for (auto i = 0; i < totalvert; i++)
    {
        vertices[i].position = v3(model * v4(vertices[i].position, 1.0));
    }
    this->resetModelMatrix();
    computeNormals();
    rebuildOctree();
    this->needToRefresh = true;
}

void MeshDefinition::Mesh::recomputeNormals(HistoryKeyVertexMap &apply)
{
    const int totTri = (int)this->affectedTriangles.size();

    unordered_map<TriangleID, v3> newNormals;
    newNormals.reserve(totTri);

    forall(id, this->affectedTriangles)
    {
        newNormals[id] = this->getTriangleNormal(id);
    }
    forall(element, apply)
    {
        v3 norm = v3(0);
        forall(face, vertices[element.first].triangleIDs)
        {
            norm += newNormals[face];
        }
        element.second.normal = norm / (float)vertices[element.first].triangleIDs.size();
    }
}

void MeshDefinition::Mesh::generateGraphsAndTrees()
{
    this->generateEdges();
    computeNormals();
    collectStats();
    this->buildOctree();
}

KeyData Mesh::searchLinear(rv3 direction, rv3 origin)
{
    const int trianglecount = totalTriangles();
    KeyData result = ImpossibleKey;
    v3 testCoordinate = v3(numeric_limits<float>::max());

    v3 storedCoordinate = testCoordinate;

    for (int i = 0; i < trianglecount; i++)
    {
        auto tri = triangles[i];
        if (intersectionMoller(origin, direction, vertices[tri[0]].position, vertices[tri[1]].position, vertices[tri[2]].position, testCoordinate))
        {
            if (distance(testCoordinate, origin) < distance(storedCoordinate, origin))
            {
                storedCoordinate = testCoordinate;
                result = closest(testCoordinate, tri);
            }
            // there was a hit.
        }
    }

    return result;
}

KeyData Mesh::searchLinearParallel(rv3 direction, rv3 origin)
{
    const int triangleCount = totalTriangles();
    KeyData result = ImpossibleKey;
    float closestDistance = numeric_limits<float>::max();

    int nThreads = getNThreads;
    vector<thread> threads;
    mutex mtx;

    for (int i = 0; i < nThreads; i++)
    {
        int id = i;
        threads.push_back(thread([&, id]() {
            KeyData localResult = ImpossibleKey;
            float localClosestDistance = numeric_limits<float>::max();
            v2 bp;

            for (int triangleID = id; triangleID < triangleCount; triangleID += nThreads)
            {
                float distance = numeric_limits<float>::max();

                if (glm::intersectRayTriangle(origin, direction, vertices[triangles[triangleID][0]].position, vertices[triangles[triangleID][1]].position, vertices[triangles[triangleID][2]].position, bp, distance) && distance < localClosestDistance)
                {
                    localClosestDistance = distance;
                    localResult = triangleID;
                }
            }

            mtx.lock();
            if (localClosestDistance < closestDistance)
            {
                closestDistance = localClosestDistance;
                result = localResult;
            }
            mtx.unlock();
        }));
    }

	joinThreads;
    return result;
}

void MeshDefinition::Mesh::applyTransformation()
{
    translationValues = v3(0);
    rotationMatrix = m4(1);
    scaleValues = v3(1);
    this->applyModelMatrix();
}

void MeshDefinition::Mesh::undoHistory()
{
    say "Undoing History" done;
}

void MeshDefinition::Mesh::redoHistory()
{
    say "Redoing History" done;
}

void MeshDefinition::Mesh::cullHistory(ChangeLogLevel levelsUpwardToCull)
{
}
