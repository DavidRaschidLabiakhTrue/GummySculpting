#include "Octree.hpp"

using namespace OctreeDefinition;

/**
 * @brief Collect all vertices within a given range of the collision
 *
 * @param collision
 * @param range
 * @return KeyList
 */
KeyList OctreeDefinition::Octree::collectVerticesAroundCollision(OctreeCollision collision, double range) ONOEXCEPT
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
 * @brief Collects all triangles within the given range of the collision.
 * Includes triangles that have one or more vertices within the range.
 *
 * @param collision
 * @param range
 * @return TriangleIDList
 */
TriangleIDList OctreeDefinition::Octree::collectTrianglesAroundCollision(OctreeCollision collision, double range) ONOEXCEPT
{
    return getTrianglesFromVertices(collectVerticesAroundCollision(collision, range));
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
OctreeCollision OctreeDefinition::Octree::octreeRayIntersection(v3 origin, v3 direction) ONOEXCEPT
{
    // Create a new octree collision object and set distance to max float value
    OctreeCollision collision;
    collision.distance = NoCollisionDistance;

    float distance = NoCollisionDistance;

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
            float tempDistance = NoCollisionDistance; // temp distance value for intersection below

            // If the plane is intersected
            if (intersectRayPlane(
                    origin,
                    direction,
                    corner,
                    planeNormals[i],
                    tempDistance))
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
        if (distance > collision.distance || distance == NoCollisionDistance)
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
                collision.isCollision = true;
            }
        }
    }

    return collision;
}