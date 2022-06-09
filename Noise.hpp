#ifndef Noise_HPP
#define Noise_HPP
#include "Mesh.hpp"
#include "SculptPayload.hpp"
namespace Sculpting::Noising // likely not grammatically correct
{
	using namespace SculptPayloadDefinition;
	using namespace MeshDefinition;

	void applyNoise(MeshReference cMesh, SculptPayloadReference payload , const int interations = 4);
}

#endif
