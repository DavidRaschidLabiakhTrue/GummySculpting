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
    inline v3 getEdgeMidpoint(MeshReference cMesh, KeyData v1, KeyData v2);
} // namespace Sculpting::Tessellate
#endif