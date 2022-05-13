#include "Octant.hpp"

Octant::Octant(v3 center, double halfsize, int limit, int index)
{
    this->center = center;
    this->halfsize = halfsize;
    this->limit = limit;
    this->index = index;
}

Octant::~Octant()
{
}

// Might not need this function
bool Octant::contains(int t)
{

    return false;
}

bool Octant::inBounds(vector<int> &points)
{
    foreach (p, points)
    {
        v3 pos = VertexLookUp(p);
        if (abs(center.x - pos.x) > halfsize + std::numeric_limits<float>::epsilon() ||
            abs(center.y - pos.y) > halfsize + std::numeric_limits<float>::epsilon() ||
            abs(center.z - pos.z) > halfsize + std::numeric_limits<float>::epsilon())
        {
            return false;
        }
    }

    return true;
}

// Return true if Octant is full
bool Octant::insert(int t)
{
    tris.emplace_back(t);
    return tris.size() > limit;
}

// Subdivide Octant by adding 8 children
vector<Octant> Octant::subdivide(int octantsIndex, double looseness)
{
    double childHalfsize = halfsize / 2;
    vector<Octant> newOctants;

    // Initialize children with correct center positions
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                double x = (center.x - childHalfsize) + i * halfsize;
                x = x + (1 - 2 * i) * childHalfsize * looseness;
                double y = (center.y - childHalfsize) + j * halfsize;
                y = y + (1 - 2 * j) * childHalfsize * looseness;
                double z = (center.z - childHalfsize) + k * halfsize;
                z = z + (1 - 2 * k) * childHalfsize * looseness;

                // Add child to children and octants arrays, always last in array
                children[i * 4 + j * 2 + k] = octantsIndex;
                newOctants.emplace_back(Octant(v3(x, y, z), childHalfsize * (1 + looseness), limit, octantsIndex++));
                newOctants[newOctants.size()-1].parent = this->index;
            }
        }
    }

    return newOctants;
}

// Calculate the morton code of a point relative to the given center point
inline int morton(v3 point, v3 center)
{
    float x = ((point.x == 0.0f) && std::signbit(point.x)) ? 0.0f : point.x;
    float y = ((point.y == 0.0f) && std::signbit(point.y)) ? 0.0f : point.y;
    float z = ((point.z == 0.0f) && std::signbit(point.z)) ? 0.0f : point.z;
    return ((x >= center.x) << 2) | ((y >= center.y) << 1) | ((z >= center.z));
}

vector<v3> Octant::generateMesh()
{
    /**
     * Octant corner vertices visualization
     *    7-----6
     *   /|    /|
     *  3-----2 |
     *  | 4---|-5
     *  |/    |/
     *  0-----1
     *
     */
    vector<v3> corners = {
        v3(center.x - halfsize, center.y - halfsize, center.z - halfsize),
        v3(center.x + halfsize, center.y - halfsize, center.z - halfsize),
        v3(center.x + halfsize, center.y + halfsize, center.z - halfsize),
        v3(center.x - halfsize, center.y + halfsize, center.z - halfsize),
        v3(center.x - halfsize, center.y - halfsize, center.z + halfsize),
        v3(center.x + halfsize, center.y - halfsize, center.z + halfsize),
        v3(center.x + halfsize, center.y + halfsize, center.z + halfsize),
        v3(center.x - halfsize, center.y + halfsize, center.z + halfsize)};

    vector<v3> verts = {
        corners[0], corners[1],
        corners[1], corners[2],
        corners[2], corners[3],
        corners[3], corners[0],
        corners[4], corners[5],
        corners[5], corners[6],
        corners[6], corners[7],
        corners[7], corners[4],
        corners[0], corners[4],
        corners[1], corners[5],
        corners[2], corners[6],
        corners[3], corners[7]};

    return verts;
}