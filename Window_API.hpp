#ifndef Window_API_HPP
#define Window_API_HPP

#include "Window_Class.hpp"

#include "Macro.hpp"

#include "MainDirective.hpp"

Usage Macros;



namespace Window_API
{
	Usage Window_Class;

	// Hidden Structures.
	namespace Window_API_Structures
	{
		struct MouseCoordinates
		{
		public:
			Construct MouseCoordinates();
			Deconstruct ~MouseCoordinates();
			double msx;
			double msy;
		};

		struct WindowDimensions
		{
		public:
			Construct WindowDimensions();
			Deconstruct ~WindowDimensions();

			int width;
			int height;

			float aspectRatiof;
			float aspectRatioi;

		};

		struct ScreenData : public MouseCoordinates, public WindowDimensions
		{
		public:
			// this generates the info.
			Construct ScreenData();
			Deconstruct ~ScreenData();
			v4 translationVector;

		};
	}


	// what grants desired window data on call
	struct WindowAPIData
	{
		public:
			Construct WindowAPIData();
			Deconstruct ~WindowAPIData();
			Window_API_Structures::ScreenData& reload(); // reload and send out data.
		private:
			Window_API_Structures::ScreenData screendata;
	};

	extern WindowAPIData WinAPI; // this is what's exported and searched.


	struct MouseDeltaPosition
	{
		public:
			MouseDeltaPosition();
			~MouseDeltaPosition();

			void update();
			void getCurrent();
			v2 getDelta();
			
			v2 last;
			v2 current;
			v2 storedPos;
	};

	extern MouseDeltaPosition MouseDelta;

	namespace Global_Window_API_EnviromentVariables
	{
		extern v4 WindowBackgroundColor; // color of the background on OpenGL;
	}

	// functions that help control window and opengl functionalities in a compact manner with their APIs
	namespace Window_API_Functions
	{
		extern bool shouldNotClose();
		extern void clearBuffer();
		extern void eventQuery();

		extern void setMousePosition(double x, double y);
	}

}




#endif

