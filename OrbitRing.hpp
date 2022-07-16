#ifndef OrbitRing_HPP
#define OrbitRing_HPP

#include "MathDefinitions.hpp"
#include <vector>;

namespace OrbitRing_
{
	using MathTypeDefinitions::CoordinateDefine::rv3;
	using MathTypeDefinitions::CoordinateDefine::v3;
	class OrbitRing 
	{
		public:
			OrbitRing(); 
			OrbitRing(int circleResolution, float diameter);
			~OrbitRing();

			void generateXYRing();
			void generateYZRing();



			rv3 left();
			rv3 right();

			rv3 operator[](int i);
		private:
			int internalIndex = 0; // internal index;
			int resolution = 360;
			float diameter = 10.0f;
			int getRealIndex(int i);
			std::vector<v3> imple; // internal implementation array

	};


}

#endif
