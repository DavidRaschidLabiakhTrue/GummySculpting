#include "Brush.hpp"

void Sculpting::Brush::applyBrush(MeshReference cMesh, SculptPayloadReference payload)
{
	const auto hit = payload.hit;
	const auto angLim = glm::radians(60.0f);
	const float scale = 0.05;

	const auto hitNorm = payload.hitNorm;
	const float radius = payload.radius;


	const float piVal = pi<float>();

	const float brushConst = payload.polarity * payload.radius * scale;

	auto end = cMesh.currentVertices.end();
	// parallize
	#pragma loop(hint_parallel(8))
	for (auto vertex = cMesh.currentVertices.begin(); vertex != end; ++vertex)
	{
		const float curve = ((glm::cos((distance((*vertex).second.position, payload.hit) / radius) * piVal) + 1.0f) * 0.5f);
		const float ang = angle((*vertex).second.normal, hitNorm);

		if (ang < angLim)
		{
			const float modifier = ((glm::cos((ang / angLim) * piVal) + 1.0f) * 0.5f);

			(*vertex).second.position += brushConst * curve * normalize(modifier * (*vertex).second.normal + (1 - modifier) * hitNorm);
		}
		else
		{
			(*vertex).second.position += brushConst * curve * hitNorm;
		}
	}

    Algos::applyCurrentVerticesToMesh(cMesh);
}