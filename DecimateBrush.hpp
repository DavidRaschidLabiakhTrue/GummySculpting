#ifndef DecimateBrush_HPP
#define DecimateBrush_HPP

#include "Mesh.hpp"
#include "SculptPayload.hpp"
#include "ToolsWindow.hpp"
#include <unordered_set>

namespace Sculpting::Decimate
{
    using namespace MeshDefinition;
    using namespace SculptPayloadDefinition;

    void applyDecimate(MeshReference cMesh, SculptPayloadReference payload);
} // namespace Sculpting::Decimate
#endif