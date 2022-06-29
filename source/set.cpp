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
	{
		Test test("Copy Constructor / Assignment operator");
		std::string str("abcdefghijklmnopqrstuvwxyz");
		ft::set<char> st1(str.begin(), str.end());
		test.equal(st1.empty(), false);
		test.equal(st1.size(), (unsigned long)26);
		ft::set<char> st2 = st1;
		test.equal(st2.empty(), false);
		test.equal(st2.size(), (unsigned long)26);
		ft::set<char> st3(st1);
		test.equal(st3.empty(), false);
		test.equal(st3.size(), (unsigned long)26);
	}
}
