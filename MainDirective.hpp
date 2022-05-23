#ifndef MainDirective_HPP
#define MainDirective_HPP

#include <vector>
#include <string>

namespace MainDirectiveDefinition
{
	using std::string;
	using std::vector;

	typedef vector<vector<string>> DirectiveList;

	extern DirectiveList Directives;

}

#endif
