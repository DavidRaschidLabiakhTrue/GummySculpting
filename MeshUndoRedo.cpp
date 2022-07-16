#include "MeshUndoRedo.hpp"
//
//MeshUndoRedo_::UndoRedo::UndoRedo()
//{
//}
//
//MeshUndoRedo_::UndoRedo::~UndoRedo()
//{
//}
//
//void MeshUndoRedo_::UndoRedo::saveOldToHistory()
//{
//
//	if (isThereCurrentVerticesBeingSculpted() == false)
//	{
//		return; // guard against saving empty changes.
//	}
//
//	
//
//	if (stepTracker.shouldCullMaxToCurrent()) // if there are elements beyond our current position, we are creating a new branch so we should pop the old branch.
//	{
//		int cullAmount = stepTracker.howManyToCull(); // suspect
//
//		for (int i = 0; i < cullAmount; i++)
//		{
//			history.pop_back();
//		}
//
//		stepTracker.synchronizeMaxStepWithCurrentStep();
//		say "Removed" spc cullAmount spc "entries of history from the back" done;
//		
//	}
//	
//	this->history.emplace_back(UndoRedoHistory(savedVertices));
//
//	stepTracker.raiseStep();
//	clearSaved();
//
//	displayUndoRedoStat();
//}
//
//bool MeshUndoRedo_::UndoRedo::isThereHistory()
//{
//	return history.size() > 0;
//}
//
//void MeshUndoRedo_::UndoRedo::clearSaved()
//{
//	savedVertices.clear();
//}
//
//bool MeshUndoRedo_::UndoRedo::isThereCurrentVerticesBeingSculpted()
//{
//	if (currentVertices.size() > 0)
//	{
//		return true;
//	}
//	return false;
//}
//
//void MeshUndoRedo_::UndoRedo::displayCurrentHistoryCount()
//{
//	say "history has" spc history.size() spc "slots being used" done;
//}
//
//void MeshUndoRedo_::UndoRedo::emptyOutHistory()
//{
//	const int elementsToPop = history.size();
//	say "clearing history" done;
//	for (int i = 0; i < elementsToPop; i++)
//	{
//		history.pop_front();
//	}
//
//	stepTracker.resetStep();
//	displayUndoRedoStat();
//}
//
//void MeshUndoRedo_::UndoRedo::displayStep()
//{
//	say "Current Step" spc stepTracker.currentStep() done;
//	say "Current Max Step" spc stepTracker.maxStep() done;
//}
//
//void MeshUndoRedo_::UndoRedo::displayUndoRedoStat()
//{
//	say "\n";
//	displayCurrentHistoryCount();
//	displayStep();
//	
//}
//
//bool MeshUndoRedo_::UndoRedo::canMeshRedo()
//{
//	bool canStepForward = stepTracker.currentStep() < stepTracker.maxStep();
//	if (canStepForward)
//	{
//		say "The Mesh *can* step" done;
//	}
//	else
//	{
//		say "The Mesh *cannot* step" done;
//	}
//
//	// deque with size 1 means 1 element at 0
//	// deque with size 2 means 2 elements at 0, 1
//
//	
//
//	bool doesNotExceedBounds = stepTracker.currentStep() + 1 < history.size();
//	
//	if (doesNotExceedBounds)
//	{
//		say "Redoing does not exceed bounds" done;
//	}
//	else
//	{
//		say "Redoing exceeds bounds at step:" spc stepTracker.currentStep() spc "with size:" spc history.size() done;
//	}
//
//	return canStepForward && doesNotExceedBounds;
//}
//
//bool MeshUndoRedo_::UndoRedo::stackIsNotEmpty()
//{
//	return redoStack.size() > 0;
//}
//
//
//
//MeshUndoRedo_::UndoRedoHistory::UndoRedoHistory(UndoMap& undomap)
//{
//	this->undoMap = undomap;
//}
//
//MeshUndoRedo_::UndoRedoHistory::UndoRedoHistory()
//{
//}
//
//MeshUndoRedo_::UndoRedoHistory::~UndoRedoHistory()
//{
//}
//
//void MeshUndoRedo_::UndoRedoHistory::setPosition(rv3 prevPosition)
//{
//	type = UndoRedoHistoryType::TRANSLATION;
//	previousPosition = prevPosition;
//}
//
//void MeshUndoRedo_::UndoRedoHistory::setRotation(rm4 prevRotation)
//{
//	type = UndoRedoHistoryType::ROTATION;
//	previousRotation = prevRotation;
//}
//
//void MeshUndoRedo_::UndoRedoHistory::setScale(rm4 prevScale)
//{
//	type = UndoRedoHistoryType::SCALE;
//}
//
//MeshUndoRedo_::HistoryIndexTracker::HistoryIndexTracker()
//{
//}
//
//MeshUndoRedo_::HistoryIndexTracker::~HistoryIndexTracker()
//{
//}
//
//void MeshUndoRedo_::HistoryIndexTracker::raiseStep()
//{
//	currentStepLevel++;
//	if (maxStepLevel < currentStepLevel)
//	{
//		maxStepLevel = currentStepLevel;
//	}
//}
//
//void MeshUndoRedo_::HistoryIndexTracker::lowerStep()
//{
//	currentStepLevel--;
//	if (currentStepLevel < 0) // safety
//	{
//		currentStepLevel = 0;
//	}
//}
//
//void MeshUndoRedo_::HistoryIndexTracker::resetStep()
//{
//	currentStepLevel = 0;
//	maxStepLevel = 0;
//}
//
//void MeshUndoRedo_::HistoryIndexTracker::synchronizeMaxStepWithCurrentStep()
//{
//	maxStepLevel = currentStepLevel;
//}
//
//bool MeshUndoRedo_::HistoryIndexTracker::isCurrentBeyondCull()
//{
//	return maxStepLevel < cullLevel;
//}
//
//bool MeshUndoRedo_::HistoryIndexTracker::shouldCullMaxToCurrent()
//{
//	if (currentStepLevel < maxStepLevel)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool MeshUndoRedo_::HistoryIndexTracker::currentStepIsLessOrEqualThanMaxStep()
//{
//	return currentStep() < maxStep();
//}
//
//int MeshUndoRedo_::HistoryIndexTracker::currentStep()
//{
//	return currentStepLevel;
//}
//
//int MeshUndoRedo_::HistoryIndexTracker::maxStep()
//{
//	return maxStepLevel;
//}
//
//int MeshUndoRedo_::HistoryIndexTracker::howManyToCull()
//{
//	return maxStepLevel - currentStepLevel;
//}
//
//bool MeshUndoRedo_::HistoryIndexTracker::isStepValid()
//{
//	return currentStep() > -1;
//}
