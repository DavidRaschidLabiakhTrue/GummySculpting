#include "MeshChangeLog.hpp"

using namespace MeshChangeLogDefinition;

MeshChangeLogDefinition::ChangeLog::ChangeLog()
{
	this->changeList.emplace_back(HistoryKeyVertexMap()); // add a starting map.
	this->currentLevel = 1;
}

MeshChangeLogDefinition::ChangeLog::~ChangeLog()
{
}

void MeshChangeLogDefinition::ChangeLog::adjustLevelUp()
{
	currentLevel++;
	if (maxLevel < currentLevel)
	{
		//say "Adding new History Level" done;
		maxLevel = currentLevel;
		this->changeList.emplace_back(HistoryKeyVertexMap());
	}
}

void MeshChangeLogDefinition::ChangeLog::adjustLevelDown()
{
	if (currentLevel - 1 != 0)
	{
		currentLevel--; // shift down 1
		//say "Shifted down a history Level" done;
		return;
	}
	eif(currentLevel - 1 == 0)
	{
		currentLevel = 0;
		//say "Returned to Base reversion Level" done;
	}
	else
	{
		return;
	}

}

void MeshChangeLogDefinition::ChangeLog::cullLevelsUpward()
{
	if (currentLevel != 0)
	{
		this->changeList.resize(currentLevel); // if we are at level 0, we want to ensure we have space for 1 element
	}
	
	
}

HistoryKeyVertexMap& MeshChangeLogDefinition::ChangeLog::getCurrentLevel()
{
	return this->changeList[currentLevel];
}

ChangeLogLevel MeshChangeLogDefinition::ChangeLog::currentLevelIndex()
{
	return currentLevel - 1;
}
