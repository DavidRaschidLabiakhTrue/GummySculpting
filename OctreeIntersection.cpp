#include "Octree.hpp"

using namespace OctreeDefinition;

/**
 * @brief Collect all vertices within a given range of the collision
 *
 * @param collision
 * @param range
 * @return KeyList
 */
KeyList OctreeDefinition::Octree::collectVerticesAroundCollisionOriginal(OctreeCollision collision, float range) ONOEXCEPT
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
        if (abs(distance(vertices[element].position, collision.position)) <= range)
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

void Octree::collectVerticesAroundCollision(float range) ONOEXCEPT
{

    // collectVerticesAroundCollisionParallel(range);
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

    verticesInRange = results;
    affectedTriangles = getTrianglesFromVertices(verticesInRange);
}

/**
 * @brief Collects all triangles within the given range of the collision.
 * Includes triangles that have one or more vertices within the range.
 *
 * @param collision
 * @param range
 * @return pair<TriangleIDList, TriangleIDList>
 */
void OctreeDefinition::Octree::collectTrianglesAroundCollision(float range) ONOEXCEPT
{
    collectVerticesAroundCollision(range);

    TriangleIDList tempAffectedTriangles = affectedTriangles;
    TriangleIDList tempTrianglesInRange;

    foreach (tri, tempAffectedTriangles)
    {
        if (abs(distance(vertices[triangles[tri][0]].position, collision.position)) <= range &&
            abs(distance(vertices[triangles[tri][1]].position, collision.position)) <= range &&
            abs(distance(vertices[triangles[tri][2]].position, collision.position)) <= range)
        {
            tempTrianglesInRange.emplace_back(tri);
        }
    }

    trianglesInRange = tempTrianglesInRange; // this is copying twice.
}

/**
 * @brief Collects all triangles within the given range of the collision.
 * Includes triangles that have one or more vertices within the range.
 *
 * @param collision
 * @param range
 * @return TriangleIDList
 */
