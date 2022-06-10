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

		float radius = 3.0f;

		


	};
}

#endif
