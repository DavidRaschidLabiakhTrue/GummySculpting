#include "MeshUndoRedo.hpp"

MeshUndoRedo_::UndoRedo::UndoRedo()
{
}

MeshUndoRedo_::UndoRedo::~UndoRedo()
{
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
