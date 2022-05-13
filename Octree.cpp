#include "Octree.hpp"

Octree::Octree(vector<v3> &verts, Indices &indices)
{

    auto start = chrono::steady_clock::now();
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
        auto edge0 = edgeset.insert(Edge(p0.index, p1.index));
        auto edge1 = edgeset.insert(Edge(p1.index, p2.index));
        auto edge2 = edgeset.insert(Edge(p2.index, p0.index));

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

    edges = vector<Edge>(edgeset.size());
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

Octree::~Octree()
{
}

void Octree::octreeDebug()
{
    say "Octree Debug" done;
    say "\tPoint Limit: " << limit done;
    say "\tDepth Limit: " << depthLimit done;
    say "\tDepth: " << depth done;
    say "\tPoints: " << points.size() done;
    say "\tEdges: " << edges.size() done;
    say "\tTriangles: " << triangles.size() done;
    say "\tOctants: " << octants.size() done;
    say "\tLeaves: " << leaves.size() done;
    say "\tCenter: " << glm::to_string(octants[0].center) done;
    say "\tHalfsize: " << octants[0].halfsize done;
    say "\tTriangles in Root: " << octants[0].tris.size() done;

    int count = 0;
    int owt = 0;
    int tip = 0;
    foreach (o, octants)
    {
        if (o.state)
            count++;
        if (o.tris.size()) {
            owt++;
            if(o.state == 1)
                tip++;
        }
    }
    say "\tActive Octants: " << count done;
    say "\tOctants with Triangles: " << owt done;
    say "\tPsuedo-Leaves w/ Traingles: " << tip done;

    say "Octree Mesh:" done;
    say "\tVertices: " << octreeVertices.size() done;
    say "\tIndices: " << octreeIndices.size() done;

    // say "\t----Triangles----" done;
    // foreach (t, triangles)
    // {
    //     say "\tTriangle: " << t.index done;
    //     say "\t  Points: " << t.points[0] << " " << t.points[1] << " " << t.points[2] done;
    //     say "\t  Edges: " << t.edges[0] << " " << t.edges[1] << " " << t.edges[2] done;
    // }

    // say "\t----Edges----" done;
    // foreach (e, edges)
    // {
    //     say "\tEdge " << e.index done;
    //     say "\t  Points: " << e.points[0] << "-" << e.points[1] done;
    //     say "\t  Triangles: < " << e.triangles[0] << " | " << e.triangles[1] << " >" done;
    // }

    // say "\t----Points----" done;
    // foreach(p, points) {
    //     say "\tPoint " << p.index << ": " done;
    //     say "\t  Edges: ";
    //     foreach(e, p.edges) {
    //         say e << " ";
    //     }
    //     say endl;
    // }
}

vector<Point> Octree::collect(Collision &collision, double range)
{
    vector<Point> points;
    std::unordered_set<Point, point_hash, point_equal> unchecked;
    std::unordered_set<Point, point_hash, point_equal> tempUnchecked;
    std::unordered_set<Point, point_hash, point_equal> checked;

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
            if (distance(VertexLookUp(p.index), collision.pos) <= range)
            {
                points.emplace_back(p);
                // Add each point that is connected by an edge to this point
                foreach (edge, p.edges)
                {
                    Edge temp = edges[edge];
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
    vector<v3> pts = {VertexLookUp(triangles[t].points[0]), VertexLookUp(triangles[t].points[1]), VertexLookUp(triangles[t].points[2])};
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
    int next = morton(VertexLookUp(triangles[t].points[0]), oct.center);

    // If triangle points are not in the same octant...
    if (morton(VertexLookUp(triangles[t].points[1]), oct.center) != next || morton(VertexLookUp(triangles[t].points[2]), oct.center) != next)
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
    // resize(t);
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
            if (intersectRayTriangle(origin, direction, VertexLookUp(triangles[t].points[0]), VertexLookUp(triangles[t].points[1]), VertexLookUp(triangles[t].points[2]), baryPosition, distance))
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