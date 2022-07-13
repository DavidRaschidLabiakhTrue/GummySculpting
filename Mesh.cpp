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

// TODO: Test runtimes and scaling of each version
// Testing with normal function to find degenerate triangles
void MeshDefinition::Mesh::computeNormals()
{
    // computeNormalsParallel();
    normalList.clear();
    const int totalTri = this->totalTriangles();
    normalList.reserve(totalTri);
    // first calculate all the normals
    for (int i = 0; i < totalTri; i++)
    {
        normalList.emplace_back(this->getTriangleNormal(i));

        if (isnan(normalList[i].x) || isnan(-normalList[i].x) ||
            isnan(normalList[i].y) || isnan(-normalList[i].y) ||
            isnan(normalList[i].z) || isnan(-normalList[i].z))
        {
            say "Degenerate Triangle Found" done;
            say "Triangle" spc i spc "Normal: " spc to_string(normalList[i]) done;
            say "v0" spc triangles[i][0] spc to_string(vertices[triangles[i][0]].position) done;
            say "v1" spc triangles[i][1] spc to_string(vertices[triangles[i][1]].position) done;
            say "v2" spc triangles[i][2] spc to_string(vertices[triangles[i][2]].position) done;
            say "---------------------------------" done;
        }
    }

    forall(vert, this->vertices)
    {
        v3 tempNorm = v3(0);
        forall(id, vert.triangleIDs)
        {
            tempNorm += normalList[id]; // add them up
        }


        vert.normal = normalize(tempNorm / ((float)vert.triangleIDs.size())); // average them



        //if (isnan(vert.normal.x) || isnan(-vert.normal.x) ||
        //    isnan(vert.normal.y) || isnan(-vert.normal.y) ||
        //    isnan(vert.normal.z) || isnan(-vert.normal.z))
        //{
        //    say "Vertex Normal: " spc to_string(vert.normal) done;
        //    say "triangleIDs size: " spc vert.triangleIDs.size() done;
        //    say "---------------------------------" done;
        //}
    }
    //say "Normals Calculated" done;
}

void MeshDefinition::Mesh::computeNormalsParallel()
{
    const int totalTri = this->totalTriangles();
    normalList = vector<v3>(totalTri);

    int nThreads = getNThreads;
    vector<thread> threads;

    for (int threadID = 0; threadID < nThreads; threadID++)
    {
        const int id = threadID;
        threads.push_back(thread([&, id]() { // is that a fucking lambda
            for (int i = id; i < totalTri; i += nThreads)
            {
                normalList[i] = this->getTriangleNormal(i);
            }
        }));
    }
    joinAndClearThreads;

    const int totalVert = this->vertices.size();
    for (int threadID = 0; threadID < nThreads; threadID++)
    {
        const int id = threadID;
        threads.push_back(thread([&, id]() {
            for (int i = id; i < totalVert; i += nThreads)
            {
                v3 tempNorm = v3(0);
                foreach (id, vertices[i].triangleIDs)
                {
                    tempNorm += normalList[id]; // add them up
                }
                vertices[i].normal = normalize(tempNorm / (float)vertices[i].triangleIDs.size()); // average them
            }
        }));
    }
    joinThreads;
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
void MeshDefinition::Mesh::recomputeNormalsFromCurrentVertices()
{
	const int totTri = (int)this->affectedTriangles.size();
	unordered_map<TriangleID, v3> newNormals;
	newNormals.reserve(totTri);

	v3 norm;

	forall(id, this->affectedTriangles)
	{
		newNormals[id] = this->getTriangleNormal(id);
	}
	forall(element, currentVertices)
	{
		norm = v3(0);
		forall(face, vertices[element.first].triangleIDs)
		{
			norm += newNormals[face];
		}
		element.second.normal = norm / (float)vertices[element.first].triangleIDs.size();
	}
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
    return result; // based
}

void MeshDefinition::Mesh::storeUndoAndCurrent()
{
	// can likely be parallelized but I've tormented ryan more than enough about that.
	currentVertices.clear();
	forall(element, trianglesInRange)
	{
		forall(id, triangles[element].indice)
		{
			if (!savedVertices.contains(id))
			{
				savedVertices[id] = vertices[id];
			}
			currentVertices[id] = vertices[id];
		}
	}
}

void MeshDefinition::Mesh::undoHistory()
{
    say "Undoing History" done;

	if (isThereHistory() && stepTracker.isStepValid())
	{
		forall(element, history[stepTracker.currentStep()].undoMap)
		{
			vertices[element.first] = element.second;
		}
		stepTracker.lowerStep();
		needToRefresh = true;
	}
	displayCurrentHistoryCount();
	
}

void MeshDefinition::Mesh::redoHistory()
{
    say "Redoing History" done;
}



void MeshDefinition::Mesh::saveSavedVerticesToUndo()
{
	saveOldToHistory();
	needToStore = true;
}

void MeshDefinition::Mesh::cullHistory(ChangeLogLevel levelsUpwardToCull)
{
}
