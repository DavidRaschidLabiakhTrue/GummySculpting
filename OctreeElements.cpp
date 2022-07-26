#include "Octree.hpp"
using namespace OctreeDefinition;
extern concurrency::concurrent_vector<unique_ptr<mutex>> octantMutexes;
/**
 * @brief Insert triangle into octree, using the triangleID. Corrects state and subdivides if necessary.
 *
 * @param tri
 * @return true
 * @return false
 */
bool OctreeDefinition::Octree::insertTriangle(TriangleID tri) ONOEXCEPT
{
    // expand triangletooctantlist to match the number of triangles
    if (tri >= triangleToOctantList.size())
    {
        int diff = tri - triangleToOctantList.size();
        for (int i = 0; i <= diff; i++)
        {
            triangleToOctantList.push_back(NonExistentOctantIndex);
        }
    }

    // fuck it, just use the parallel version. don't wanna rewrite this.
    return insertTriangleParallel(tri);
}

/**
 * @brief Remove triangle from octree
 *
 * @param tri
 * @return true
 * @return false
 */
bool OctreeDefinition::Octree::removeTriangleFromOctree(TriangleID tri) ONOEXCEPT
{
    // Get octant that triangle is in
    OctantIndex oix = triangleToOctantList[tri];

    // If triangle is not in an octant, return false
    if (oix == NonExistentOctantIndex)
    {
        return false;
    }

    OctantReference octantRef = octants[oix]; // Get the octant reference for clarity

    const int triangleIDsSize = (int)octantRef.triangleIDs->size();

    if (octants[oix].triangleIDs->find(tri) != octants[oix].triangleIDs->end())
    {
        octants[oix].triangleIDs->erase(tri);
    }

    return false; // Triangle was not found in the octant
}

void Octree::updateAffectedTriangles()
{
    updateAffectedTrianglesParallel(); // testing
}

// Parallel Functions
/**
 * @brief Insert triangle into octree, using the triangleID. Corrects state and subdivides if necessary.
 *
 * @param tri
 * @return true
 * @return false
 */
bool OctreeDefinition::Octree::insertTriangleParallel(TriangleID tri) ONOEXCEPT
{
    // Check if the triangle is in the octree
    if (!Octree::isTriangleInOctantBounds(tri, root))
    {
        resizeOctreeParallel(tri);
    }
    OctantIndex oix = root;

    // Loop until the triangle is inserted into the correct octant
    while (true)
    {
        pair<OctantIndex, int> foundPair = findOctantForTriangleParallel(tri, oix); // Find the octant which encloses the triangle
        oix = foundPair.first;                                                      // Get the octant index
        int localDepth = foundPair.second;                                          // Get the local depth of the octant
        octantMutexes[oix]->lock();

        // Validate the octant
        if (octants[oix].octantState != OctantLeaf)
        {
            OctantIndex newOix = findOctantForTriangleParallel(tri, oix).first;
            if (newOix != oix)
            {
                octantMutexes[oix]->unlock();
                oix = newOix;
                continue;
            }
        }

        // OctantReference octant = octants[oix]; // Get the octant reference
        octants[oix].triangleIDs->emplace(tri); // Add the triangle to the octant's triangle list
        triangleToOctantList[tri] = oix;        // Set triangle's octant index to the new octant index

        // If octant is internal and empty, change state to not empty internal
        if (octants[oix].octantState == OctantEmptyInternal)
        {
            octants[oix].octantState = OctantNotEmptyInternal;
        }
        // Else If octant is a leaf, check depth and subdivide if # of triangles held exceeds limit
        else if (octants[oix].octantState == OctantLeaf &&
                 localDepth < octreeDepthLimit &&
                 octants[oix].triangleIDs->size() > octantTriangleLimit)
        {
            subdivideOctantParallel(oix, localDepth);
        }

        octantMutexes[oix]->unlock();
        return true;
    }
}

bool Octree::insertTrianglesParallel() ONOEXCEPT
{
    int nThreads = std::thread::hardware_concurrency();

    if (nThreads == 0)
    {
        nThreads = 1;
    }

    int triangleCount = totalTriangles();
    vector<thread> threads;
    for (int i = 0; i < nThreads; i++)
    {
        int id = i;
        // I'm doin lambda functions, what're you gonna do about it?
        threads.push_back(thread([&, id]() {
            for (int j = id; j < triangleCount; j += nThreads)
            {
                insertTriangleParallel(j);
            }
        }));
    }

    foreach (t, threads)
    {
        t.join();
    }
    return true;
}

void OctreeDefinition::Octree::octreeReinsertTrianglesParallel() ONOEXCEPT
{
    // TriangleOctantKeyPairList::loadTriangleOctantKeyPairList();
    loadTriangleOctantList();
    foreach (octant, octants)
    {
        octant.triangleIDs->clear();
    }

    insertTrianglesParallel();
}

bool Octree::updateTriangleInOctreeParallel(TriangleID tri) ONOEXCEPT
{
    if (removeTriangleFromOctreeParallel(tri))
    {
        insertTriangleParallel(tri);
        return true;
    }
    return false;
}

bool Octree::updateTrianglesInOctreeParallel(TriangleIDList tris) ONOEXCEPT
{
    int nTris = (int)tris.size();
    if (nTris == 0)
    {
        return true;
    }

    int nThreads = getNThreads;
    vector<thread> threads;
    vector<bool> updateSuccessfulList;
    for (int i = 0; i < nThreads; i++)
    {
        updateSuccessfulList.push_back(true);
        int id = i;
        threads.push_back(thread([&, id]() {
            for (int j = id; j < nTris; j += nThreads)
            {
                updateSuccessfulList[id] = updateSuccessfulList[id] && updateTriangleInOctreeParallel(tris[j]);
            }
        }));
    }
    joinThreads;

    return all_of(updateSuccessfulList.begin(), updateSuccessfulList.end(), [](bool b) { return b; });
}

bool Octree::removeTriangleFromOctreeParallel(TriangleID tri) ONOEXCEPT
{
    // Get octant that triangle is in
    OctantIndex oix = triangleToOctantList[tri];

    // If triangle is not in an octant, return false
    if (oix == NonExistentOctantIndex || oix >= octants.size())
    {
        return false;
    }

    lock_guard<mutex> lock(*octantMutexes[oix]);

    if (octants[oix].triangleIDs->find(tri) != octants[oix].triangleIDs->end())
    {
        octants[oix].triangleIDs->erase(tri);
        return true;
    }

    return false; // Triangle was not found in the octant
}

void Octree::updateAffectedTrianglesParallel() ONOEXCEPT
{
    updateTrianglesInOctreeParallel(affectedTriangles);
    clearCollision();
}

void Octree::clearCollision() ONOEXCEPT
{
    collision = OctreeCollision();
    verticesInRange.clear();
    trianglesInRange.clear();
    affectedTriangles.clear();

    reflectedCollision = OctreeCollision();
    reflectedVerticesInRange.clear();
    reflectedTrianglesInRange.clear();
}