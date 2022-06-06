#include "SculptPayload.hpp"

SculptPayloadDefinition::SculptPayload::SculptPayload()
{
	this->radius = 0.5;
}

SculptPayloadDefinition::SculptPayload::~SculptPayload()
{
}

void SculptPayloadDefinition::SculptPayload::changeRadius(float newRadius)
{
	this->radius = newRadius;
}

void SculptPayloadDefinition::SculptPayload::updateLast(const TriangleID& id, rv3 lastHit, v3 tempNorm)
{
	this->last = id;
	this->hit = lastHit;
	this->hitNorm = tempNorm;
}

void SculptPayloadDefinition::SculptPayload::reverseDir()
{
	this->rDir = direction * -1.0f;
}
