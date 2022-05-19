#include "Octree.hpp"
#include "VertexIDHashing.hpp"

using namespace OctreeDefinition;

/**
 * @brief Print octree information for debugging.
 */
void OctreeDefinition::Octree::octreePrintStats()
{
    say "Octree Debug" done;
    say "\tVertex Limit:" spc octantTriangleLimit done;
    say "\tDepth Limit:" spc octreeDepthLimit done;
    say "\tDepth:" spc octreeDepth done;
    say "\tCenter:" spc to_string(octants[root].octantCenter) done;
    say "\tHalfsize:" spc octants[root].octantHalfSize done;
    say "\tVertices: " << verticeCount() done;
    say "\tTriangles:" spc totalTriangles() done;
    say "\tOctants:" spc octants.size() done;
    say "\tTriangles in Root:" spc octants[root].triangleIDs.size() done;
    say "\tLeaves:" spc leaves.size() done;

    int count = 0; // Counts leaves and pseudo-leaves
    int owt = 0; // Octants with triangles
    int pwt = 0; // Triangles in pseudo leaves
    foreach (o, octants)
    {
        if (o.octantState)
        {
            count++;
        }

        if (o.triangleIDs.size())
        {
            owt++;
            if (o.octantState == OctantState::OctantNotEmptyInternal)
            {
                pwt++;
            }
        }
    }
    // Ignore for now
    say "\tActive Octants:" spc count done;
    say "\tOctants w/ Triangles:" spc owt done;
    say "\tPsuedo-Leaves w/ Traingles:" spc pwt done;
}

/**
 * @brief Build the octree by inserting all triangles of the mesh into the octree.
 * Initializes the root octant.
 */
void OctreeDefinition::Octree::buildOctree()
{
    say "Initializing Octree...";

    TriangleOctantKeyPairList::loadTriangleOctantKeyPairList();

    // Adjust the extents of the mesh vertices wrt the center
    float maxExtent = compMax(abs(this->center - limMax));
    float minExtent = compMin(abs(this->center - limMin));

    // Create root octant with appropriate center and half size
    Octant rootOctant;
    rootOctant.octantIndex = 0;
    rootOctant.octantCenter = this->center;
    rootOctant.octantHalfSize = glm::max(maxExtent, minExtent) * octreeBuffer;
    octants.emplace_back(rootOctant);

    say "done" done;

    // Insert all triangles into the octree
    int triangleCount = totalTriangles();
    for (int i = 0; i < triangleCount; i++)
    {
        Octree::insertTriangle(i);
    }
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
    if (octreeDepth == octreeDepthLimit)
    {
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
        float oldRootAdjustedHalfSize = (float)(oldRoot.octantHalfSize / octreeLooseness);
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