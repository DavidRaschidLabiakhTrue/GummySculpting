#ifndef Macro_HPP
#define Macro_HPP

#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>



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

	#define say std::cout <<
	#define spc << " " <<
	#define done << '\n'
	#define forall(item,items) for(auto &item: (items))
	#define foreach(item,items) for(auto &item: (items))

	#define variableVariantType variant<reference_wrapper<int>, reference_wrapper<float>, reference_wrapper<bool>>

	#define getNThreads glm::max(1, (int)std::thread::hardware_concurrency())
	#define joinThreads foreach(t, threads) {t.join();}
	#define joinAndClearThreads joinThreads threads.clear();

	#define timerStart auto start = std::chrono::system_clock::now()
	#define timerEnd(name) say name spc "elapsed time" spc (std::chrono::duration<double>(std::chrono::system_clock::now() - start)).count() << "s" done
}




#endif

