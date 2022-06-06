#include "Octree.hpp"
using namespace OctreeDefinition;

using namespace OctantDefinition;
extern concurrency::concurrent_vector<unique_ptr<mutex>> octantMutexes;

/**
 * @brief Search octree for octant which encloses triangle. Standard Traversal.
 *
 * @param triangle
 * @return OctantIndex
 */
OctantIndex OctreeDefinition::Octree::findOctantForTriangle(TriangleID triangle) ONOEXCEPT
{
    octreeCurrentDepth = 0;                                                                                                    // Set the current depth to 0
    v3 triangleCentroid = getTriangleCentroid(triangle);                                                                       // get the triangle centroid, used for morton code
    OctantIndex currOctant = root;                                                                                             // Track the current octant index, start at root
    OctantIndex nextOctant = octants[currOctant].children[mortonCodeHash(triangleCentroid, octants[currOctant].octantCenter)]; // Calculate and track the next octant

    while (nextOctant != NoOctantChildSet && isTriangleInOctantBounds(triangle, nextOctant)) // While the next octant exists and the triangle is within its bounds
    {
        currOctant = nextOctant;                                                                                       // Set the current octant to the next octant
        nextOctant = octants[currOctant].children[mortonCodeHash(triangleCentroid, octants[currOctant].octantCenter)]; // Calculate the next octant
        octreeCurrentDepth++;                                                                                          // increment the current depth
    }
    return currOctant;
}

int OctreeDefinition::Octree::mortonCodeHash(v3 point, v3 center) ONOEXCEPT
{
    // this function is performing a safety test on point.members that are "0" on an axis.
    // Due to the nature of floating points, -0.0f is possible and less than 0.0f, so this function takes this into account and auto converts -0.0f into 0.0f if it exists so there are no errors in the MortonCode produced.
    return (MortonCodeConvert_Safe(point.x, center.x) << 2) | (MortonCodeConvert_Safe(point.y, center.y) << 1) | (MortonCodeConvert_Safe(point.z, center.z));
}

/**
 * @brief Subdivide the given octant. Adds the children to the octant and octants list.
 * Can recurse if child octant needs to subdivide.
 *
 * @param oix
 */
void OctreeDefinition::Octree::subdivideOctant(OctantIndex oix) ONOEXCEPT
{

    if (octreeCurrentDepth == octreeDepth) // Update the current depth value of the octree if subdivision increases it
    {
        octreeDepth++;
    }

    octreeCurrentDepth++; // Child octants are at the next depth of the octant being subdivided

    for (int i = 0; i < 8; i++) // Create this octants children
    {
        createChildOctant((OctantPosition)i, oix);
    }

    // // Reinsert triangles into children if they fit entirely inside
    // // Reverse order to preserve positions on removal
    // for (int i = (int)octants[oix].triangleIDs->size() - 1; i >= 0; i--)
    // {
    //     TriangleID tri = octants[oix].triangleIDs->at(i);
    //     v3 triangleCentroid = getTriangleCentroid(tri);
    //     OctantIndex childOctant = octants[oix].children[mortonCodeHash(triangleCentroid, octants[oix].octantCenter)];
    //     // If triangle fits in child octant, insert it
    //     if (isTriangleInOctantBounds(tri, childOctant))
    //     {
    //         octants[childOctant].triangleIDs->emplace_back(tri);                    // Insert triangle into child octant
    //         triangleToOctantList[tri] = childOctant;                                // Correct the triangle - octant mapping
    //         octants[oix].triangleIDs->erase(octants[oix].triangleIDs->begin() + i); // Remove triangle from the parent octant
    //     }
    // }

    // Reinsert triangles into children if they fit entirely inside
    auto ts = *(octants[oix].triangleIDs.get());
    foreach (tri, ts)
    {
        v3 triangleCentroid = getTriangleCentroid(tri);
        OctantIndex childID = octants[oix].children[mortonCodeHash(triangleCentroid, octants[oix].octantCenter)];

        // If triangle fits in child octant, insert it
        if (isTriangleInOctantBounds(tri, childID))
        {
            int temp = tri;
            octants[childID].triangleIDs->insert(temp); // Insert triangle into child octant
            triangleToOctantList[tri] = childID;        // Correct the triangle - octant mapping
            octants[oix].triangleIDs->erase(tri);       // Remove triangle from the parent octant
        }
    }

    for (int i = 0; i < 8; i++) // Subdivide any child octants if necessary
    {
        OctantIndex childOctant = octants[oix].children[i]; // Avoiding nested [] operators for clarity
        if (octreeCurrentDepth < octreeDepthLimit && octants[childOctant].triangleIDs->size() > octantTriangleLimit)
        {
            subdivideOctant(childOctant);
        }
    }

    // Set state of subdivided octant
    // Checks if octant contains any triangles ands sets state accordingly
    if (octants[oix].triangleIDs->size() == 0)
    {
        octants[oix].octantState = OctantEmptyInternal;
    }
    else
    {
        octants[oix].octantState = OctantNotEmptyInternal;
    }
    octreeCurrentDepth--;
}