TriangleIDList OctreeDefinition::Octree::collectTrianglesAroundCollisionOriginal(OctreeCollision collision, float range) ONOEXCEPT
{
    return getTrianglesFromVertices(collectVerticesAroundCollisionOriginal(collision, range));
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
OctreeCollision OctreeDefinition::Octree::octreeRayIntersectionOriginal(v3 origin, v3 direction) ONOEXCEPT
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    // Create a new octree collision object and set distance to max float value
    OctreeCollision collision;
    collision.distance = NoCollisionDistance;

    foreach (octant, octants)
    {
        float distance = NoCollisionDistance;
        // If octant has no triangles, continue
        if (octant.octantState == OctantEmptyInternal || octant.triangleIDs->size() == 0)
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
        foreach (tri, *(octant.triangleIDs))
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

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    say "Intersection elapsed time: " << elapsed_seconds.count() << "s" done;
    return collision;
}

void Octree::octreeRayIntersectionCore(v3 origin, v3 direction, OctreeCollision &collisionRef) ONOEXCEPT
{
    // Correct ray for model matrix
    origin = (v3)(v4(origin, 1.0) * model);
    direction = normalize((v3)(v4(direction, 1.0) * model));

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> queue;
    OctreeCollision newCollision;
    float octantCollisionDistance = NoCollisionDistance;
    float triangleCollisionDistance = NoCollisionDistance;

    // debug
    foreach (octant, octants)
    {
        octant.intersected = false;
    }

    queue.push(make_pair(NoCollisionDistance, root));

    while (!queue.empty())
    {

        float octantDistance = queue.top().first;
        int octantID = queue.top().second;
        OctantReference octant = octants[octantID];
        queue.pop();

        // Checks each triangle in the octant for collision with the ray
        // Records the closest collision, replacing the current collision when necessary
        foreach (tri, *(octant.triangleIDs))
        {
            IndexedTriangle triangle = triangles[tri]; // Indexed triangle for clarity
            float tempDistance;
            v2 unusedBaryPosition; // Unused variable to pass into the intersection function

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
                    tempDistance) &&
                tempDistance < triangleCollisionDistance)
            {
                newCollision.triangleID = tri;
                newCollision.distance = tempDistance;
                newCollision.position = origin + direction * tempDistance;
                newCollision.isCollision = true;
                newCollision.octantID = octantID;
                octantCollisionDistance = octantDistance;
                triangleCollisionDistance = tempDistance;
            }
        }

        // Don't check for child octants if the octant is a leaf
        if (octant.octantState == OctantLeaf)
        {
            continue;
        }

        // Check if the octants children are intersected and if so, push them onto the queue
        foreach (child, octant.children)
        {

            OctantReference childOctant = octants[child];

            if (isOriginInOctantBounds(origin, childOctant))
            {
                octants[child].intersected = true;
                queue.push(make_pair(0.0f, child));
                continue;
            }

            // Get nearest corner of octant
            // Uses the morton code to determine which corner is nearest and gets the corresponding vector
            // Then calculates the position of the corner
            v3 originDirectionVector = octantPositionVectors[mortonCodeHash(origin, childOctant.octantCenter)];
            v3 corner = childOctant.octantCenter + originDirectionVector * childOctant.octantHalfSize;

            // Calculate the intersection of the ray with each face of the octant
            // TODO: Should have better naming for vector components
            for (int i = 0; i < 3; i++)
            {
                float tempDistance; // temp distance value for intersection below

                // If the plane is intersected
                if (intersectRayPlane(
                        origin,
                        direction,
                        corner,
                        planeNormals[i],
                        tempDistance))
                {
                    v3 point = origin + direction * tempDistance; // Calculate the intersection pointd
                    int j = (i + 1) % 3;                          // Determine the second component of the plane to test

                    // Check if the intersection point is within the octant's face
                    // and if the distance is closer than the current recorded distance
                    if (abs(childOctant.octantCenter[i] - point[i]) <= childOctant.octantHalfSize &&
                        abs(childOctant.octantCenter[j] - point[j]) <= childOctant.octantHalfSize &&
                        tempDistance <= triangleCollisionDistance)
                    {
                        octants[child].intersected = true;
                        queue.push(make_pair(tempDistance, child));
                    }
                }
            }
        }
    }

    collisionRef = newCollision;
}

void OctreeDefinition::Octree::octreeRayIntersection(v3 origin, v3 direction, bool isSymmetric, v3 planeOrigin, v3 planeNormal) ONOEXCEPT
{
    thread reflectedThread;
    if (isSymmetric)
    {
        v3 reflectOrigin, reflectDirection;
        reflectRay(origin, direction, planeOrigin, planeNormal, reflectOrigin, reflectDirection);

        reflectedThread = thread([&, reflectOrigin, reflectDirection]() {
            octreeRayIntersectionCore(reflectOrigin, reflectDirection, reflectedCollision);
        });
    }

    octreeRayIntersectionCore(origin, direction, collision);

    if (isSymmetric)
    {
        reflectedThread.join();
    }
}

bool Octree::isOriginInOctantBounds(v3 origin, OctantReference octant) ONOEXCEPT
{
    return (abs(origin.x - octant.octantCenter.x) <= octant.octantHalfSize &&
            abs(origin.y - octant.octantCenter.y) <= octant.octantHalfSize &&
            abs(origin.z - octant.octantCenter.z) <= octant.octantHalfSize);
}

void Octree::reflectRay(rv3 origin, rv3 direction, rv3 planeOrigin, rv3 planeNormal, rv3 reflectOrigin, rv3 reflectDirection) ONOEXCEPT
{
    reflectDirection = glm::reflect(direction, planeNormal);

    if (glm::epsilonEqual(dot(origin - planeOrigin, planeNormal), 0.0f, 0.00001f))
    {
        reflectOrigin = origin;
        return;
    }

    float distance;
    if (!glm::intersectRayPlane(origin, planeNormal, planeOrigin, planeNormal, distance))
    {
        glm::intersectRayPlane(origin, -planeNormal, planeOrigin, planeNormal, distance);
        distance = -distance;
    }

    reflectOrigin = origin + 2.0f * distance * planeNormal;
}

