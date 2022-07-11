#include "MeshUndoRedo.hpp"

MeshUndoRedo_::UndoRedo::UndoRedo()
{
}

MeshUndoRedo_::UndoRedo::~UndoRedo()
{
}

void MeshUndoRedo_::UndoRedo::saveOldToHistory()
{
	if (savedVertices.size() == 0)
	{
		return; // guard against saving empty changes.
	}
	say "Saving old vertices to history" done;
	this->history.emplace_back(UndoRedoHistory(savedVertices));
	this->savedVertices.clear();
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
