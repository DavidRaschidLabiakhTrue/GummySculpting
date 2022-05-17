#include "Octree.hpp"

#include "VertexIDHashing.hpp"

using namespace OctreeDefinition;
using namespace VertexIDHashingDefinition;

OctreeDefinition::Octree::Octree()
{
}

OctreeDefinition::Octree::~Octree()
{
}

/**
 * @brief Print octree information for debugging.
 */
void OctreeDefinition::Octree::octreePrintStats()
{
    say "Octree Debug" done;
    say "\tPoint Limit:" spc octantTriangleLimit done;
    say "\tDepth Limit:" spc octreeDepthLimit done;
    say "\tDepth:" spc octreeDepth done;
    // say "\tPoints: " << points.size() done; - need to reimplement
    say "\tEdges:" spc edgesTotal() done;
    say "\tTriangles:" spc totalTriangles() done;
    say "\tOctants:" spc octants.size() done;
    say "\tLeaves:" spc leaves.size() done;

    say "\tCenter:" spc to_string(octants[root].octantCenter) done;
    say "\tHalfsize:" spc octants[root].octantHalfSize done;
    say "\tTriangles in Root:" spc octants[root].triangleIDs.size() done;

    int count = 0;
    int owt = 0;
    int tip = 0;
    foreach (o, octants)
    {
        if (o.octantState)
        {
            count++;
        }

        if (o.triangleIDs.size())
        {
            owt++;
            if (o.octantState == OctantState::OctantNotEmptyInternal) // this really needs to be enumerated to say what is going on.
            {
                tip++;
            }
        }
    }

    say "\tActive Octants:" spc count done;
    say "\tOctants with Triangles:" spc owt done;
    say "\tPsuedo-Leaves w/ Traingles:" spc tip done;

    // Not implementing for now.
    /*
    say "Octree Mesh:" done;
    say "\tVertices: " << octreeVertices.size() done;
    say "\tIndices: " << octreeIndices.size() done;
    */
}

/**
 * @brief Collect all vertices within a given range of the collision
 *
 * @param collision
 * @param range
 * @return KeyList
 */
KeyList OctreeDefinition::Octree::collect(OctreeCollision &collision, double range)
{
    KeyList results; // list of keys returned from collecting method

    std::unordered_set<KeyData, point_hash, point_equal> unchecked; // List of vertices to check if they're within range
    std::unordered_set<KeyData, point_hash, point_equal> checked;   // Every vertex that has been checked

    // Prime the unchecked set with the triangle vertices
    unchecked.insert(triangles[collision.triangleID][0]);
    unchecked.insert(triangles[collision.triangleID][1]);
    unchecked.insert(triangles[collision.triangleID][2]);

    // While there are still unchecked vertices
    while (!unchecked.empty())
    {
        // Copy and move the first element of the unchecked set to checked
        KeyData element = *unchecked.begin();
        unchecked.erase(unchecked.begin());
        checked.insert(element);

        // Check distance between the collision and the element
        if (distance(vertices[element].position, collision.position) <= range)
        {
            results.emplace_back(element); // Add the element to the results list

            // Add each vertex that is connected by an edge to this vertex
            // and has not already been checked.
            // Using unordered set allows us to insert into unchecked whether or not it already exists.
            foreach (vertex, edges[element].vertexEdges)
            {
                if (!checked.contains(vertex))
                {
                    unchecked.insert(vertex);
                }
            }
        }
    }

    return results;
}

/**
 * @brief Build the octree by inserting all triangles of the mesh into the octree.
 * Initializes the root octant.
 */
void OctreeDefinition::Octree::buildOctree()
{
    TriangleOctantKeyPairList::loadTriangleOctantKeyPairList();

    // Adjust the extents of the mesh vertices wrt the center
    float maxExtent = compMax(abs(this->center - limMax));
    float minExtent = compMin(abs(this->center - limMin));

    // Create root octant with appropriate center and half size
    Octant rootOctant;
    rootOctant.octantIndex = 0;
    rootOctant.octantCenter = this->center;
    rootOctant.octantHalfSize = glm::max(maxExtent, minExtent);
    octants.emplace_back(rootOctant);

    // Insert all triangles into the octree
    int triangleCount = totalTriangles();
    for (int i = 0; i < triangleCount; i++)
    {
        Octree::insertTriangle(i);
    }
}

