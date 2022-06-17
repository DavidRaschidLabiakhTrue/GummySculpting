#ifndef MeshToolsWindow_HPP
#define MeshToolsWindow_HPP

#include "Window_API.hpp"



namespace MeshToolsWindowDefinition
{
	using namespace Window_API;


	class MeshToolsWindow
	{
	public:
		MeshToolsWindow();
		~MeshToolsWindow();

		void build();
		void toggleWindow();
	};
}

#endif // !MeshToolsWindow_HPP

