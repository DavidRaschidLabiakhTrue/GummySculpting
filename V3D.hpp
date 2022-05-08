#ifndef V3D_HPP
#define V3D_HPP

#include "MathDefinitions.hpp"
#include <vector>
#define NOTUSINGNORMALORUV

namespace VertexDefinition
{
	Usage MathTypeDefinitions::CoordinateDefine;
	using std::vector;
	// formal definition of a vertex structure
	typedef unsigned int BitData; // used to clarify this data will only ever be accessed with bits.

	namespace GlobalVertexParameters
	{
		extern const float DefaultAlphaValue;
		extern const v4 DefaultColorLoader;
		extern const BitData DefaultBinaryWeightData;
	}

	struct V3D
	{
		public:
		Construct V3D();
		Construct V3D(float x, float y, float z);
		Construct V3D(float x, float y, float z, float r, float g, float b);
		Deconstruct ~V3D();


		void operator=(v3 newPosition);
		void operator=(rv3 newPosition);
		void operator=(v4 newColor);
		void operator=(rv4 newColor);

		void operator +=(v3 positionOffset);
		void operator -=(v3 positionOffset);

		void operator +=(v4 addColor);
		void operator -=(rv4 subtractColor);


	



		v3 position;
		v4 color; // shrink to v3 eventually.
		BitData bitData; // reserve first 14 starting from right to represent weight data with a resolution of 100.00 total.
#ifndef NOTUSINGNORMALORUV
		// Don't use these unless specified. They aren't needed.
		v3 normal;
		v2 uv;
#endif // !NOTUSINGNORMALORUV
	};

	typedef V3D& RV3D;
	typedef vector<V3D> Vertices;


}



#endif // !V3D_HPP