/**
 * @brief Search octree for octant which encloses triangle. Standard Traversal.
 *
 * @param triangle
 * @return OctantIndex
 */
OctantIndex OctreeDefinition::Octree::findOctantForTriangle(TriangleID triangle)
{
    octreeCurrentDepth = 0;                              // Set the current depth to 0
    v3 triangleCentroid = getTriangleCentroid(triangle); // get the triangle centroid, used for morton code
    OctantIndex currOctant = root;                       // Track the current octant index, start at root

    // Calculate and track the next octant
    OctantIndex nextOctant = octants[currOctant].children[mortonCodeHash(triangleCentroid, octants[currOctant].octantCenter)];

    // While the next octant exists and the triangle is within its bounds
    while (nextOctant != NoOctantChildSet && isTriangleInOctantBounds(triangle, nextOctant))
    {
        // Set the current octant to the next octant
        currOctant = nextOctant;

        // Calculate the next octant
        nextOctant = octants[currOctant].children[mortonCodeHash(triangleCentroid, octants[currOctant].octantCenter)];

        // increment the current depth
        octreeCurrentDepth++;
    }

    return currOctant;
}

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
 * @brief Subdivide the given octant. Adds the children to the octant and octants list.
 * Can recurse if child octant needs to subdivide.
 *
 * @param oix
 */
