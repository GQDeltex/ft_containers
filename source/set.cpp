#include "../include/ft/set.hpp"
#include "Test.hpp"

void TestSet() {
	{
		Test test("Default Constructor");
		ft::set<char> st;
		test.unequal(st, NULL);
	}
}
