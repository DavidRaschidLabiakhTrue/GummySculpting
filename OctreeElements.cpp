#include "Octree.hpp"
using namespace OctreeDefinition;

/**
 * @brief Insert triangle into octree, using the triangleID. Corrects state and subdivides if necessary.
 *
 * @param tri
 * @return true
 * @return false
 */
bool OctreeDefinition::Octree::insertTriangle(TriangleID tri)
{
    // Check if the triangle is in the octree
    if (!Octree::isTriangleInOctantBounds(tri, root))
    {
        resizeOctree(tri);
    }

    OctantIndex oix = findOctantForTriangle(tri); // Find the octant which encloses the triangle
    OctantReference octant = octants[oix];        // Get the octant reference
    octant.triangleIDs.emplace_back(tri);         // Add the triangle to the octant's triangle list
    triangleToOctantList[tri].octantIndex = oix;  // Set triangle's octant index to the new octant index

    // If octant is internal and empty, change state to not empty internal
    if (octant.octantState == OctantEmptyInternal)
    {
        octant.octantState = OctantNotEmptyInternal;
        // TODO: Add octant to NotEmptyOctantList?
    }

    // Else If octant is a leaf, check depth and subdivide if # of triangles held exceeds limit
    else if (octant.octantState == OctantLeaf && octreeCurrentDepth < octreeDepthLimit && octant.triangleIDs.size() > octantTriangleLimit)
    {
        subdivideOctant(oix);
    }

    return true;
}

/**
 * @brief Remove triangle from octree
 *
 * @param tri
 * @return true
 * @return false
 */
bool OctreeDefinition::Octree::removeTriangleFromOctree(TriangleID tri)
{
    // Get octant that triangle is in
    OctantIndex oix = triangleToOctantList[tri].octantIndex;

    // If triangle is not in an octant, return false
    if (oix == NonExistentOctantIndex)
    {
        return false;
    }

    OctantReference octantRef = octants[oix]; // Get the octant reference for clarity

    // Search through the octants triangle list for the triangle
    for (int i = 0; i < octantRef.triangleIDs.size(); i++)
    {
        // If the triangle was found, remove it from the octant's list and return true
        if (octantRef.triangleIDs[i] == tri)
        {
            octantRef.triangleIDs.erase(octantRef.triangleIDs.begin() + i);
            return true;
        }
    }

    return false; // Triangle was not found in the octant
}

/**
 * @brief Remove triangle from octree and reinsert it
 * Remove is O(1) due to saving the triangles' octant
 * Reinsertion is O(log n)? due to standard octree traversal
 *
 * @param tri
 * @return true
 * @return false
 */
bool OctreeDefinition::Octree::updateTriangleInOctree(TriangleID tri)
{
    if (removeTriangleFromOctree(tri))
    {
        insertTriangle(tri);
        return true;
    }
    return false;
}

/**
 * @brief Updates a list of triangles in the octree.
 * Returns false if any update has failed, but continues to update the list.
 *
 * @param tris
 * @return true
 * @return false
 */
bool OctreeDefinition::Octree::updateTrianglesInOctree(TriangleIDList tris)
{
    bool updateSuccessful = true;
    foreach (tri, tris)
    {
        updateSuccessful = updateSuccessful && updateTriangleInOctree(tri);
    }
    return updateSuccessful;
}