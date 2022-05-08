#ifndef Macro_HPP
#define Macro_HPP

#include <iostream>
#include <vector>
#include <string>

typedef std::vector<std::string> StringList; // Traces of vector<> are bad for readability.

namespace Macros
{
	using namespace std;
	// specify deconstructor
	#define Deconstruct 
	// specify Constructor
	#define Construct 
	// specify Empty Constructor to silence C++
	#define Empty_Construct

	#define Public_Variables

	#define Special_Operators

	// Cleaner Name Space Mechanic.
	#define Usage using namespace

	#define UnassignedPTR NULL

	#define ifn(x) if ((x) == NULL)

	#define eif(x) else if((x))

	#define TrueConstructor true
	
	#define FileNotOpen NULL

	#define say cout <<
	#define spc << " " << 
	#define done << '\n'
	#define forall(item,items) for(auto &item: (items))
}




#endif

