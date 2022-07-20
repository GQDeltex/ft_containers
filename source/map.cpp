#include "Test.hpp"
#include <vector>
#include <typeinfo>

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
		test.equal(mp.size(), (size_t)0, "Size is zero");
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
		test.equal(mp.size(), (size_t)1, "Is 1 long now");
		ft::pair<ft::map<int, int>::iterator,bool>back2 = mp.insert(ft::pair<int, int>(10, 50));
		test.equal(back2.second, false, "Was not inserted");
		// Check iterator to be at beginning
		test.equal(mp.empty(), false, "Is still not empty");
		test.equal(mp.size(), (size_t)1, "Size is still 1");
	}
	{
		Test test("Insert single value with hint");
		ft::map<int, int> mp;
		test.equal(mp.empty(), true, "Is empty in beginning");
		ft::pair<ft::map<int, int>::iterator,bool>back2 = mp.insert(ft::pair<int, int>(40, 30));
		ft::map<int, int>::iterator back3 = mp.insert(back2.first, ft::pair<int, int>(10, 20));
		test.equal(*back3, ft::pair<const int, int>(10, 20), "Iterator points to new value");
		test.equal(mp.size(), (size_t)2, "Size is now 2");
		ft::map<int, int>::iterator back4 = mp.insert(back3, ft::pair<int, int>(10, 50));
		test.equal(*back4, ft::pair<const int, int>(10, 20), "Iterator points to old value");
		test.equal(back3, back4, "Iterators are the same");
		test.equal(mp.size(), (size_t)2, "Size is still 2");
	}
	{
		Test test("Insert multiple elements from range");
		ft::map<int, int> mp;
		mp.insert(test_data.begin(), test_data.end());
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (size_t)14, "14 elements now");
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
	{
		Test test("Reverse Iterators");
		ft::map<int, int> mp(test_data.begin(), test_data.end());
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
		ft::map<int, int> mp;
		test.equal(mp.empty(), true, "Is empty in beginning");
		test.unequal(mp.max_size(), (size_t)0, "Max size is not zero");
		std::cout << "Max Size: " << mp.max_size() << std::endl;
	}
	{
		Test test("Delete one element from iterator");
		ft::map<int, int> mp(test_data.begin(), test_data.end());
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (size_t)14, "14 values");
		ft::map<int, int>::iterator it = mp.begin();
		it++;
		it++;
		mp.erase(it);
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (size_t)13, "13 values");
	}
	{
		Test test("Delete one element from value");
		ft::map<int, int> mp(test_data.begin(), test_data.end());
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (size_t)14, "14 values");
		size_t erased_elements = mp.erase(50);
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(erased_elements, (size_t)1, "Erased 1 element");
		test.equal(mp.size(), (size_t)13, "13 values");
		erased_elements = mp.erase(50);
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(erased_elements, (size_t)0, "Erased 0 element");
		test.equal(mp.size(), (size_t)13, "13 values");
	}
	{
		Test test("Delete one element from range");
		ft::map<int, int> mp(test_data.begin(), test_data.end());
		test.equal(mp.empty(), false, "Is not empty now");
		test.equal(mp.size(), (size_t)14, "14 values");
		mp.erase(mp.begin(), mp.end());
		test.equal(mp.empty(), true, "Is empty now");
		test.equal(mp.size(), (size_t)0, "Is empty (0 elements)");
	}
	{
		Test test("Swapping one map with another");
		ft::map<int, int> mp1(test_data.begin(), test_data.end());
		ft::map<int, int> mp2;
		mp2.insert(ft::pair<int, int>(3, 7));

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
		ft::map<int, int> mp(test_data.begin(), test_data.end());
		test.equal(mp.empty(), false, "Set is not empty");
		test.equal(mp.size(), (size_t)14, "Size is 14");
		mp.clear();
		test.equal(mp.empty(), true, "Set is empty");
		test.equal(mp.size(), (size_t)0, "Size is 0");
	}
	{
		Test test("value_comp and key_comp");
		ft::map<int, int> mp;
		(void)mp.value_comp();
		(void)mp.key_comp();
	}
	{
		Test test("Find");
		ft::map<int, int> mp(test_data.begin(), test_data.end());
		ft::map<int, int>::iterator it1 = mp.find(50);
		test.equal(it1->second, 1, "Returns correct item");
		ft::map<int, int>::iterator it2 = mp.find(10);
		test.equal(it2, mp.end(), "If not found iterator to end");
	}
	{
		Test test("Count");
		ft::map<int, int> mp(test_data.begin(), test_data.end());
		test.equal(mp.count(50), (size_t)1, "Found 'W' one time");
		test.equal(mp.count(10), (size_t)0, "Found 'x' zero times");
	}
	{
		Test test("Lower Bound");
		ft::map<int, int> mp(test_data.begin(), test_data.end());
		ft::map<int, int>::iterator lb_it = mp.lower_bound(50);
		test.equal(lb_it->first, 50, "Is lower bound of 50 is 50");
		ft::map<int, int>::iterator ub_it = mp.upper_bound(50);
		test.equal(ub_it->first, 53, "Is upper bound of 50 is 53");
		ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> eq_rg = mp.equal_range(50);
		test.equal((eq_rg.first)->first, 50, "Is lower bound of range 'e'");;
		test.equal((eq_rg.second)->first, 53, "Is upper bound of range 'l'");;
	}
}
