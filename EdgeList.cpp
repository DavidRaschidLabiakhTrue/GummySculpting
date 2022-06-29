#include "EdgeList.hpp"

using namespace EdgeListDefinition;

EdgeList::EdgeList()
{
}

EdgeList::~EdgeList()
{
}

EdgeReference EdgeList::getEdge(KeyData key) EDGENOEXCEPT
{
    return this->edges[key];
}

void EdgeList::generateEdges()
{
    edges.clear();
    const auto countUniqueVertices = vertices.size();
    edges.reserve(countUniqueVertices);
    for (int i = 0; i < countUniqueVertices; i++)
    {
        this->edges.emplace_back(Edge());
    }

    // forall(tri, triangles)
    // {
    // 	edges[tri[0]].vertexEdges.insert(tri[1]);
    // 	edges[tri[0]].vertexEdges.insert(tri[2]);

    // 	edges[tri[1]].vertexEdges.insert(tri[0]);
    // 	edges[tri[1]].vertexEdges.insert(tri[2]);

    // 	edges[tri[2]].vertexEdges.insert(tri[0]);
    // 	edges[tri[2]].vertexEdges.insert(tri[1]);
    // }

    int nThreads = getNThreads;
    vector<thread> threads;
    for (int threadID = 0; threadID < nThreads; threadID++)
    {
        const int id = threadID;
        threads.push_back(thread([&, id]() {
            for (int vertexID = id; vertexID < countUniqueVertices; vertexID += nThreads)
            {
                foreach (tri, vertices[vertexID].triangleIDs)
                {
                    // edges[vertexID].vertexEdges.insert(triangles[tri][0]);
                    // edges[vertexID].vertexEdges.insert(triangles[tri][1]);
                    // edges[vertexID].vertexEdges.insert(triangles[tri][2]);
                    // edges[vertexID].vertexEdges.erase(vertexID);

                    if (triangles[tri][0] == vertexID)
                    {
                        edges[vertexID].vertexEdges.insert(triangles[tri][1]);
                        edges[vertexID].vertexEdges.insert(triangles[tri][2]);
                    }
                    else if (triangles[tri][1] == vertexID)
                    {
                        edges[vertexID].vertexEdges.insert(triangles[tri][0]);
                        edges[vertexID].vertexEdges.insert(triangles[tri][2]);
                    }
                    else
                    {
                        edges[vertexID].vertexEdges.insert(triangles[tri][0]);
                        edges[vertexID].vertexEdges.insert(triangles[tri][1]);
                    }
                }
            }
        }));
    }
    joinThreads;
}

void EdgeList::cleanUpEdges()
{
    const auto countofedges = edges.size();

    for (int i = 0; i < countofedges; i++)
    {
        // edges[i].cleanUp();
    }
}

void EdgeList::printAllEdges()
{
    int tracker = 0;
    const int edgeCount = (const int)edges.size();

    for (int i = 0; i < edgeCount; i++)
    {
        say "id:" spc tracker << ":";
        tracker++;
        edges[i].printEdge();
    }
}

const int EdgeListDefinition::EdgeList::edgesTotal() EDGENOEXCEPT
{
    return (const int)edges.size();
}

v4 EdgeListDefinition::EdgeList::colorAverageAt(KeyData key) EDGENOEXCEPT
{
    v4 res = v4(0);

    auto &edge = edges[key].vertexEdges;

    forall(element, edge)
    {
        res += vertices[element].color;
    }
    res /= (float)edge.size();

    return res;
}

v3 EdgeListDefinition::EdgeList::averageAt(KeyData key) EDGENOEXCEPT
{
    v3 res = v3(0);

    auto &edge = edges[key].vertexEdges;

    forall(element, edge)
    {
        res += vertices[element].position;
    }
    res /= (float)edge.size();

    return res;
}

KeyList EdgeListDefinition::EdgeList::getEdgeTriangles(EdgePair edge) EDGENOEXCEPT
{
    KeyList res;
    unordered_set<KeyData> v0Triangles(vertices[edge.first].triangleIDs.begin(),
                                       vertices[edge.first].triangleIDs.end());

    foreach (tri, vertices[edge.second].triangleIDs)
    {
        if (v0Triangles.contains(tri))
        {
            res.emplace_back(tri);
        }
    }

    return res;
}