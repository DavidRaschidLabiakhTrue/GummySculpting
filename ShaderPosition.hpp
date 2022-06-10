#ifndef ShaderPosition_HPP
#define ShaderPosition_HPP

#include <string>
#include "Macro.hpp"

Usage Macros;


namespace ShaderPositionDefinition
{
	using std::string;
	// represents hard coded constants used for binding
	class ShaderPosition
	{
		public:
		Construct ShaderPosition();
		Deconstruct ~ShaderPosition();

		int position;
		string slot;

		void loadPosition(); // load position shader data
		void loadColor(); // load color shader data
		void loadWeight(); // load weight shader data

		void loadCameraMatrix(); // load camera matrix shader data
		void loadModelMatrix(); // load model matrix shader data
		void loadProjectionMatrix();
		void loadViewMatrix();

		void loadOffset();
		void loadScale();
		void loadStaticColor();
		void loadStaticColorBool();
		void loadRandomColor();

		void loadTimeModifier();
	};

	// basically a global constant that contains all relevant data needed.
	class ShaderPositionData
	{
		public:
		Construct ShaderPositionData();
		Construct ~ShaderPositionData();

		ShaderPosition position;
		ShaderPosition color;
		ShaderPosition data;
		ShaderPosition cameraMatrix;
		ShaderPosition modelMatrix;
		ShaderPosition projection;
		ShaderPosition view;
		ShaderPosition offset;
		ShaderPosition scale;
		ShaderPosition staticColor;
		ShaderPosition staticColorBool;
		ShaderPosition randomColor;
		ShaderPosition timeModifier;
	};

	extern ShaderPositionData ShaderSlotInfo;
}

#endif