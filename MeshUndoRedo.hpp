#ifndef MeshUndoRedo_HPP
#define MeshUndoRedo_HPP


#include <unordered_map>
#include "MathDefinitions.hpp"
#include "GraphicsData.hpp"

#include <deque>

#include <stack>

namespace MeshUndoRedo_
{
	using namespace GraphicsDataDefinition;
	using std::unordered_map;
	using namespace MathTypeDefinitions::MatrixDefine;
	using std::deque;
	using std::stack;

	typedef unordered_map<KeyData, V3D> UndoMap; // the extra slots used here are really showing themselves.

	enum UndoRedoHistoryType
	{
		TRANSLATION,
		ROTATION,
		SCALE,
		STROKE,
		FULL_MESH,
		UNSET
	};


	struct UndoRedoHistory
	{
		public:
			UndoRedoHistory(UndoMap& undomap);
			UndoRedoHistory();
			~UndoRedoHistory();

			void setPosition(rv3 prevPosition);
			void setRotation(rm4 prevRotation);
			void setScale(rm4 prevScale);
			

			UndoRedoHistoryType type = UndoRedoHistoryType::UNSET;
			UndoMap undoMap;
			v3 previousPosition;
			m4 previousRotation;
			m4 previousScale;
	};

	typedef deque<UndoRedoHistory> HistoryList;
	typedef deque<UndoRedoHistory> RedoStack;
	
	class HistoryIndexTracker
	{
		public:
			HistoryIndexTracker();
			~HistoryIndexTracker();

			void raiseStep();
			void lowerStep();

			void resetStep();

			void synchronizeMaxStepWithCurrentStep();

			bool isCurrentBeyondCull(); // safety check if the current is beyond the cull point.

			bool shouldCullMaxToCurrent(); // check if a new step is made but there is history on top of the position, cull memory otherwise

			bool currentStepIsLessOrEqualThanMaxStep(); // checks if the current step is not equal to the max step. if the current step < max step, this is used to *redo* a vertex map


			int currentStep(); // get the current step level
			int maxStep();
			int howManyToCull();
			bool isStepValid();
		private:
			int currentStepLevel = -1;
			int maxStepLevel = -1;
			int cullLevel = 64; // if history makes it this far, cull half of the current slots in memory.

	};

	class UndoRedo
	{
		public:
			UndoRedo();
			~UndoRedo();
			
			void saveOldToHistory();
			bool isThereHistory();
			void clearSaved();
			bool isThereCurrentVerticesBeingSculpted();
			void displayCurrentHistoryCount();
			
			void emptyOutHistory();

			void displayStep();

			void displayUndoRedoStat();

			bool canMeshRedo();
			bool stackIsNotEmpty();
			HistoryIndexTracker stepTracker;

			// a vector is a bad idea to use for this as it can't be culled directly.
			UndoMap currentVertices; // set of vertices being operated on
			UndoMap savedVertices; // original set of vertices that are being stored to history.
			HistoryList history; // a deque is much better as we can cull memory as needed.
			RedoStack redoStack;
			bool needToStore = false;

	};
}

#endif
