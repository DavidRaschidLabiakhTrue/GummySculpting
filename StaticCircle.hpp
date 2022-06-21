#ifndef StaticCircle_HPP
#define StaticCircle_HPP

#include "StaticMesh.hpp"
#include "IndiceList.hpp"
namespace StaticCircleDefinition
{
	using namespace StaticMeshDefinition;
	using IndiceListDefinition::IndiceList;

	class StaticCircle : public StaticMesh, public IndiceList
	{
		public:
		StaticCircle();
		StaticCircle(bool trueConstructor);
		void bindCircle();
		void refreshCircle();



		void drawCircle();

		~StaticCircle();

		float diameter = 1.0f;
		float radius = 0.5f;

		


	};
}

#endif
