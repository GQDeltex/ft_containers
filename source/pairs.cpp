#include "Test.hpp"

#ifndef USE_STD
# define USE_STD 1
#endif

#if USE_STD == 1
# include <utility>
  namespace ft = std;
#else
# include "../include/ft/pairs.hpp"
#endif

void TestPairs() {
	{
		Test test("Create Pair");
		ft::pair<int, char> pr;
		pr.first = 4;
		pr.second = 'x';
		test.equal(pr.first, 4);
		test.equal(pr.second, 'x');
	}
	{
		Test test("make_pairs");
		ft::pair<int, char> pr = ft::make_pair(4, 'x');
		test.equal(pr.first, 4);
		test.equal(pr.second, 'x');
	}
}