/**
 * @brief Creates a child octant for the octant at the given index.
 * Adds the child to the octant list.
 * Adjusts the center and halfsize of the child octant according to the looseness of the octree.
 *
 * NOTE: Can be optimized by calculating the unadjusted and loose halfsizes before hand since
 * those are shared between all children of an octant.
 *
 * @param octantPosition
 * @param parentIndex
 */
void OctreeDefinition::Octree::createChildOctant(OctantPosition octantPosition, OctantIndex parentIndex) ONOEXCEPT
{
    Octant childOctant;                                  // Empty octant
    OctantReference parentOctant = octants[parentIndex]; // Get the parent octant reference

    float unadjustedHalfSize = parentOctant.octantHalfSize / 2.0f;     // Unadjusted half size for child octant
    float looseHalfSize = (float)octreeLooseness * unadjustedHalfSize; // Looseness adjusted half size for child octant
    float halfSizeDifference = looseHalfSize - unadjustedHalfSize;     // Difference between the two half sizes

    v3 positionVector = octantPositionVectors[(int)octantPosition]; // Position vector for child octant

    // Unadjusted child center, based on parent center and unadjusted half size
    v3 unadjustedChildCenter = parentOctant.octantCenter + v3(unadjustedHalfSize) * positionVector;

    // Set child center, adjusted for looseness
    // Subtraction used to reverse direction of position vector
    // Moves the child's center towards the parent's center based on the half size difference
    childOctant.octantCenter = unadjustedChildCenter - v3(halfSizeDifference) * positionVector;
    childOctant.octantHalfSize = looseHalfSize;    // Set half size of child octant, adjusted for looseness
    childOctant.octantIndex = (int)octants.size(); // Set octants index to the next available index
    childOctant.parent = parentIndex;              // Set parent of child octant

    // Set the parent's child at the octant position to the child's index in the octants vector
    parentOctant.children[(int)octantPosition] = childOctant.octantIndex;

    octants.push_back(childOctant); // Add child octant to octants list
    octantMutexes.push_back(make_unique<mutex>());
}

/**
 * @brief Checks if each vertex of the triangle is within the octant's bounds
 *
 * @param tri
 * @param octantID
 * @return true
 * @return false
 */
bool OctreeDefinition::Octree::isTriangleInOctantBounds(TriangleID tri, OctantIndex octantID) ONOEXCEPT
{
    // Octant oct = octants[octantID];                                                     // retrieve the current processed octant
    IndexedTriangle triangle = triangles[tri];                                                        // retrieve the current processed triangle
    v3 halfSizeVector = v3(octants[octantID].octantHalfSize + std::numeric_limits<float>::epsilon()); // Half size vec3 for comparison

    // Component-wiser check if the difference between each vertex and the octant's center is less than the octant's half size
    return all(lessThanEqual(abs(octants[octantID].octantCenter - vertices[triangle[0]].position), halfSizeVector)) &&
           all(lessThanEqual(abs(octants[octantID].octantCenter - vertices[triangle[1]].position), halfSizeVector)) &&
           all(lessThanEqual(abs(octants[octantID].octantCenter - vertices[triangle[2]].position), halfSizeVector));
}

