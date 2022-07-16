#ifndef OrbitArray_HPP
#define OrbitArray_HPP

#include "CircleArray.hpp"
#include "MathDefinitions.hpp"

namespace OrbitArray_
{
	using namespace MathTypeDefinitions::CoordinateDefine;
	using CircleArray_::CircleArray;
	
	class OrbitArray : public CircleArray<v3>
	{
		public:
			
			OrbitArray() = delete;
			OrbitArray(bool makeX, bool makeY, bool makeZ, float setRadius = 10.0f);
			~OrbitArray();

			void sayCurrent();
			v3 getCurrent();

		private:
			float radius;
	};

}

#endif
