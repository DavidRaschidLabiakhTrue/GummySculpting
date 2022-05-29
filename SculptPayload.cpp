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

void SculptPayloadDefinition::SculptPayload::updateLast(const TriangleID& id)
{
	this->last = id;
}
