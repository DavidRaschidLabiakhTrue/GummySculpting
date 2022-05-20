#include "MeshChangeLog.hpp"

using namespace MeshChangeLogDefinition;

MeshChangeLogDefinition::ChangeLog::ChangeLog()
{

}

MeshChangeLogDefinition::ChangeLog::~ChangeLog()
{
}

void MeshChangeLogDefinition::ChangeLog::adjustLevelUp()
{
	currentLevel++;
	if (maxLevel < currentLevel)
	{
		maxLevel = currentLevel;
	}
}

void MeshChangeLogDefinition::ChangeLog::adjustLevelDown()
{
	if (currentLevel - 1 != 0)
	{
		currentLevel--; // shift down 1
		return;
	}
	eif(currentLevel - 1 == 0)
	{
		currentLevel = 0;
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
