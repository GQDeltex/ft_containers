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
		Test test("Range Constructor / empty / size");
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
		Test test("Insert single value without hint");
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
		Test test("Insert single value with hint");
		ft::set<char> st;
		test.equal(st.empty(), true, "Is empty in beginning");
		ft::pair<ft::set<char>::iterator,bool>back2 = st.insert('x');
		ft::set<char>::iterator back3 = st.insert(back2.first, 'g');
		test.equal(*back3, 'g', "Iterator points to new value");
		test.equal(st.size(), (unsigned long)2, "Size is now 2");
		ft::set<char>::iterator back4 = st.insert(back3, 'g');
		test.equal(*back4, 'g', "Iterator points to old value");
		test.equal(back3, back4, "Iterators are the same");
		test.equal(st.size(), (unsigned long)2, "Size is still 2");
	}
	{
		Test test("Insert multiple elements from range");
		ft::set<char> st;
		std::string	str("Hello World");
		st.insert(str.begin(), str.end());
		test.equal(st.empty(), false, "Is not empty now");
		test.equal(st.size(), (unsigned long)8, "8 unique characters");
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
	{
		Test test("Reverse Iterators");
		ft::set<char> st;
		test.equal(st.empty(), true, "Is empty in beginning");
		st.insert('x');
		st.insert('g');
		st.insert('s');
		st.insert('k');
		st.insert('i');
		ft::set<char>::reverse_iterator begin = st.rbegin();
		ft::set<char>::reverse_iterator end = st.rend();
		ft::set<char>::reverse_iterator it = begin;
		for(;it!=end;it++) {
			std::cout << "SET: " << *it << std::endl;
		}
		do {
			it--;
			std::cout << "SET: " << *it << std::endl;
		} while (it != begin);

	}
	{
		Test test("max_size()");
		ft::set<char> st;
		test.equal(st.empty(), true, "Is empty in beginning");
		test.unequal(st.max_size(), (unsigned long)0, "Max size is not zero");
		st.insert('x');
		st.insert('g');
		std::cout << "Max Size: " << st.max_size() << std::endl;
	}
	{
		Test test("Delete one element from iterator");
		ft::set<char> st;
		std::string	str("Hello World");
		st.insert(str.begin(), str.end());
		test.equal(st.empty(), false, "Is not empty now");
		test.equal(st.size(), (unsigned long)8, "8 unique characters");
		ft::set<char>::iterator it = st.begin();
		it++;
		it++;
		st.erase(it);
		test.equal(st.empty(), false, "Is not empty now");
		test.equal(st.size(), (unsigned long)7, "7 unique characters");
	}
	{
		Test test("Delete one element from value");
		ft::set<char> st;
		std::string	str("Hello World");
		st.insert(str.begin(), str.end());
		test.equal(st.empty(), false, "Is not empty now");
		test.equal(st.size(), (unsigned long)8, "8 unique characters");
		size_t erased_elements = st.erase(' ');
		test.equal(st.empty(), false, "Is not empty now");
		test.equal(erased_elements, (unsigned long)1, "Erased 1 element");
		test.equal(st.size(), (unsigned long)7, "7 unique characters");
		erased_elements = st.erase(' ');
		test.equal(st.empty(), false, "Is not empty now");
		test.equal(erased_elements, (unsigned long)0, "Erased 0 element");
		test.equal(st.size(), (unsigned long)7, "7 unique characters");
	}
	{
		Test test("Delete one element from range");
		ft::set<char> st;
		std::string	str("Hello World");
		st.insert(str.begin(), str.end());
		test.equal(st.empty(), false, "Is not empty now");
		test.equal(st.size(), (unsigned long)8, "8 unique characters");
		st.erase(st.begin(), st.end());
		test.equal(st.empty(), true, "Is empty now");
		test.equal(st.size(), (unsigned long)0, "Is empty (0 elements)");
	}
	{
		Test test("Swapping one set with another");
		std::string	str1("Hello World");
		ft::set<char> st1;
		st1.insert(str1.begin(), str1.end());
		std::string str2("What's up?");
		ft::set<char> st2;
		st2.insert(str2.begin(), str2.end());

		ft::set<char>::iterator it1 = st1.begin();
		ft::set<char>::iterator it2 = st2.begin();
		ft::set<char>::iterator it1_1 = it1;
		ft::set<char>::iterator it2_1 = it2;

		ft::set<char> st1_1 = st1;
		ft::set<char> st2_1 = st2;

		st2.swap(st1);

		test.equal(it1, it1_1);
		test.equal(it2, it2_1);
		it1++;
		it2++;
		it1_1++;
		it2_1++;
		test.equal(it1, it1_1);
		test.equal(it2, it2_1);
		//test.equal(st1, st2_1);
		//test.equal(st2, st1_1);
	}
	{
		Test test("Clear the set");
		std::string	str("Hello World");
		ft::set<char> st;
		st.insert(str.begin(), str.end());
		test.equal(st.empty(), false, "Set is not empty");
		test.equal(st.size(), (unsigned long)8, "Size is 8");
		st.clear();
		test.equal(st.empty(), true, "Set is empty");
		test.equal(st.size(), (unsigned long)0, "Size is 0");
	}
}
