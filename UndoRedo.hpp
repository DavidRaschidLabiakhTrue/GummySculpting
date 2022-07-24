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
			UndoRedoHistory(UndoMap& undomap) noexcept;
			UndoRedoHistory(rv3 translation) noexcept;
			UndoRedoHistory(rm4 mat, UndoRedoHistoryType typeOfMatrix) noexcept;

			UndoRedoHistory() noexcept;
			~UndoRedoHistory() noexcept;

			void setPosition(rv3 prevPosition) noexcept;
			void setRotation(rm4 prevRotation) noexcept;
			void setScale(rm4 prevScale) noexcept;


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
			HistoryIndexController() noexcept;
			~HistoryIndexController() noexcept;

			void stepUp() noexcept; // kick current up 1, and max up one to match it if needed
			void stepDown() noexcept; // kick current down 1 if kicking down doesn't make it negative

			bool atTop() noexcept; // check if we are at the top of the history list

			bool canStepUp() noexcept; // Redo Check - Check if we can take a step up in the history list - if current less than max
			bool canStepDown() noexcept; // Undo Check - Check if we can take a step down in the history list - if 0 or below, No.


			bool shouldCullToMax() noexcept; // check if there is history ahead of current position when wanting to add a new entry

			// getters
			HistoryIndex current() noexcept;
			HistoryIndex max() noexcept;
			HistoryThreshold threshold() noexcept;

			int getAdjustment() noexcept;


			void resetStep() noexcept;

			int getTotalToCull() noexcept;
			void setMaxToCurrent() noexcept;

			void adjust() noexcept;

			bool shouldAdjust() noexcept;



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
		UndoRedo() noexcept;
		~UndoRedo() noexcept;

		bool thereIsHistory() noexcept; // safety check there is history in the history list
		void resetHistory() noexcept;

		void cullCleanUp() noexcept; // check if we are trying to add vertices with history already in front of current and clean up if so

		void storeSavedAndChanged() noexcept;

		void displayUndoRedoData() noexcept;

		void sayStoring() noexcept;
		void sayUndoing() noexcept;
		void sayRedoing() noexcept;

		void storeTranslation(rv3 translation) noexcept;
		void storeRotation(rm4 rotation) noexcept;
		void storeScale(rm4 scale) noexcept;


		bool compareLevel(const int baseLevel, const int cmp) noexcept; // Sanity Check

		UndoMap currentVertices; // set of vertices being operated on
		UndoMap savedVertices; // original set of vertices that are being stored to history.
		UndoMap changedVertices; // map containing the total of new positions changed to in a stroke.

		bool needToStore = false;
		bool verboseUndoRedo = false;
		HistoryList history;
		HistoryIndexController stepTracker;

	};
}

#endif
