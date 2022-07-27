#ifndef Toolbar_HPP
#define Toolbar_HPP

#include "Window_API.hpp"
#include "TopBar.hpp"

#include "MainDirective.hpp"


namespace ToolbarDefinition
{
	using namespace Window_API;
	using namespace TopBarDefinition;

	// a gui class that enables a toolbar in gummy
	class Toolbar
	{
	public:
		Toolbar();
		~Toolbar();

		void build();
		
		TopBar topBar;
	};
}

#endif // !Toolbar_HPP

