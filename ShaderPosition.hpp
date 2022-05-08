#ifndef ShaderPosition_HPP
#define ShaderPosition_HPP

#include <string>
#include "Macro.hpp"

Usage Macros;


namespace ShaderPositionDefinition
{
	using std::string;
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
	};

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
	};

	extern ShaderPositionData ShaderSlotInfo;
}

#endif