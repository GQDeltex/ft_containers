#include "Test.hpp"
#include <string>

#ifndef USE_STD
# define USE_STD 0
#endif

#if USE_STD == 0
# include "../include/ft/is_integral.hpp"
#else
# include <type_traits>
  namespace ft = std;
#endif

void TestIsIntegral() {
	{
		Test test("Is int integral");
		test.equal(ft::is_integral<int>::value, true);
	}
	{
		Test test("Is bool integral");
		test.equal(ft::is_integral<bool>::value, true);
	}
	{
		Test test("Is float not integral");
		test.equal(ft::is_integral<float>::value, false);
	}
	{
		Test test("Is std::string not integral");
		test.equal(ft::is_integral<std::string>::value, false);
	}
}
