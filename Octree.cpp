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

void OctreeDefinition::Octree::buildOctree()
{
    TriangleOctantKeyPairList::loadTriangleOctantKeyPairList();
}

void OctreeDefinition::Octree::octreePrintStats()
{
    say "Octree Debug" done;
    say "\tPoint Limit:" spc octreeLimit done;
    say "\tDepth Limit:" spc octreeDepthLimit done;
    say "\tDepth:" spc octreeDepth done;
    // say "\tPoints: " << points.size() done; - need to reimplement
    say "\tEdges:" spc edgesTotal() done;
    say "\tTriangles:" spc totalTriangles() done;
    say "\tOctants:" spc octantsTotal() done;
    say "\tLeaves:" spc leaves.size() done;

    say "\tCenter:" spc to_string(octants[0].octantCenter) done;
    say "\tHalfsize:" spc octants[0].octantHalfSize done;
    say "\tTriangles in Root:" spc octants[0].octantTotalTriangles() done;

    int count = 0;
    int owt = 0;
    int tip = 0;
    foreach (o, octants)
    {
        if (o.octantState)
        {
            count++;
        }

        if (o.octantTotalTriangles())
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

bool OctreeDefinition::Octree::octantPointsInBound(RIndexTriangle tri, OctantIndex octantID)
{
    OctantReference oct = octants[octantID]; // retrieve the current processed octant

    for (int i = 0; i < 3; i++)
    {
        rv3 pos = vertices[tri[i]].position;
        // what is this supposed to be doing?
        if (oct.octantHalfSizeCenterComparison(pos))
        {
            return false;
        }
    }
    return true;
}

const int OctreeDefinition::Octree::octantsTotal()
{
    return octants.size();
}

const int OctreeDefinition::Octree::octantsLeavesTotal()
{
    return leaves.size();
}

// auto OctreeDefinition::Octree::collect(OctreeCollision &collision, double range)
// {
//     // this code is not properly structured

//     KeyList results; // list of keys returned from collecting method

//     std::unordered_set<KeyData, point_hash, point_equal> unchecked;     // needs commenting
//     std::unordered_set<KeyData, point_hash, point_equal> tempUnchecked; // needs commenting
//     std::unordered_set<KeyData, point_hash, point_equal> checked;       // needs commenting - what is checked

//     for (int i = 0; i < 3; i++)
//     {
//         unchecked.insert(triangles[collision.triangleID][i]);
//     }

//     while (!unchecked.empty())
//     {
//         tempUnchecked = unchecked; // this seems extremely performance inefficient to copy over containers like this.

//         // for each element in unchecked
//         foreach (uncheckedElement, unchecked)
//         {
//             // if distance between the collision and unchecked element is less than or equal to the range
//             if (distance(vertices[uncheckedElement].position, collision.position) <= range)
//             {
//                 // load the unchecked element into results
//                 results.emplace_back(uncheckedElement);
//                 // now check the elements edges
//                 // Add each point that is connected by an edge to this point
//                 foreach (vertexEdge, edges[uncheckedElement].vertexEdges)
//                 {
//                     // Left OFF Here - Need to figure out what is going on with this logic. - I shouldn't try and remake the structure but all of these additional helper structures are a mess.
//                 }
//             }
//         }
//     }

//     return;
// }


// Rewritten to avoid copying the entire unchecked set.
// Collect all vertices within a given range of the collision
auto OctreeDefinition::Octree::collect(OctreeCollision &collision, double range)
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
            // and that has not already been checked
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

// vector<Point> Octree::collect(Collision &collision, double range)
// {
//     vector<Point> points;
//     std::unordered_set<Point, point_hash, point_equal> unchecked; // needs commenting
//     std::unordered_set<Point, point_hash, point_equal> tempUnchecked;  // needs commenting
//     std::unordered_set<Point, point_hash, point_equal> checked;  // needs commenting - what is checked

//     // Insert intersected triangle's points into unchecked
//     foreach (p, triangles[collision.triangle].points)
//     {
//         unchecked.insert(p);
//     }

//     // While unchecked is not empty
//     while (!unchecked.empty())
//     {
//         tempUnchecked = unchecked;
//         // For each unchecked point
//         foreach (p, unchecked)
//         {

//             // If distance to point is within range
//             if (distance(getVertexPosition(p.index), collision.pos) <= range)
//             {
//                 points.emplace_back(p);
//                 // Add each point that is connected by an edge to this point
//                 foreach (edge, p.edges)
//                 {
// 					// oddly programmed - what is occuring here logically?
//                     GEdge temp = edges[edge];
//                     Point otherPoint = temp.getOtherPoint(p.index);

//                     // Check if point was checked
//                     if (!checked.contains(otherPoint))
//                     {
//                         // If not add to tempUnchecked
//                         tempUnchecked.insert(otherPoint);
//                     }
//                 }
//             }

//             // Add to checked and remove from unchecked
//             checked.insert(p);
//             tempUnchecked.erase(p);
//         }

//         unchecked = tempUnchecked;
//     }

//     return points;
// }

/*
#include "Octree.hpp"

Octree::Octree(vector<v3> &verts, vector<int> &indices)
{


    points.reserve(verts.size());
    triangles = vector<Triangle>(indices.size() / 3);
    edges.reserve((int)ceil(indices.size() / 2));
    edgeset.reserve((int)ceil(indices.size() / 2));

    // Calculate center and halfsize of the octree.
    v3 maxDist = v3(0);
    float halfsize = 0;
    v3 center = v3(0);
    int i = 0;
    foreach (v, verts)
    {
        center += v;
        points.emplace_back(Point(i++));

        maxDist.x = glm::max(maxDist.x, abs(v.x));
        maxDist.y = glm::max(maxDist.y, abs(v.y));
        maxDist.z = glm::max(maxDist.z, abs(v.z));
    }

    center /= verts.size();
    // center += v3(std::numeric_limits<float>::epsilon());

    halfsize = (float)1.0001 * glm::max(maxDist.x, glm::max(maxDist.y, maxDist.z)); // Add padding

    say "Center and Halfsize time: " << chrono::duration<double, milli>(chrono::steady_clock::now() - start).count() << " ms" done;

    // Triangle limit per octant is 5% of total triangles in mesh
    // limit = (int)ceil((0.05 * indices.size() / 3));

    // Initialize octants with root node
    octants.emplace_back(Octant(center, halfsize, limit, 0));
    leaves.insert(0);

    int edgeIndex = 0;
    int triIndex = 0;

    start = chrono::steady_clock::now();
    // Generate triangles
    for (int i = 0; i < indices.size(); i += 3)
    {
        Point &p0 = points[indices[i]];
        Point &p1 = points[indices[i + 1]];
        Point &p2 = points[indices[i + 2]];
        Triangle t = Triangle(p0.index, p1.index, p2.index, triIndex);
        p0.addTriangle(triIndex);
        p1.addTriangle(triIndex);
        p2.addTriangle(triIndex);

        // Add edges to triangle, inserting into octree edge set to guarantee uniqueness.
        auto edge0 = edgeset.insert(GEdge(p0.index, p1.index));
        auto edge1 = edgeset.insert(GEdge(p1.index, p2.index));
        auto edge2 = edgeset.insert(GEdge(p2.index, p0.index));

        // If edges were inserted to set (i.e. edge is new)
        // Set index of edge
        // Add edge to points
        if (edge0.second)
        {
            edge0.first->index = edgeIndex;
            p0.addEdge(edgeIndex);
            p1.addEdge(edgeIndex++);
        }
        if (edge1.second)
        {
            edge1.first->index = edgeIndex;
            p1.addEdge(edgeIndex);
            p2.addEdge(edgeIndex++);
        }
        if (edge2.second)
        {
            edge2.first->index = edgeIndex;
            p0.addEdge(edgeIndex);
            p2.addEdge(edgeIndex++);
        }

        t.addEdge(edge0.first->index);
        t.addEdge(edge1.first->index);
        t.addEdge(edge2.first->index);

        // Add triangle to each edge
        edge0.first->addTriangle(triIndex);
        edge1.first->addTriangle(triIndex);
        edge2.first->addTriangle(triIndex);

        triangles[triIndex] = t;
        triIndex++;
    }

    edges = vector<GEdge>(edgeset.size());
    foreach (e, edgeset)
    {
        edges[e.index] = e;
    }

    say "Triangle/Edge gen time: " << chrono::duration<double, milli>(chrono::steady_clock::now() - start).count() << " ms" done;

    start = chrono::steady_clock::now();
    for (int i = 0; i < triIndex; i++)
    // for (int i = 0; i < 100; i++)
    {
        insert(i);
    }
    say "Insertion time: " << chrono::duration<double, milli>(chrono::steady_clock::now() - start).count() << " ms" done;
    generateMesh(false);
    octreeDebug();
}
*/

/*
vector<Point> Octree::collect(Collision &collision, double range)
{
    vector<Point> points;
    std::unordered_set<Point, point_hash, point_equal> unchecked; // needs commenting
    std::unordered_set<Point, point_hash, point_equal> tempUnchecked;  // needs commenting
    std::unordered_set<Point, point_hash, point_equal> checked;  // needs commenting - what is checked

    // Insert intersected triangle's points into unchecked
    foreach (p, triangles[collision.triangle].points)
    {
        unchecked.insert(p);
    }


    // While unchecked is not empty
    while (!unchecked.empty())
    {
        tempUnchecked = unchecked;
        // For each unchecked point
        foreach (p, unchecked)
        {

            // If distance to point is within range
            if (distance(getVertexPosition(p.index), collision.pos) <= range)
            {
                points.emplace_back(p);
                // Add each point that is connected by an edge to this point
                foreach (edge, p.edges)
                {
                    // oddly programmed - what is occuring here logically?
                    GEdge temp = edges[edge];
                    Point otherPoint = temp.getOtherPoint(p.index);

                    // Check if point was checked
                    if (!checked.contains(otherPoint))
                    {
                        // If not add to tempUnchecked
                        tempUnchecked.insert(otherPoint);
                    }
                }
            }

            // Add to checked and remove from unchecked
            checked.insert(p);
            tempUnchecked.erase(p);
        }

        unchecked = tempUnchecked;
    }

    return points;
}

void Octree::resize(int t)
{
    vector<v3> pts = {getVertexPosition(triangles[t].points[0]), getVertexPosition(triangles[t].points[1]), getVertexPosition(triangles[t].points[2])};
    v3 centroid = (pts[0] + pts[1] + pts[2])/v3(3);
    v3 direction(1);
    while(!octants[0].inBounds(triangles[t].points)) {
        int rootCode = 0;
        if(centroid.x < octants[0].center.x) {
            direction.x = -1;
            rootCode += 4;
        }
        if(centroid.y < octants[0].center.y) {
            direction.y = -1;
            rootCode += 2;
        }
        if(centroid.z < octants[0].center.z) {
            direction.z = -1;
            rootCode++;
        }
        float newHalfsize = octants[0].halfsize * 2;
        v3 newCenter = octants[0].center + direction * octants[0].halfsize;
        Octant newRoot = Octant(newCenter, newHalfsize, limit, 0);
        Octant oldRoot = octants[0];
        newRoot.state = 0;
        octants[0] = newRoot;
        subdivideOctant(0);
        int oldRootNewPosition = octants[0].children[rootCode];
        octants[oldRootNewPosition] = oldRoot;
        // Update parents
        octants[oldRootNewPosition].parent = 0;
        foreach(child, oldRoot.children) {
            octants[oldRoot.children[child]].parent = oldRootNewPosition;
        }
    }
}

// NOTE: untested new resize, not adjusted yet for project revision - Ryan
void Octree::resize(int t)
{
    Triangle tri = triangles[t];
    Octant oldRoot = octants[0];
    vector<V3> pts = {VertexLookUp(tri.points[0]), VertexLookUp(tri.points[1]), VertexLookUp(tri.points[2])};

    // Direction to grow octree
    V3 direction(1);

    // Resize until triangle is in bounds
    while(!octants[0].inBounds(triangles[t].points)) {
        // Morton code of the current root inside the new root
        int rootCode = 0;

        // Calculates the direction the octree must grow
        if(tri.centroid.x < oldRoot.center.x) {
            direction.x = -1;
            rootCode += 4;
        }
        if(tri.centroid.y < oldRoot.center.y) {
            direction.y = -1;
            rootCode += 2;
        }
        if(tri.centroid.z < oldRoot.center.z) {
            direction.z = -1;
            rootCode++;
        }

        // Adjusted halfsize
        float adjustedHalfSize = (oldRoot.halfsize / (1 + looseness));
        float newHalfsize = adjustedHalfSize * 2;

        // Adjusted root center
        V3 adjustedCenter = oldRoot.center + (-1.0f * direction) * (oldRoot.halfsize - adjustedHalfSize);
        V3 newCenter = adjustedCenter + direction * adjustedHalfSize;

        // Create New root octant, set its state, and set as root
        Octant newRoot = Octant(newCenter, newHalfsize, limit, 0);
        newRoot.state = 0;
        octants[0] = newRoot;

        // Subdivide the new root
        subdivideOctant(0);

        // Place the old root in the appropriate position as child of new root and in the octant array
        int oldRootNewPosition = octants[0].children[rootCode];
        octants[oldRootNewPosition] = oldRoot;

        // Update parent value of old root's children to its new position in octants array
        octants[oldRootNewPosition].parent = 0;
        foreach(child, oldRoot.children) {
            octants[oldRoot.children[child]].parent = oldRootNewPosition;
        }
    }
}

// Find the octant which fully encapsulates the given triangle
// Stops when a leaf node is reached
int Octree::findOctant(int t)
{
    // currentDepth = 0;
    // int o = 0;
    // int next = getNext(o, t);

    // // next is 0 when a leaf node is reached
    // while (next != o)
    // {
    //     currentDepth++;
    //     o = next;
    //     next = getNext(o, t);
    // }
    // return o;

    currentDepth = 0;
    int o = 0;
    int next = octants[o].children[morton(triangles[t].centroid, octants[o].center)];

    while(next != 0 && octants[next].inBounds(triangles[t].points)) {
        currentDepth++;
        o = next;
        next = octants[o].children[morton(triangles[t].centroid, octants[o].center)];
    }
    return o;
}

// Calculate the next octant the given triangle
// TODO: Handle cases with 0
// MAYBE: base of centroid
int Octree::getNext(int o, int t)
{
    Octant oct = octants[o];
    int next = morton(getVertexPosition(triangles[t].points[0]), oct.center);

    // If triangle points are not in the same octant...
    if (morton(getVertexPosition(triangles[t].points[1]), oct.center) != next || morton(getVertexPosition(triangles[t].points[2]), oct.center) != next)
    {
        return o;
    }

    // Get index of the next octant from children
    next = oct.children[next];
    // If child doesn't exist, return o
    return next == 0 ? o : next;
}

// in octants list, find position for t, and insert t with respect to the octants list.
bool Octree::insert(int t)
{
    if(!octants[0].inBounds(t)){
        // resize(t);
    }
    int o = findOctant(t);
    bool doSubdivision = octants[o].insert(t);
    leaves.insert(o);
    triangles[t].octant = o;

    if (octants[o].state == 0)
    {
        octants[o].state = 1;
    }
    else if (octants[o].state == 2 && currentDepth < depthLimit && doSubdivision)
    {
        subdivideOctant(o);
    }

    return true;
}

void Octree::subdivideOctant(int o)
{
    if(currentDepth == depth) depth++;
    for(int i = 0; i < 8; i++) {
        leaves.insert((int) octants.size() + i);
    }
    // Subdivide octant and place children into octants list
    foreach (octant, octants[o].subdivide((int)octants.size(), looseness))
    {
        octants.emplace_back(octant);
    }

    // Reinsert triangles into children if they fit entirely inside
    // Reverse order to preserve positions on removal
    for (int i = (int)octants[o].tris.size() - 1; i >= 0; i--)
    {
        Triangle &t = triangles[octants[o].tris[i]];

        // base on centroid
        int next = octants[o].children[morton(t.centroid, octants[o].center)];

        if (octants[next].inBounds(t.points))
        {
            bool isFull = octants[next].insert(t.index);
            t.octant = next;

            // If child octant becomes full, subdivide it
            if(isFull && currentDepth < depthLimit) {
                subdivideOctant(next);
            }

            // Remove triangle from parent octant
            octants[o].tris.erase(octants[o].tris.begin() + i);
        }

        // set state of octant
        if (octants[o].tris.size() == 0)
        {
            leaves.erase(o);
            octants[o].state = 0;
        }
        else
        {
            octants[o].state = 1;
        }
    }
}

bool Octree::contains(Triangle t)
{
    return true;
}

bool Octree::remove(Triangle &t)
{
    return true;
}

Collision Octree::rayIntersection(v3 &origin, v3 direction)
{
    Collision collision;
    collision.distance = std::numeric_limits<float>::max();

    float tmpDist = 0;
    float distance = std::numeric_limits<float>::max();
    v3 planeNormals[] = {
        {0, 0, 1}, // xy plane
        {1, 0, 0}, // yz plane
        {0, 1, 0}  // xz plane
    };

    // Check intersetion on every leaf octant
    // Then check intersection on each
    foreach (o, octants)
    {
        if (!o.state)
            continue;

        // Get nearest corner of octant
        v3 corner = o.center;
        for (int i = 0; i < 3; ++i)
        {
            if (origin[i] < o.center[i])
            {
                corner[i] -= o.halfsize;
            }
            else
            {
                corner[i] += o.halfsize;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (intersectRayPlane(origin, direction, corner, planeNormals[i], tmpDist))
            {
                // intersection point
                v3 point = origin + direction * tmpDist;
                int j = (i + 2) % 3;

                if (abs(o.center[i] - point[i]) <= o.halfsize && abs(o.center[j] - point[j]) <= o.halfsize)
                {
                    if (tmpDist < distance)
                    {
                        distance = tmpDist;
                    }
                }
            }
        }

        // Skip octant if intersect distance is < current collision or no intersection
        if (distance > collision.distance || distance == std::numeric_limits<float>::max())
        {
            continue;
        }

        foreach (t, o.tris)
        {
            vec2 baryPosition;
            if (intersectRayTriangle(origin, direction, getVertexPosition(triangles[t].points[0]), getVertexPosition(triangles[t].points[1]), getVertexPosition(triangles[t].points[2]), baryPosition, distance))
            {
                if (distance < collision.distance)
                {
                    collision.triangle = t;
                    collision.distance = distance;
                    collision.pos = origin + direction * distance;
                }
            }
        }
    }

    return collision;
}

void Octree::generateMesh(bool trianglesOnly) {
    octreeVertices.clear();
    octreeIndices.clear();

    // Gather all vertices from octants
    vector<v3> tempVertices;
    foreach(o, octants) {
        if(trianglesOnly && !o.tris.size()){
            continue;
        }

        foreach(v, o.generateMesh()) {
            tempVertices.push_back(v);
        }
    }

    // Convert to indexed list
    unordered_set<v3> vertSet;
    unordered_map<v3, int> vertMap;
    int index = 0;
    foreach(v, tempVertices) {
        auto res = vertSet.insert(v);

        if(res.second) {
            octreeVertices.push_back(v);
            vertMap[v] = index;
            octreeIndices.push_back(index++);
        } else {
            octreeIndices.push_back(vertMap[*res.first]);
        }
    }
}


// NOTE: untested update functions - Ryan
// Remove and reinsert triangle
void Octree::update(int t)
{
    if (octants[triangles[t].octant].remove(t))
    {
        insert(t);
    }
}

// Remove and reinsert triangles
void Octree::update(vector<int> tris)
{
    foreach (tri, tris)
    {
        update(tri);
    }
}
*/
