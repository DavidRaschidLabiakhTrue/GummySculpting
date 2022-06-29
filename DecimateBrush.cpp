#include "DecimateBrush.hpp"

using namespace Sculpting;

// Currently unused, was used for testing purposes.
// TODO: Change to work properly as a brush
// NOTES: min radius to decimate certain to force a larger area?
//        Add protection to prevent neighboring edges from being decimated?
void Decimate::applyDecimate(MeshReference cMesh, SculptPayloadReference payload)
{
    // payload.last = -1;
    // if (payload.wasRun)
    // {
    //     return;
    // }
    // Test collapse edge
    // cMesh.removeTriangles(cMesh.collapseEdge(make_pair(cMesh.triangles[cMesh.collision.triangleID][0],
    //                                                    cMesh.triangles[cMesh.collision.triangleID][1])));

    // Test collapse triangle
    // cMesh.removeTriangles(cMesh.collapseTriangle(cMesh.collision.triangleID));
    // cMesh.collapseTriangle(cMesh.collision.triangleID);

    // cMesh.decimateMesh();
}