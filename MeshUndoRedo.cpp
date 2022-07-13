#include "MeshUndoRedo.hpp"

MeshUndoRedo_::UndoRedo::UndoRedo()
{
}

MeshUndoRedo_::UndoRedo::~UndoRedo()
{
}

void MeshUndoRedo_::UndoRedo::saveOldToHistory()
{

	if (isThereCurrentVerticesBeingSculpted() == false)
	{
		return; // guard against saving empty changes.
	}

	

	if (stepTracker.shouldCullMaxToCurrent()) // if there are elements beyond our current position, we are creating a new branch so we should pop the old branch.
	{
		int cullAmount = stepTracker.howManyToCull();
		for (int i = 0; i < cullAmount; i++)
		{
			history.pop_back();
		}
		say "Removing" spc cullAmount spc "entries of history from the back" done;
	}
	
	this->history.emplace_back(UndoRedoHistory(savedVertices));
	say "Saving stored set to history" done;
	stepTracker.raiseStep();
	clearSaved();

	displayCurrentHistoryCount();
}

bool MeshUndoRedo_::UndoRedo::isThereHistory()
{

	return history.size() > 0;
}

void MeshUndoRedo_::UndoRedo::clearSaved()
{
	savedVertices.clear();
}

bool MeshUndoRedo_::UndoRedo::isThereCurrentVerticesBeingSculpted()
{
	if (currentVertices.size() > 0)
	{
		return true;
	}
	return false;
}

void MeshUndoRedo_::UndoRedo::displayCurrentHistoryCount()
{
	say "history has" spc history.size() spc "slots being used" done;
}



MeshUndoRedo_::UndoRedoHistory::UndoRedoHistory(UndoMap& undomap)
{
	this->undoMap = undomap;
}

MeshUndoRedo_::UndoRedoHistory::UndoRedoHistory()
{
}

MeshUndoRedo_::UndoRedoHistory::~UndoRedoHistory()
{
}

void MeshUndoRedo_::UndoRedoHistory::setPosition(rv3 prevPosition)
{
	type = UndoRedoHistoryType::TRANSLATION;
	previousPosition = prevPosition;
}

void MeshUndoRedo_::UndoRedoHistory::setRotation(rm4 prevRotation)
{
	type = UndoRedoHistoryType::ROTATION;
	previousRotation = prevRotation;
}

void MeshUndoRedo_::UndoRedoHistory::setScale(rm4 prevScale)
{
	type = UndoRedoHistoryType::SCALE;
}

MeshUndoRedo_::HistoryIndexTracker::HistoryIndexTracker()
{
}

MeshUndoRedo_::HistoryIndexTracker::~HistoryIndexTracker()
{
}

void MeshUndoRedo_::HistoryIndexTracker::raiseStep()
{
	currentStepLevel++;
	if (maxStepLevel < currentStepLevel)
	{
		maxStepLevel = currentStepLevel;
	}
}

void MeshUndoRedo_::HistoryIndexTracker::lowerStep()
{
	currentStepLevel--;
	if (currentStepLevel < 0) // safety
	{
		currentStepLevel = 0;
	}
}

bool MeshUndoRedo_::HistoryIndexTracker::isCurrentBeyondCull()
{
	return maxStepLevel < cullLevel;
}

bool MeshUndoRedo_::HistoryIndexTracker::shouldCullMaxToCurrent()
{
	if (currentStepLevel < maxStepLevel)
	{
		return true;
	}
	return false;
}

int MeshUndoRedo_::HistoryIndexTracker::currentStep()
{
	return currentStepLevel;
}

int MeshUndoRedo_::HistoryIndexTracker::howManyToCull()
{
	return maxStepLevel - currentStepLevel;
}

bool MeshUndoRedo_::HistoryIndexTracker::isStepValid()
{
	return currentStep() > -1;
}
