#include "Test.hpp"
#include <vector>

#ifndef USE_STD
# define USE_STD 0
#endif
#if USE_STD == 1
# include <map>
  namespace ft = std;
#else
# include "../include/ft/map.hpp"
# include "../include/ft/pairs.hpp"
#endif

static void add_numbers(ft::map<int, int>& myMap) {
	myMap.insert(ft::pair<int, int>(50, 1));
    myMap.insert(ft::pair<int, int>(30, 2));
    myMap.insert(ft::pair<int, int>(70, 3));
    myMap.insert(ft::pair<int, int>(20, 4));
    myMap.insert(ft::pair<int, int>(80, 5));
    myMap.insert(ft::pair<int, int>(40, 6));
    myMap.insert(ft::pair<int, int>(60, 7));
    myMap.insert(ft::pair<int, int>(31, 8));
    myMap.insert(ft::pair<int, int>(55, 9));
    myMap.insert(ft::pair<int, int>(75, 10));
    myMap.insert(ft::pair<int, int>(53, 11));
    myMap.insert(ft::pair<int, int>(76, 12));
    myMap.insert(ft::pair<int, int>(35, 13));
    myMap.insert(ft::pair<int, int>(57, 14));
}

void TestMap() {
	ft::map<int, int> test_data;
	add_numbers(test_data);
	{
		Test test("Default constructor");
		ft::map<std::string, int> mp;
		test.equal(mp.size(), (unsigned long)0, "Size is zero");
		test.equal(mp.empty(), true, "Map is empty");
	}
	{
		Test test("Range Constructor / empty / size");
		ft::map<int, int> mp(test_data.begin(), test_data.end());
		test.equal(mp.empty(), false, "Map 2 is not empty");
		test.equal(mp.size(), (size_t)14, "Size is 14");
	}
	{
		Test test("Copy Constructor / Assignment operator");
		ft::map<int, int> mp1(test_data.begin(), test_data.end());
		test.equal(mp1.empty(), false);
		test.equal(mp1.size(), (size_t)14);
		ft::map<int, int> mp2 = mp1;
		test.equal(mp2.empty(), false);
		test.equal(mp2.size(), (size_t)14);
		ft::map<int, int> st3(mp1);
		test.equal(st3.empty(), false);
		test.equal(st3.size(), (size_t)14);
	}
	{
		Test test("Insert single value without hint");
		ft::map<int, int> mp;
		test.equal(mp.empty(), true, "Is empty in beginning");
		ft::pair<ft::map<int, int>::iterator,bool>back1 = mp.insert(ft::pair<int, int>(10, 30));
		test.equal(back1.second, true, "Was inserted");
		// Check iterator to be at beginning
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (unsigned long)1, "Is 1 long now");
		ft::pair<ft::map<int, int>::iterator,bool>back2 = mp.insert(ft::pair<int, int>(10, 50));
		test.equal(back2.second, false, "Was not inserted");
		// Check iterator to be at beginning
		test.equal(mp.empty(), false, "Is still not empty");
		test.equal(mp.size(), (unsigned long)1, "Size is still 1");
	}
	{
		Test test("Insert single value with hint");
		ft::map<int, int> mp;
		test.equal(mp.empty(), true, "Is empty in beginning");
		ft::pair<ft::map<int, int>::iterator,bool>back2 = mp.insert(ft::pair<int, int>(40, 30));
		ft::map<int, int>::iterator back3 = mp.insert(back2.first, ft::pair<int, int>(10, 20));
		test.equal(*back3, ft::pair<const int, int>(10, 20), "Iterator points to new value");
		test.equal(mp.size(), (unsigned long)2, "Size is now 2");
		ft::map<int, int>::iterator back4 = mp.insert(back3, ft::pair<int, int>(10, 50));
		test.equal(*back4, ft::pair<const int, int>(10, 20), "Iterator points to old value");
		test.equal(back3, back4, "Iterators are the same");
		test.equal(mp.size(), (unsigned long)2, "Size is still 2");
	}
	{
		Test test("Insert multiple elements from range");
		ft::map<int, int> mp;
		mp.insert(test_data.begin(), test_data.end());
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (unsigned long)14, "14 elements now");
	}
	{
		Test test("Iterators");
		ft::map<int, int> mp(test_data.begin(), test_data.end());
		ft::map<int, int>::iterator begin = mp.begin();
		ft::map<int, int>::iterator end = mp.end();
		ft::map<int, int>::iterator it = begin;
		std::cout << "Begin Printing:" << std::endl;
		for(;it!=end;it++) {
			std::cout << "MAP: " << it->first << ":" << it->second << std::endl;
		}
		std::cout << "And backwards!" << std::endl;
		do {
			it--;
			std::cout << "MAP: " << it->first << ":" << it->second << std::endl;
		} while (it != begin);
	}
	/*
	{
		Test test("Reverse Iterators");
		ft::map<int, int> st;
		test.equal(mp.empty(), true, "Is empty in beginning");
		mp.insert('x');
		mp.insert('g');
		mp.insert('s');
		mp.insert('k');
		mp.insert('i');
		ft::map<int, int>::reverse_iterator begin = mp.rbegin();
		ft::map<int, int>::reverse_iterator end = mp.rend();
		ft::map<int, int>::reverse_iterator it = begin;
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
		ft::map<int, int> st;
		test.equal(mp.empty(), true, "Is empty in beginning");
		test.unequal(mp.max_size(), (unsigned long)0, "Max size is not zero");
		mp.insert('x');
		mp.insert('g');
		std::cout << "Max Size: " << mp.max_size() << std::endl;
	}
	{
		Test test("Delete one element from iterator");
		ft::map<int, int> st;
		std::string	str("Hello World");
		mp.insert(str.begin(), str.end());
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (unsigned long)8, "8 unique characters");
		ft::map<int, int>::iterator it = mp.begin();
		it++;
		it++;
		mp.erase(it);
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (unsigned long)7, "7 unique characters");
	}
	{
		Test test("Delete one element from value");
		ft::map<int, int> st;
		std::string	str("Hello World");
		mp.insert(str.begin(), str.end());
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (unsigned long)8, "8 unique characters");
		size_t erased_elements = mp.erase(' ');
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(erased_elements, (unsigned long)1, "Erased 1 element");
		test.equal(mp.size(), (unsigned long)7, "7 unique characters");
		erased_elements = mp.erase(' ');
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(erased_elements, (unsigned long)0, "Erased 0 element");
		test.equal(mp.size(), (unsigned long)7, "7 unique characters");
	}
	{
		Test test("Delete one element from range");
		ft::map<int, int> st;
		std::string	str("Hello World");
		mp.insert(str.begin(), str.end());
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (unsigned long)8, "8 unique characters");
		mp.erase(mp.begin(), mp.end());
		test.equal(mp.empty(), true, "Is empty now");
		test.equal(mp.size(), (unsigned long)0, "Is empty (0 elements)");
	}
	{
		Test test("Swapping one map with another");
		std::string	str1("Hello World");
		ft::map<int, int> mp1;
		mp1.insert(str1.begin(), str1.end());
		std::string str2("What's up?");
		ft::map<int, int> mp2;
		mp2.insert(str2.begin(), str2.end());

		ft::map<int, int>::iterator it1 = mp1.begin();
		ft::map<int, int>::iterator it2 = mp2.begin();
		ft::map<int, int>::iterator it1_1 = it1;
		ft::map<int, int>::iterator it2_1 = it2;

		ft::map<int, int> mp1_1 = mp1;
		ft::map<int, int> mp2_1 = mp2;

		mp2.swap(mp1);

		test.equal(it1, it1_1);
		test.equal(it2, it2_1);
		it1++;
		it2++;
		it1_1++;
		it2_1++;
		test.equal(it1, it1_1);
		test.equal(it2, it2_1);
		//test.equal(mp1, mp2_1);
		//test.equal(mp2, mp1_1);
	}
	{
		Test test("Clear the map");
		std::string	str("Hello World");
		ft::map<int, int> st;
		mp.insert(str.begin(), str.end());
		test.equal(mp.empty(), false, "Set is not empty");
		test.equal(mp.size(), (unsigned long)8, "Size is 8");
		mp.clear();
		test.equal(mp.empty(), true, "Set is empty");
		test.equal(mp.size(), (unsigned long)0, "Size is 0");
	}
	{
		Test test("value_comp and key_comp");
		ft::map<int, int> st;
		test.equal(typeid(mp.value_comp()).name(), typeid(std::less<char>).name(), "Value comp is std::less");
		test.equal(typeid(mp.key_comp()).name(), typeid(std::less<char>).name(), "Key comp is std::less");
	}
	{
		Test test("Find");
		ft::map<int, int> st;
		std::string	str("Hello World");
		mp.insert(str.begin(), str.end());
		ft::map<int, int>::iterator it1 = mp.find('W');
		test.equal(*it1, 'W', "Returns correct item");
		ft::map<int, int>::iterator it2 = mp.find('x');
		test.equal(it2, mp.end(), "If not found iterator to end");
	}
	{
		Test test("Count");
		ft::map<int, int> st;
		std::string	str("Hello World");
		mp.insert(str.begin(), str.end());
		test.equal(mp.count('W'), (unsigned long)1, "Found 'W' one time");
		test.equal(mp.count('x'), (unsigned long)0, "Found 'x' zero times");
	}
	{
		Test test("Lower Bound");
		ft::map<int, int> st;
		std::string	str("Hello World");
		mp.insert(str.begin(), str.end());
		ft::map<int, int>::iterator lb_it = mp.lower_bound('e');
		test.equal(*lb_it, 'e', "Is lower bound of 'e' equal 'e'");
		ft::map<int, int>::iterator ub_it = mp.upper_bound('o');
		test.equal(*ub_it, 'r', "Is upper bound of 'o' equal 'r'");
		ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> eq_rg = mp.equal_range('e');
		test.equal(*(eq_rg.first), 'e', "Is lower bound of range 'e'");;
		test.equal(*(eq_rg.second), 'l', "Is upper bound of range 'l'");;
	}
	*/
}
