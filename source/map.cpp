#include "Test.hpp"

#ifndef USE_STD
# define USE_STD 0
#endif
#if USE_STD == 1
# include <map>
  namespace ft = std;
#else
# include "../include/ft/map.hpp"
#endif

void TestMap() {
	{
		Test test("Default constructor");
		ft::map<std::string, int>();
	}
}