void OctreeDefinition::Octree::subdivideOctant(OctantIndex oix)
{
    OctantReference octant = octants[oix];

    // Update the current depth value of the octree if subdivision increases it
    if (octreeCurrentDepth == octreeDepth)
    {
        octreeDepth++;
    }

    octreeCurrentDepth++; // Child octants are at the next depth of the octant being subdivided

    // Create this octants children
    for (int i = 0; i < 8; i++)
    {
        createChildOctant((OctantPosition)i, oix);
    }

    // Reinsert triangles into children if they fit entirely inside
    // Reverse order to preserve positions on removal
    for (int i = octant.triangleIDs.size(); i >= 0; i--)
    {
        TriangleID tri = octant.triangleIDs[i];
        v3 triangleCentroid = getTriangleCentroid(tri);
        OctantIndex childOctant = octant.children[mortonCodeHash(triangleCentroid, octant.octantCenter)];

        // If triangle fits in child octant, insert it
        if (isTriangleInOctantBounds(tri, childOctant))
        {
            octants[childOctant].triangleIDs.emplace_back(tri);
            octant.triangleIDs.erase(octant.triangleIDs.begin() + i);
        }
    }

    // Subdivide any child octants if necessary
    for (int i = 0; i < 8; i++)
    {
        OctantIndex childOctant = octant.children[i]; // Avoiding nested [] operators for clarity
        if (octreeCurrentDepth < octreeDepthLimit && octants[childOctant].triangleIDs.size() > octantTriangleLimit)
        {
            subdivideOctant(childOctant);
        }
    }

    // Set state of subdivided octant
    // Checks if octant contains any triangles ands sets state accordingly
    if (octant.triangleIDs.size() == 0)
    {
        octant.octantState = OctantEmptyInternal;
    }
    else
    {
        octant.octantState = OctantNotEmptyInternal;
    }
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
void OctreeDefinition::Octree::createChildOctant(OctantPosition octantPosition, OctantIndex parentIndex)
{
    Octant childOctant;                                  // Empty octant
    OctantReference parentOctant = octants[parentIndex]; // Get the parent octant reference

    float unadjustedHalfSize = parentOctant.octantHalfSize / 2.0f; // Unadjusted half size for child octant
    float looseHalfSize = octreeLooseness * unadjustedHalfSize;    // Looseness adjusted half size for child octant
    float halfSizeDifference = looseHalfSize - unadjustedHalfSize; // Difference between the two half sizes

    v3 positionVector = octantPositionVectors[octantPosition]; // Position vector for child octant

    // Unadjusted child center, based on parent center and unadjusted half size
    v3 unadjustedChildCenter = parentOctant.octantCenter + v3(unadjustedHalfSize) * positionVector;

    // Set child center, adjusted for looseness
    // Subtraction used to reverse direction of position vector
    // Moves the child's center towards the parent's center based on the half size difference
    childOctant.octantCenter = unadjustedChildCenter - v3(halfSizeDifference) * positionVector;
    childOctant.octantHalfSize = looseHalfSize; // Set half size of child octant, adjusted for looseness
    childOctant.octantIndex = octants.size();   // Set octants index to the next available index
    childOctant.parent = parentIndex;           // Set parent of child octant

    // Set the parent's child at the octant position to the child's index in the octants vector
    parentOctant.children[octantPosition] = childOctant.octantIndex;

    octants.emplace_back(childOctant); // Add child octant to octants list
}

/**
 * @brief Checks if each vertex of the triangle is within the octant's bounds
 *
 * @param tri
 * @param octantID
 * @return true
 * @return false
 */
bool OctreeDefinition::Octree::isTriangleInOctantBounds(TriangleID tri, OctantIndex octantID)
{
    OctantReference oct = octants[octantID];                                            // retrieve the current processed octant
    IndexedTriangle triangle = triangles[tri];                                          // retrieve the current processed triangle
    v3 halfSizeVector = v3(oct.octantHalfSize + std::numeric_limits<float>::epsilon()); // Half size vec3 for comparison

    // Component-wiser check if the difference between each vertex and the octant's center is less than the octant's half size
    return all(lessThanEqual(abs(oct.octantCenter - vertices[triangle[0]].position), halfSizeVector)) &&
           all(lessThanEqual(abs(oct.octantCenter - vertices[triangle[1]].position), halfSizeVector)) &&
           all(lessThanEqual(abs(oct.octantCenter - vertices[triangle[2]].position), halfSizeVector));
}

/**
 * @brief Resize octree to fit the given triangle by creating a new root
 * octant and placing the old root as a child
 *
 * @param tri
 */
void OctreeDefinition::Octree::resizeOctree(TriangleID tri)
{
    // If the depth limit is currently reached, increase limit to allow resizing
    if(octreeDepth == octreeDepthLimit) {
        octreeDepth++;
        octreeDepthLimit++;
    }

    v3 triangleCentroid = getTriangleCentroid(tri); // Get the triangle's centroid

    // Continuously resize until triangle fits into the root octant
    while (!isTriangleInOctantBounds(tri, root))
    {
        OctantReference oldRoot = octants[root]; // Save oldRoot to replace one of the new root's children

        // Get morton code of triangle centroid to determine direction to grow octree
        OctantPosition newRootDirection = (OctantPosition)mortonCodeHash(triangleCentroid, oldRoot.octantCenter);
        v3 newRootPositionVector = octantPositionVectors[newRootDirection]; // Vector from old root to new root

        // Adjusted halfsize removing looseness
        // New Root's halfsize, already loose no need for adjustment
        float oldRootAdjustedHalfSize = (oldRoot.octantHalfSize / (1 + octreeLooseness));
        float newRootHalfsize = oldRootAdjustedHalfSize * 2;

        // Adjusted old root center, based on old root's center and adjusted half size
        // New Root's Center based on old root's center and adjusted half size
        v3 oldRootAdjustedCenter = oldRoot.octantCenter - newRootPositionVector * (oldRoot.octantHalfSize - oldRootAdjustedHalfSize);
        v3 newRootCenter = oldRootAdjustedCenter + newRootPositionVector * oldRootAdjustedHalfSize;

        // Create new root octant, set its values accordingly
        Octant newRoot;
        newRoot.octantState = OctantEmptyInternal;
        newRoot.octantHalfSize = newRootHalfsize;
        newRoot.octantCenter = newRootCenter;
        newRoot.octantIndex = root;
        octants[root] = newRoot;

        // Subdivide the new root to add missing child octants
        subdivideOctant(root);

        oldRoot.parent = root; // Set the old root's parent to the new root

        // Get the position where the old root will reside in the new root's children
        // Then get the index of child to replace
        // Then replace octant at the index with the old root
        OctantPosition oldRootNewPosition = (OctantPosition)mortonCodeHash(oldRootAdjustedCenter, newRootCenter);
        OctantIndex oldRootNewIndex = octants[root].children[oldRootNewPosition];
        octants[oldRootNewIndex] = oldRoot;

        // Adjust the parent values of the old roots children to point to its new index
        if (oldRoot.octantState != OctantLeaf)
        {
            foreach (child, oldRoot.children)
            {
                octants[oldRoot.children[child]].parent = oldRootNewIndex;
            }
        }
    }
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

/**
 * @brief Tests every octant that has triangles for intersection with the given ray.
 * Skips octants that do not have triangles.
 * Written to be easily parallelizable if needed, also avoids handling loose bounds.
 *
 * @param origin
 * @param direction
 * @return OctreeCollision
 */
OctreeCollision OctreeDefinition::Octree::octreeRayIntersection(v3 origin, v3 direction)
{
    // Create a new octree collision object and set distance to max float value
    OctreeCollision collision;
    collision.distance = std::numeric_limits<float>::max();

    float distance = std::numeric_limits<float>::max();

    foreach (octant, octants)
    {
        // If octant has no triangles, continue
        if (octant.octantState == OctantEmptyInternal || octant.triangleIDs.size() == 0)
        {
            continue;
        }

        // Get nearest corner of octant
        // Uses the morton code to determine which corner is nearest and gets the corresponding vector
        // Then calculates the position of the corner
        v3 originDirectionVector = octantPositionVectors[mortonCodeHash(origin, octant.octantCenter)];
        v3 corner = octant.octantCenter + originDirectionVector * octant.octantHalfSize;

        // Calculate the intersection of the ray with each face of the octant
        // TODO: Should have better naming for vector components
        for (int i = 0; i < 3; i++)
        {
            float tempDistance = std::numeric_limits<float>::max(); // temp distance value for intersection below

            // If the plane is intersected
            if (intersectRayPlane(origin, direction, corner, planeNormals[i], tempDistance))
            {
                v3 point = origin + direction * tempDistance; // Calculate the intersection point
                int j = (i + 2) % 3;                          // Determine the second component of the plane to test

                // Check if the intersection point is within the octant's face
                // and if the distance is closer than the current recorded distance
                if (abs(octant.octantCenter[i] - point[i]) <= octant.octantHalfSize &&
                    abs(octant.octantCenter[j] - point[j]) <= octant.octantHalfSize &&
                    tempDistance < distance)
                {
                    distance = tempDistance; // Set the current distance to the new distance
                }
            }
        }

        // Skip octant if intersect distance is greater than current collision or there is no intersection
        if (distance > collision.distance || distance == std::numeric_limits<float>::max())
        {
            continue;
        }

        // Checks each triangle in the octant for collision with the ray
        // Records the closest collision, replacing the current collision when necessary
        foreach (tri, octant.triangleIDs)
        {
            IndexedTriangle triangle = triangles[tri]; // Indexed triangle for clarity
            v2 unusedBaryPosition;                     // Unused variable to pass into the intersection function

            // If the ray intersects the triangle and the distance is less than the current collision,
            // update the collision with the new intersected triangle, distance, and position
            // Long ass function call formatted wierdly to make it easier to read
            if (intersectRayTriangle(
                    origin,
                    direction,
                    vertices[triangle[0]].position,
                    vertices[triangle[1]].position,
                    vertices[triangle[2]].position,
                    unusedBaryPosition,
                    distance) &&
                distance < collision.distance)
            {
                collision.triangleID = tri;
                collision.distance = distance;
                collision.position = origin + direction * distance;
            }
        }
    }

    return collision;
}
