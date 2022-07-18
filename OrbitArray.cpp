#include "OrbitArray.hpp"



OrbitArray_::OrbitArray::OrbitArray(bool makeX, bool makeY, bool makeZ, float setRadius) : CircleArray(360)
{
	//radius = setRadius;

	//const float diameter = radius * 2.0f;
	//float heading;

	//if (makeX && makeY)
	//{
	//	for (int i = 0; i < resolution; i++)
	//	{
	//		heading = glm::radians((float)i);

	//		impl.emplace_back(v3(cos(heading), sin(heading), 0.0f));
	//	}
	//}
	//else if (makeY && makeZ)
	//{
	//	for (int i = 0; i < resolution; i++)
	//	{
	//		heading = glm::radians((float)i);
	//		v3 temp = v3(cos(heading), sin(heading), 0.0f);
	//		temp.z = temp.x;
	//		temp.x = 0.0f;
	//		

	//		impl.emplace_back(temp);
	//	}
	//}
	//else if (makeX && makeZ)
	//{
	//	for (int i = 0; i < resolution; i++)
	//	{
	//		heading = glm::radians((float)i);
	//		v3 temp = v3(cos(heading), sin(heading), 0.0f);
	//		temp.z = temp.y;
	//		temp.y = 0.0f;

	//		impl.emplace_back(temp);
	//	}
	//	auto swapLimit = resolution / 2;

	//	for (int i = 0; i < swapLimit; i++)
	//	{
	//		v3 temp = impl[i];
	//		v3 temp2 = impl[resolution - i];

	//		impl[i] = temp2;
	//		impl[resolution - 1] = temp;
	//	}
	//}
	//else
	//{
	//	// Don't be fucking stupid and try to use all 3, it's a circle.
	//}

}

OrbitArray_::OrbitArray::~OrbitArray()
{
}

using namespace MathTypeDefinitions::CoordinateDefine;
void OrbitArray_::OrbitArray::sayCurrent()
{
	auto augmentedPosition = radius * current();
	say position spc to_string(augmentedPosition) done;
}
v3 OrbitArray_::OrbitArray::getCurrent()
{
	return radius * current();
}
