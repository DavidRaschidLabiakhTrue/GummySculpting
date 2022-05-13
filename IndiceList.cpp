#include "IndiceList.hpp"

using namespace IndiceListDefinition;

IndiceList::IndiceList()
{
}

IndiceList::~IndiceList()
{
}

const int IndiceListDefinition::IndiceList::indicesMemorySize()
{
	return indices.size() * sizeof(KeyData);
}