// Parallel Functions
mutex mtxOctants;
mutex mtxDepth;
void OctreeDefinition::Octree::subdivideOctantParallel(OctantIndex oix, int localDepth) ONOEXCEPT
{
    mtxDepth.lock();
    if (localDepth == octreeDepth) // Update the current depth value of the octree if subdivision increases it
    {
        octreeDepth++;
    }
    mtxDepth.unlock();

    localDepth++;
    vector<int> children;
    children.reserve(8);
    for (int i = 0; i < 8; i++) // Create this octants children
    {
        children.push_back(createChildOctantParallel((OctantPosition)i, oix));
    }

    // // Reinsert triangles into children if they fit entirely inside
    // // Reverse order to preserve positions on removal
    // for (int i = (int)octants[oix].triangleIDs->size() - 1; i >= 0; i--)
    // {
    //     TriangleID tri = octants[oix].triangleIDs->at(i);
    //     v3 triangleCentroid = getTriangleCentroid(tri);
    //     OctantIndex childID = children[mortonCodeHash(triangleCentroid, octants[oix].octantCenter)];

    //     // If triangle fits in child octant, insert it
    //     if (isTriangleInOctantBounds(tri, childID))
    //     {
    //         octants[childID].triangleIDs->emplace_back(tri);                       // Insert triangle into child octant
    //         triangleToOctantList[tri] = childID;                                  // Correct the triangle - octant mapping
    //         octants[oix].triangleIDs->erase(octants[oix].triangleIDs->begin() + i); // Remove triangle from the parent octant
    //     }
    // }

    // Reinsert triangles into children if they fit entirely inside
    auto ts = *(octants[oix].triangleIDs.get());
    foreach (tri, ts)
    {
        v3 triangleCentroid = getTriangleCentroid(tri);
        OctantIndex childID = children[mortonCodeHash(triangleCentroid, octants[oix].octantCenter)];

        // If triangle fits in child octant, insert it
        if (isTriangleInOctantBounds(tri, childID))
        {
            int temp = tri;
            octants[childID].triangleIDs->insert(temp); // Insert triangle into child octant
            triangleToOctantList[tri] = childID;        // Correct the triangle - octant mapping
            octants[oix].triangleIDs->erase(tri);       // Remove triangle from the parent octant
        }
    }

    for (int i = 0; i < 8; i++) // Subdivide any child octants if necessary
    {
        OctantIndex childID = children[i]; // Avoiding nested [] operators for clarity

        if (localDepth < octreeDepthLimit && octants[childID].triangleIDs->size() > octantTriangleLimit)
        {
            subdivideOctantParallel(childID, localDepth);
        }
        // octantMutexes[childOctant]->unlock();
    }

    // Set state of subdivided octant
    // Checks if octant contains any triangles ands sets state accordingly
    if (octants[oix].triangleIDs->size() == 0)
    {
        octants[oix].octantState = OctantEmptyInternal;
    }
    else
    {
        octants[oix].octantState = OctantNotEmptyInternal;
    }

    octants[oix].children = children;
}

// WARNING: CHILD OCTANTS ARE LOCKED WHEN CREATED
OctantIndex OctreeDefinition::Octree::createChildOctantParallel(OctantPosition octantPosition, OctantIndex parentIndex) ONOEXCEPT
{
    Octant childOctant;                         // Empty octant
    Octant parentOctant = octants[parentIndex]; // Get the parent octant reference

    float unadjustedHalfSize = parentOctant.octantHalfSize / 2.0f;     // Unadjusted half size for child octant
    float looseHalfSize = (float)octreeLooseness * unadjustedHalfSize; // Looseness adjusted half size for child octant
    float halfSizeDifference = looseHalfSize - unadjustedHalfSize;     // Difference between the two half sizes

    v3 positionVector = octantPositionVectors[(int)octantPosition]; // Position vector for child octant

    // Unadjusted child center, based on parent center and unadjusted half size
    v3 unadjustedChildCenter = parentOctant.octantCenter + v3(unadjustedHalfSize) * positionVector;

    // Set child center, adjusted for looseness
    // Subtraction used to reverse direction of position vector
    // Moves the child's center towards the parent's center based on the half size difference
    childOctant.octantCenter = unadjustedChildCenter - v3(halfSizeDifference) * positionVector;
    childOctant.octantHalfSize = looseHalfSize; // Set half size of child octant, adjusted for looseness
    childOctant.parent = parentIndex;           // Set parent of child octant

    // Insert child into octants vector and lock it before adding to the parent
    OctantIndex childIndex = insertOctantParallel(childOctant);
    // octantMutexes[childIndex]->lock();

    // set the parent's child at the octant position to the child's index in the octants vector
    // octants[parentIndex].children[(int)octantPosition] = childIndex;
    return childIndex;
}

OctantIndex Octree::insertOctantParallel(OctantReference octant) ONOEXCEPT
{
    lock_guard<mutex> lock(mtxOctants);
    OctantIndex octantIndex = (OctantIndex)octants.size();
    octant.octantIndex = octantIndex;
    octants.push_back(octant);
    octantMutexes.push_back(make_unique<mutex>());
    // auto octantIter = octants.push_back(octant);
    // OctantIndex octantIndex = (OctantIndex)(octantIter - octants.begin());
    // octant.octantIndex = octantIndex;
    return octantIndex;
}

pair<OctantIndex, int> OctreeDefinition::Octree::findOctantForTriangleParallel(TriangleID triangle, OctantIndex start) ONOEXCEPT
{
    int localDepth = 0;
    v3 triangleCentroid = getTriangleCentroid(triangle);
    OctantIndex currOctant = start;
    OctantIndex nextOctant = octants[currOctant].children[mortonCodeHash(triangleCentroid, octants[currOctant].octantCenter)];

    while (nextOctant != NoOctantChildSet && isTriangleInOctantBounds(triangle, nextOctant))
    {
        currOctant = nextOctant;
        nextOctant = octants[currOctant].children[mortonCodeHash(triangleCentroid, octants[currOctant].octantCenter)];
        localDepth++;
    }

    return make_pair(currOctant, localDepth);
}