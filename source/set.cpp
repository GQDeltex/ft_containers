#include "../include/ft/set.hpp"
#include "Test.hpp"
#include "../include/ft/pairs.hpp"

void TestSet() {
	{
		Test test("Default Constructor checking size and empty");
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
	{
		Test test("Insert value");
		ft::set<char> st;
		test.equal(st.empty(), true, "Is empty in beginning");
		ft::pair<ft::set<char>::iterator,bool>back1 = st.insert('x');
		test.equal(back1.second, true, "Was inserted");
		// Check iterator to be at beginning
		test.equal(st.empty(), false, "Is not empty now");
		test.equal(st.size(), (unsigned long)1, "Is 1 long now");
		ft::pair<ft::set<char>::iterator,bool>back2 = st.insert('x');
		test.equal(back2.second, false, "Was not inserted");
		// Check iterator to be at beginning
		test.equal(st.empty(), false, "Is still not empty");
		test.equal(st.size(), (unsigned long)1, "Size is still 1");
	}
	{
		Test test("Iterators");
		ft::set<char> st;
		test.equal(st.empty(), true, "Is empty in beginning");
		st.insert('x');
		st.insert('g');
		st.insert('s');
		st.insert('k');
		st.insert('i');
		ft::set<char>::iterator begin = st.begin();
		ft::set<char>::iterator end = st.end();
		ft::set<char>::iterator it = begin;
		for(;it!=end;it++) {
			std::cout << "SET: " << *it << std::endl;
		}
		do {
			it--;
			std::cout << "SET: " << *it << std::endl;
		} while (it != begin);
	}
}
