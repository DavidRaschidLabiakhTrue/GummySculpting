#ifndef Tessellate_HPP
#define Tessellate_HPP

#include "Mesh.hpp"
#include "SculptPayload.hpp"
#include "ToolsWindow.hpp"
#include <unordered_set>

namespace Sculpting::Tessellate
{
    using namespace MeshDefinition;
    using namespace SculptPayloadDefinition;

    void applyTessellate(MeshReference cMesh, SculptPayloadReference payload);
    void splitAdjacentOuterTriangles(MeshReference cMesh, SculptPayloadReference payload, std::unordered_set<int>& outerTriangleSet, std::unordered_set<int>& allVerticesInRange);
    void splitOuterTriangles(MeshReference cMesh, SculptPayloadReference payload, std::unordered_set<int>& outerTriangleSet, unordered_map<v3, KeyData>& midpointMap, unordered_set<int>& allVerticesInRange);
    unordered_map<v3, KeyData> createMidpointMap(MeshReference cMesh, std::unordered_set<int>& allVerticesInRange);
    void subdivideInnerTriangles(MeshReference cMesh, unordered_map<v3, KeyData>& midpointMap, std::unordered_set<int>& innerTriangleSet);
} // namespace Sculpting::Tessellate
#endif