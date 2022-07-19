#include "UndoRedo.hpp"

using UndoRedo_::HistoryIndex;

UndoRedo_::UndoRedo::UndoRedo() noexcept
{

}

UndoRedo_::UndoRedo::~UndoRedo() noexcept
{
}

bool UndoRedo_::UndoRedo::thereIsHistory() noexcept
{
	return history.size() > 0;
}

void UndoRedo_::UndoRedo::resetHistory() noexcept
{
	history.clear();
	this->stepTracker.resetStep();
}

void UndoRedo_::UndoRedo::cullCleanUp() noexcept
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

void UndoRedo_::UndoRedo::storeSavedAndChanged() noexcept
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

void UndoRedo_::UndoRedo::displayUndoRedoData() noexcept
{
	if (verboseUndoRedo)
	{
		say "Current:" spc stepTracker.current() spc " Max:" spc stepTracker.max() done;
		say "Total History" spc history.size() done;
	}

}

void UndoRedo_::UndoRedo::sayStoring() noexcept
{
	if (verboseUndoRedo)
	{
		say "\nStoring to undo redo\n" done;
	}
}

void UndoRedo_::UndoRedo::sayUndoing() noexcept
{
	if (verboseUndoRedo)
	{
		say "\nUndoing\n" done;
	}
}

void UndoRedo_::UndoRedo::sayRedoing() noexcept
{
	if (verboseUndoRedo)
	{
		say "\nRedoing\n" done;
	}
}

void UndoRedo_::UndoRedo::storeTranslation(rv3 translation) noexcept
{
	this->history.emplace_back(UndoRedoHistory(translation));
}

void UndoRedo_::UndoRedo::storeRotation(rm4 rotation) noexcept
{
	this->history.emplace_back(UndoRedoHistory(rotation, UndoRedoHistoryType::ROTATION));
}

void UndoRedo_::UndoRedo::storeScale(rm4 scale) noexcept
{
	this->history.emplace_back(UndoRedoHistory(scale, UndoRedoHistoryType::SCALE));
}

bool UndoRedo_::UndoRedo::compareLevel(const int baseLevel, const int cmp) noexcept
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

UndoRedo_::HistoryIndexController::HistoryIndexController() noexcept
{
}

UndoRedo_::HistoryIndexController::~HistoryIndexController() noexcept
{
}

void UndoRedo_::HistoryIndexController::stepUp() noexcept
{
	this->currentHistoryLevel++;
	if (currentHistoryLevel > maxHistoryLevel)
	{
		this->maxHistoryLevel++;
	}
}

void UndoRedo_::HistoryIndexController::stepDown() noexcept
{
	if (!(currentHistoryLevel - 1 < 0)) // if going down a level doesn't make the index negative
	{
		currentHistoryLevel--;
	}
}

bool UndoRedo_::HistoryIndexController::atTop() noexcept
{
	return currentHistoryLevel == maxHistoryLevel;
}

bool UndoRedo_::HistoryIndexController::canStepUp() noexcept
{
	return currentHistoryLevel < maxHistoryLevel;
}

bool UndoRedo_::HistoryIndexController::canStepDown() noexcept
{
	return currentHistoryLevel > 0;
}

bool UndoRedo_::HistoryIndexController::shouldCullToMax() noexcept
{
	return currentHistoryLevel < maxHistoryLevel;
}



HistoryIndex UndoRedo_::HistoryIndexController::current() noexcept
{
	return currentHistoryLevel;
}
HistoryIndex UndoRedo_::HistoryIndexController::max() noexcept
{
	return maxHistoryLevel;
}
using UndoRedo_::HistoryThreshold;

HistoryThreshold UndoRedo_::HistoryIndexController::threshold() noexcept
{
	return this->cullThreshold;
}

int UndoRedo_::HistoryIndexController::getAdjustment() noexcept
{
	return adjustment;
}

void UndoRedo_::HistoryIndexController::resetStep() noexcept
{
	this->currentHistoryLevel = -1;
	this->maxHistoryLevel = -1;
}

int UndoRedo_::HistoryIndexController::getTotalToCull() noexcept
{
	int res = maxHistoryLevel - currentHistoryLevel;
	if (res <= 0)
	{
		return 0;
	}
	return res;
}

void UndoRedo_::HistoryIndexController::setMaxToCurrent() noexcept
{
	maxHistoryLevel = currentHistoryLevel;
}

void UndoRedo_::HistoryIndexController::adjust() noexcept
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

bool UndoRedo_::HistoryIndexController::shouldAdjust() noexcept
{
	return adjustment % 2 != 0;
}

UndoRedo_::UndoRedoHistory::UndoRedoHistory(UndoMap& undomap) noexcept
{
	this->undoMap = undomap;
}

UndoRedo_::UndoRedoHistory::UndoRedoHistory(rv3 translation) noexcept
{
	setPosition(translation);
}

UndoRedo_::UndoRedoHistory::UndoRedoHistory(rm4 mat, UndoRedoHistoryType typeOfMatrix) noexcept
{
	type = typeOfMatrix;
	this->matrix = mat;
}

UndoRedo_::UndoRedoHistory::UndoRedoHistory() noexcept
{

}

UndoRedo_::UndoRedoHistory::~UndoRedoHistory() noexcept
{

}

void UndoRedo_::UndoRedoHistory::setPosition(rv3 prevPosition) noexcept
{
	this->type = UndoRedoHistoryType::TRANSLATION;
	this->previousPosition = previousPosition;
}

void UndoRedo_::UndoRedoHistory::setRotation(rm4 prevRotation) noexcept
{
	this->type = UndoRedoHistoryType::ROTATION;
	this->matrix = prevRotation;
}

void UndoRedo_::UndoRedoHistory::setScale(rm4 prevScale) noexcept
{
	this->type = UndoRedoHistoryType::SCALE;
	this->matrix = prevScale;
}
