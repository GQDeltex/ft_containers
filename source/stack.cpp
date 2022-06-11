#include "Test.hpp"

#ifndef USE_STD
# define USE_STD 1
#endif

#if USE_STD == 1
# include <stack>
  namespace ft = std;
#else
# include "../include/ft/stack.hpp"
#endif

void TestStack() {
	{
		Test test("Default Constructor");
		ft::stack<std::string> stk;
		test.equal(stk.empty(), true);
	}
}
