#include "../include/ft/set.hpp"
#include "Test.hpp"

void TestSet() {
	{
		Test test("Default Constructor");
		ft::set<char> st;
		test.equal(st.size(), (unsigned long)0);
		test.equal(st.empty(), true);
	}
	{
		Test test("Range Constructor");
		std::string str("abcdefghijklmnopqrstuvwxyz");
		ft::set<char> st(str.begin(), str.end());
		test.equal(st.empty(), false);
		test.equal(st.size(), (unsigned long)26);
	}
}