// New collection functions
/**
 * @brief Collects vertices withing range of collision and the reflected collision
 * Can also collect the affected vertices of both collisions into one array
 * Can also collect the triangles within range of collision and the reflected collision (separate arrays)
 *
 * @param range
 * @param isSymmetric
 * @param collectAffectedTriangles
 * @param collectTrianglesInRange
 */
void Octree::collectAroundCollision(float range, bool collectAffectedTriangles, bool collectTrianglesInRange, bool isSymmetric) ONOEXCEPT
{
    if (collectTrianglesInRange)
    {
        collectAffectedTriangles = true;
    }

    if (isSymmetric)
    {
        collectVerticesWithReflection(range);
    }
    else
    {
        collectVerticesAroundCollision(range);
    }

    if (collectAffectedTriangles)
    {
        TriangleIDList reflectedAffectedTriangles;
        affectedTriangles = getTrianglesFromVertices(verticesInRange);

        if (isSymmetric)
        {
            reflectedAffectedTriangles = getTrianglesFromVertices(reflectedVerticesInRange);
            affectedTriangles.insert(affectedTriangles.end(), reflectedAffectedTriangles.begin(), reflectedAffectedTriangles.end());
        }

        if (collectTrianglesInRange)
        {
            foreach (tri, affectedTriangles)
            {
                if (abs(distance(vertices[triangles[tri][0]].position, collision.position)) <= range &&
                    abs(distance(vertices[triangles[tri][1]].position, collision.position)) <= range &&
                    abs(distance(vertices[triangles[tri][2]].position, collision.position)) <= range)
                {
                    trianglesInRange.emplace_back(tri);
                }
            }

            if (isSymmetric)
            {
                foreach (tri, reflectedAffectedTriangles)
                {
                    if (abs(distance(vertices[triangles[tri][0]].position, collision.position)) <= range &&
                        abs(distance(vertices[triangles[tri][1]].position, collision.position)) <= range &&
                        abs(distance(vertices[triangles[tri][2]].position, collision.position)) <= range)
                    {
                        reflectedTrianglesInRange.emplace_back(tri);
                    }
                }
            }
        }
    }
}

void Octree::collectVerticesWithReflection(float range) ONOEXCEPT
{
    mutex checkedmtx;
    std::unordered_set<KeyData> checked; // Every vertex that has been checked

    thread reflectedThread([&]() {
        std::unordered_set<KeyData> unchecked;

        unchecked.insert(triangles[reflectedCollision.triangleID][0]);
        unchecked.insert(triangles[reflectedCollision.triangleID][1]);
        unchecked.insert(triangles[reflectedCollision.triangleID][2]);

        while (!unchecked.empty())
        {
            KeyData element = *unchecked.begin();
            unchecked.erase(unchecked.begin());
            checkedmtx.lock();
            checked.insert(element);
            checkedmtx.unlock();

            if (distance(vertices[element].position, collision.position) <= range)
            {
                reflectedVerticesInRange.emplace_back(element);

                foreach (vertex, edges[element].vertexEdges)
                {
                    checkedmtx.lock();
                    if (!checked.contains(vertex))
                    {
                        unchecked.insert(vertex);
                    }
                    checkedmtx.unlock();
                }
            }
        }
    });

    std::unordered_set<KeyData> unchecked; // List of vertices to check if they're within range

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
        checkedmtx.lock();
        checked.insert(element);
        checkedmtx.unlock();

        // Check distance between the collision and the element
        if (distance(vertices[element].position, collision.position) <= range)
        {
            verticesInRange.emplace_back(element); // Add the element to the results list

            // Add each vertex that is connected by an edge to this vertex
            // and has not already been checked.
            // Using unordered set allows us to insert into unchecked whether or not it already exists.
            foreach (vertex, edges[element].vertexEdges)
            {
                checkedmtx.lock();
                if (!checked.contains(vertex))
                {
                    unchecked.insert(vertex);
                }
                checkedmtx.unlock();
            }
        }
    }

    reflectedThread.join();
}