#include "UndoRedo.hpp"

using UndoRedo_::HistoryIndex;

UndoRedo_::UndoRedo::UndoRedo()
{

}

UndoRedo_::UndoRedo::~UndoRedo()
{
}

bool UndoRedo_::UndoRedo::thereIsHistory()
{
	return history.size() > 0;
}

void UndoRedo_::UndoRedo::resetHistory()
{
	history.clear();
	this->stepTracker.resetStep();
}

void UndoRedo_::UndoRedo::cullCleanUp()
{
	if (stepTracker.shouldCullToMax())
	{
		const int cullAmount = stepTracker.getTotalToCull();

		for (int i = 0; i < cullAmount; i++)
		{
			history.pop_back();
		}

		stepTracker.setMaxToCurrent();
	}
}

void UndoRedo_::UndoRedo::storeSavedAndChanged()
{

	cullCleanUp();
	if (savedVertices.size() != 0)
	{
		if (stepTracker.current() == -1)
		{
			this->history.emplace_back(UndoRedoHistory(this->savedVertices)); // stored the *original vertices* // this is so we can *undo to this point*
			stepTracker.stepUp();
		}
			
		else
		{
			int current = stepTracker.current(); // this is the current position we exist on.

			forall(element, savedVertices)
			{
				history[current].undoMap[element.first] = element.second;
			}
		}

	
		say "Storing saved:" spc savedVertices.size() done;
	}
	else
	{
		say "No vertices in saved" done;
	}

	if (changedVertices.size() != 0)
	{
		this->history.emplace_back(UndoRedoHistory(this->changedVertices)); // store the *max total changed vertices* // this is so we can *redo to this point*

		stepTracker.stepUp(); // once for redo
		say "Storing changed:" spc changedVertices.size() done;;
	}
	else
	{
		say "No vertices in changed" done;
	}


	savedVertices.clear();
	changedVertices.clear();
}

void UndoRedo_::UndoRedo::displayUndoRedoData()
{
	if (verboseUndoRedo)
	{
		say "Current:" spc stepTracker.current() spc " Max:" spc stepTracker.max() done;
		say "Total History" spc history.size() done;
	}

}

void UndoRedo_::UndoRedo::sayStoring()
{
	if (verboseUndoRedo)
	{
		say "\nStoring to undo redo\n" done;
	}
}

void UndoRedo_::UndoRedo::sayUndoing()
{
	if (verboseUndoRedo)
	{
		say "\nUndoing\n" done;
	}
}

void UndoRedo_::UndoRedo::sayRedoing()
{
	if (verboseUndoRedo)
	{
		say "\nRedoing\n" done;
	}
}

bool UndoRedo_::UndoRedo::compareLevel(const int baseLevel, const int cmp)
{
	if (baseLevel == 0)
	{
		return false;
	}
	auto& cmpMap = history[baseLevel + cmp].undoMap;
	int cmpCount = 0;
	forall(element, history[baseLevel].undoMap)
	{
		if (cmpMap.contains(element.first) && cmpMap[element.first].compare(element.second)) // check existence and equality
		{
			cmpCount++;
			continue;
		}
		else
		{
			if (verboseUndoRedo)
			{
				say "Level" spc baseLevel spc "and" spc baseLevel - 1 spc "different, similar by" spc cmpCount spc "elements\n" done;

			}
			
			return false;
		}
	}
	if (verboseUndoRedo)
	{
		say "Map" spc baseLevel spc "is the same as" spc baseLevel - 1 spc "\n" done;
	}
	
	return true;
}

UndoRedo_::HistoryIndexController::HistoryIndexController()
{
}

UndoRedo_::HistoryIndexController::~HistoryIndexController()
{
}

void UndoRedo_::HistoryIndexController::stepUp()
{
	this->currentHistoryLevel++;
	if (currentHistoryLevel > maxHistoryLevel)
	{
		this->maxHistoryLevel++;
	}
}

void UndoRedo_::HistoryIndexController::stepDown()
{
	if (!(currentHistoryLevel - 1 < 0)) // if going down a level doesn't make the index negative
	{
		currentHistoryLevel--;
	}
}

bool UndoRedo_::HistoryIndexController::atTop()
{
	return currentHistoryLevel == maxHistoryLevel;
}

bool UndoRedo_::HistoryIndexController::canStepUp()
{
	return currentHistoryLevel < maxHistoryLevel;
}

bool UndoRedo_::HistoryIndexController::canStepDown()
{
	return currentHistoryLevel > 0;
}

bool UndoRedo_::HistoryIndexController::shouldCullToMax()
{
	return currentHistoryLevel < maxHistoryLevel;
}



HistoryIndex UndoRedo_::HistoryIndexController::current()
{
	return currentHistoryLevel;
}
HistoryIndex UndoRedo_::HistoryIndexController::max()
{
	return maxHistoryLevel;
}
using UndoRedo_::HistoryThreshold;

HistoryThreshold UndoRedo_::HistoryIndexController::threshold()
{
	return this->cullThreshold;
}

int UndoRedo_::HistoryIndexController::getAdjustment()
{
	return adjustment;
}

void UndoRedo_::HistoryIndexController::resetStep()
{
	this->currentHistoryLevel = -1;
	this->maxHistoryLevel = -1;
}

int UndoRedo_::HistoryIndexController::getTotalToCull()
{
	int res = maxHistoryLevel - currentHistoryLevel;
	if (res <= 0)
	{
		return 0;
	}
	return res;
}

void UndoRedo_::HistoryIndexController::setMaxToCurrent()
{
	maxHistoryLevel = currentHistoryLevel;
}

void UndoRedo_::HistoryIndexController::adjust()
{
	if (adjustment % 2 != 0)
	{
		adjustment = 2;
		return;
	}
	else
	{
		adjustment = 1;
		return;
	}
}

bool UndoRedo_::HistoryIndexController::shouldAdjust()
{
	return adjustment % 2 != 0;
}

UndoRedo_::UndoRedoHistory::UndoRedoHistory(UndoMap& undomap)
{
	this->undoMap = undomap;
}

UndoRedo_::UndoRedoHistory::UndoRedoHistory()
{

}

UndoRedo_::UndoRedoHistory::~UndoRedoHistory()
{

}

void UndoRedo_::UndoRedoHistory::setPosition(rv3 prevPosition)
{
	this->type = UndoRedoHistoryType::TRANSLATION;
	this->previousPosition = previousPosition;
}

void UndoRedo_::UndoRedoHistory::setRotation(rm4 prevRotation)
{
	this->type = UndoRedoHistoryType::ROTATION;
	this->matrix = prevRotation;
}

void UndoRedo_::UndoRedoHistory::setScale(rm4 prevScale)
{
	this->type = UndoRedoHistoryType::SCALE;
	this->matrix = prevScale;
}
