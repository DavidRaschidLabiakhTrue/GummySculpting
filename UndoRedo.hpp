#ifndef UndoRedo_HPP
#define UndoRedo_HPP


#include "MathDefinitions.hpp"
#include "GraphicsData.hpp"

#include <deque>
#include <unordered_map>


namespace UndoRedo_
{
	using namespace GraphicsDataDefinition;
	using std::unordered_map;
	using namespace MathTypeDefinitions::MatrixDefine;
	using std::deque;


	typedef unordered_map<KeyData, V3D> UndoMap; // the extra slots used here are really showing themselves.
	
	enum UndoRedoHistoryType
	{
		TRANSLATION,
		ROTATION,
		SCALE,
		STROKE, // unused
		FULL_MESH,// unused
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
			m4 matrix;

	};

	typedef deque<UndoRedoHistory> HistoryList;
	typedef int HistoryIndex;
	typedef int HistoryThreshold;

	class HistoryIndexController
	{
		public:
			HistoryIndexController();
			~HistoryIndexController();

			void stepUp(); // kick current up 1, and max up one to match it if needed
			void stepDown(); // kick current down 1 if kicking down doesn't make it negative

			bool atTop(); // check if we are at the top of the history list

			bool canStepUp(); // Redo Check - Check if we can take a step up in the history list - if current less than max
			bool canStepDown(); // Undo Check - Check if we can take a step down in the history list - if 0 or below, No.


			bool shouldCullToMax(); // check if there is history ahead of current position when wanting to add a new entry

			// getters
			HistoryIndex current();
			HistoryIndex max();
			HistoryThreshold threshold();

			int getAdjustment();


			void resetStep();

			int getTotalToCull();
			void setMaxToCurrent();

			void adjust();

			bool shouldAdjust();



		private:
			// these values should be handled purely through methods
			HistoryIndex currentHistoryLevel = -1; 
			HistoryIndex maxHistoryLevel = -1;
			HistoryThreshold cullThreshold = 90;
			int adjustment = 0;


	};

	class UndoRedo
	{
		public:
		UndoRedo();
		~UndoRedo();

		bool thereIsHistory(); // safety check there is history in the history list
		void resetHistory();

		void cullCleanUp(); // check if we are trying to add vertices with history already in front of current and clean up if so

		void storeSavedAndChanged();

		void displayUndoRedoData();

		void sayStoring();
		void sayUndoing();
		void sayRedoing();

		bool compareLevel(const int baseLevel, const int cmp); // Sanity Check

		UndoMap currentVertices; // set of vertices being operated on
		UndoMap savedVertices; // original set of vertices that are being stored to history.
		UndoMap changedVertices; // map containing the total of new positions changed to in a stroke.

		bool needToStore = false;
		bool verboseUndoRedo = true;
		HistoryList history;
		HistoryIndexController stepTracker;

	};
}

#endif
