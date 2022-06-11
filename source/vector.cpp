#include "Test.hpp"
#include "Dummy.hpp"
#include <vector>

#ifndef USE_STD
# define USE_STD 0
#endif

#if USE_STD == 1
  namespace ft = std;
#else
# include "../include/ft/vector.hpp"
#endif

void TestVector() {
	{
		Test test("Constructor Default: Construct an empty list");
		ft::vector<std::string> lst;
		std::vector<std::string> vec;
		test.equal(lst.empty(), vec.empty());
	}
	{
		Test test("Constructor Fill: Fill the list with an item");
		ft::vector<std::string> lst(3, "Works though");
		test.notnull(lst[0], "is lst[0] not NULL");
		test.notnull(lst[1], "is lst[1] not NULL");
		test.notnull(lst[2], "is lst[2] not NULL");;
		test.equal(lst[0], std::string("Works though"), "is lst[0] right content");
		test.equal(lst[1], std::string("Works though"), "is lst[1] right content");
		test.equal(lst[2], std::string("Works though"), "is lst[1] right content");
	}
	{
		Test test("Constructor Range: Construct vector from an iterator");
		std::string test_str("Hello World");
		ft::vector<char> lst(test_str.begin(), test_str.end());
		test.equal(lst.empty(), false);
		test.equal(lst.size(), (size_t)11);
		test.equal(lst[0], 'H');
		test.equal(lst[1], 'e');
	}
	{
		Test test("Iterators: begin() get the beginning of the iterator");
		std::string test_str("Hello World");
		ft::vector<char> lst(test_str.begin(), test_str.end());
		test.equal(lst.empty(), false);
		ft::vector<char>::iterator start = lst.begin();
		test.equal(*start, 'H');
		start++;
		test.equal(*start, 'e');
	}
	{
		Test test("Iterators: end() get the end of the iterator");
		std::string test_str("Hello World");
		ft::vector<char> lst(test_str.begin(), test_str.end());
		test.equal(lst.empty(), false);
		ft::vector<char>::iterator it = lst.begin();
		std::string::iterator ref = test_str.begin();
		while (it != lst.end() && ref != test_str.end()) {
			test.equal(*it, *ref);
			ref++;
			it++;
		}
		test.equal(it == lst.end(), true);
		test.equal(ref == test_str.end(), true);
	}
	{
		Test test("push_back(): add element to end");
		ft::vector<std::string> lst;
		lst.push_back("Hello World!");
		test.notnull(lst[0], "is lst[0] not NULL");
		test.equal(lst[0], std::string("Hello World!"), "is lst[0] right content");
		lst.push_back("Hi there!");
		test.notnull(lst[1], "is lst[1] not NULL");
		test.equal(lst[1], std::string("Hi there!"), "is lst[1] right content");
		lst.push_back("Ok cool");
		test.notnull(lst[2], "is lst[2] not NULL");
		test.equal(lst[2], std::string("Ok cool"), "is lst[2] right content");
	}
	{
		Test test("empty(): check if list is empty");
		ft::vector<std::string> lst;
		test.equal(lst.empty(), true, "is lst empty");
		lst.push_back("Hi there");
		test.equal(lst.empty(), false, "is lst non-empty");
	}
	{
		Test test("size(): check list size");
		ft::vector<std::string> lst;
		test.equal(lst.size(), (size_t)0, "is lst size 0");
		lst.push_back("Hi there");
		test.equal(lst.size(), (size_t)1, "is lst size 1");
		lst.push_back("Hi there");
		test.equal(lst.size(), (size_t)2, "is lst size 2");
	}
	{
		Test test("front(): get first item");
		ft::vector<std::string> lst;
		lst.push_back("Hello World!");
		lst.push_back("Hi there!");
		test.equal(lst.front(), std::string("Hello World!"), "is first element correct");
	}
	{
		Test test("get_allocator(): get the allocator");
		ft::vector<std::string> lst;
		test.equal(lst.get_allocator(), std::allocator<std::string>(), "is allocator std::allocator");
	}
	{
		Test test("Assignment Operator: assing a vector to another");
		ft::vector<std::string> lst1(1, "Hello World");
		test.equal(lst1.size(), (size_t)1, "Has first list 1 item");
		test.equal(lst1[0], (std::string)"Hello World", "Is first item correct");

		ft::vector<std::string> lst2;
		test.equal(lst2.empty(), true, "Is second list empty");

		lst2 = lst1;
		test.equal(lst1.empty(), false, "Is first list empty");
		test.equal(lst1.size(), (size_t)1, "Has first list 1 item");
		test.equal(lst1[0], (std::string)"Hello World", "Is first element correct");
		test.equal(lst2.empty(), false, "Is second list empty");
		test.equal(lst2.size(), (size_t)1, "Has second list 1 item");
		test.equal(lst2[0], (std::string)"Hello World", "Is first element correct");

		lst2.push_back("Oh hi there");
		test.equal(lst1.size(), (size_t)1, "Has first list still 1 item");
		test.equal(lst2.size(), (size_t)2, "Has second list now 2 items");
		test.equal(lst2[1], (std::string)"Oh hi there", "Is second element correct");
	}
	{
		Test test("Copy Constructor: Copy a vector while constructing another one");
		ft::vector<std::string> lst1(1, "Hello World");
		test.equal(lst1.size(), (size_t)1, "Has first list 1 item");
		test.equal(lst1[0], (std::string)"Hello World");

		ft::vector<std::string> lst2(lst1);
		test.equal(lst1.empty(), false, "Is first list empty");
		test.equal(lst1.size(), (size_t)1, "Has first list 1 item");
		test.equal(lst1[0], (std::string)"Hello World", "Is first item correct");
		test.equal(lst2.empty(), false, "Is second list empty");
		test.equal(lst2.size(), (size_t)1, "Has second list 1 item");
		test.equal(lst2[0], (std::string)"Hello World", "Is first item correct");

		lst2.push_back("Oh hi there");
		test.equal(lst1.size(), (size_t)1, "Has first list still 1 item");
		test.equal(lst2.size(), (size_t)2, "Has second list now 2 items");
		test.equal(lst2[1], (std::string)"Oh hi there", "Is second element correct");
	}
	{
		Test test("Leak test with dummy class");
		ft::vector<Dummy> lst1;
		lst1.push_back(Dummy());
		lst1.push_back(Dummy());
		lst1.push_back(Dummy());
		ft::vector<Dummy> lst2;
		lst2.push_back(Dummy());
		lst2 = lst1;
		lst2.push_back(Dummy());
	}
	{
		Test test("Check Allocated Space with capacity");
		ft::vector<std::string> lst;
		test.equal(lst.capacity(), (size_t)0);
		lst.reserve(10);
		test.equal(lst.capacity(), (size_t)10);
	}
	{
		Test test("Resize the vector and truncate/extend");
		std::string str("Hello World!");
		ft::vector<char> lst(str.begin(), str.end());
		test.equal(lst.size(), (size_t)12);
		lst.resize(5);
		test.equal(lst.size(), (size_t)5);
		lst.resize(8, 'X');
		test.equal(lst.size(), (size_t)8, "Is size the size we requested");
		test.equal(lst[6], 'X', "Is extended element equal to 'X'");
	}
	{
		Test test("Clear Vector");
		std::string str("Hello World!");
		ft::vector<char> lst(str.begin(), str.end());
		test.equal(lst.size(), (size_t)12);
		lst.clear();
		test.equal(lst.size(), (size_t)0);
	}
	{
		Test test("Assing from Iterator (replace content)");
		std::string str1("Hello World!");
		ft::vector<char> lst(str1.begin(), str1.end());
		test.equal(lst.size(), (size_t)12);
		test.equal(lst[0], 'H');
		test.equal(lst[8], 'r');
		test.equal(lst[9], 'l');
		std::string str2("Nice Day!");
		lst.assign(str2.begin(), str2.end());
		test.equal(lst.size(), (size_t)9);
		test.equal(lst[0], 'N');
		test.equal(lst[8], '!');
	}
	{
		Test test("Assing from value/type (place content)");
		std::string str1("Hello World!");
		ft::vector<char> lst(str1.begin(), str1.end());
		test.equal(lst.size(), (size_t)12);
		test.equal(lst[0], 'H');
		test.equal(lst[8], 'r');
		test.equal(lst[9], 'l');
		lst.assign(4, 'X');
		test.equal(lst.size(), (size_t)4);
		test.equal(lst[0], 'X');
		test.equal(lst[3], 'X');
	}
	{
		Test test("Assing from value/type (place content)");
		std::string str1("Hello World!");
		ft::vector<char> lst(str1.begin(), str1.end());
		test.equal(lst.size(), (size_t)12);
		test.equal(lst[10], 'd');
		test.equal(lst[11], '!');
		lst.pop_back();
		test.equal(lst.size(), (size_t)11);
		test.equal(lst[10], 'd');
	}
	{
		Test test("Inserting single element");
		std::string str1("Hello World!");
		ft::vector<char> lst(str1.begin(), str1.end());
		test.equal(lst.size(), (size_t)12);
		test.equal(lst[11], '!');
		lst.insert(lst.end(), 'X');
		test.equal(lst.size(), (size_t)13);
		test.equal(lst[11], '!');
		test.equal(lst[12], 'X');
		test.equal(lst[0], 'H');
		lst.insert(lst.begin(), 'X');
		test.equal(lst.size(), (size_t)14, "Is length correct");
		test.equal(lst[12], '!', "Is end still '!'");
		test.equal(lst[13], 'X', "Is added 'X' at end");
		test.equal(lst[0], 'X', "Is 'X' at front");
		test.equal(lst[1], 'H', "Is beginning still 'H'");
	}
	{
		Test test("Inserting multiple elements");
		std::string str1("Hello World!");
		ft::vector<char> lst(str1.begin(), str1.end());
		test.equal(lst.size(), (size_t)12);
		test.equal(lst[11], '!');
		lst.insert(lst.end(), 3, 'X');
		test.equal(lst.size(), (size_t)15, "Is size now 15");
		test.equal(lst[11], '!', "Is end still '!'");
		test.equal(lst[12], 'X', "Is last 3 'X'");
		test.equal(lst[14], 'X', "Is last element 'X'");
		test.equal(lst[0], 'H', "Is 'H' in beginning");
		lst.insert(lst.begin(), 3, 'X');
		test.equal(lst.size(), (size_t)18, "Is length correct");
		test.equal(lst[14], '!', "Is end still '!'");
		test.equal(lst[17], 'X', "Is added 'X' at end");
		test.equal(lst[0], 'X', "Is 'X' at front");
		test.equal(lst[2], 'X', "Is 'X' at front");
		test.equal(lst[3], 'H', "Is beginning still 'H'");
	}
	{
		Test test("Inserting from iterator");
		std::string str1("Hello World!");
		ft::vector<char> lst(str1.begin(), str1.end());
		test.equal(lst.size(), (size_t)12);
		test.equal(lst[11], '!');
		std::string str2("BURN!");
		lst.insert(lst.end(), str2.begin(), str2.end());
		test.equal(lst.size(), (size_t)17, "Is size correctly updated");
		test.equal(lst[11], '!', "Is end still '!'");
		test.equal(lst[12], 'B', "Is concatenated string there");
		test.equal(lst[16], '!', "Is end of second string there");
		test.equal(lst[0], 'H', "Is 'H' in beginning");
		std::string str3("NOW");
		lst.insert(lst.begin(), str3.begin(), str3.end());
		test.equal(lst.size(), (size_t)20, "Is length correct");
		test.equal(lst[14], '!', "Is end still '!'");
		test.equal(lst[19], '!', "Is added '!' at end");
		test.equal(lst[0], 'N');
		test.equal(lst[2], 'W');
		test.equal(lst[3], 'H', "Is beginning still 'H'");
	}
	{
		Test test("Erase single element");
		std::string str1("Hello World!");
		ft::vector<char> lst(str1.begin(), str1.end());
		test.equal(lst.size(), (size_t)12, "Is length 12");
		test.equal(lst[0], 'H', "Is first element 'H'");
		lst.erase(lst.begin());
		test.equal(lst[0], 'e', "Is second element now the first");
		test.equal(lst.size(), (size_t)11, "Is vector size smaller now");
		lst.erase(lst.begin() + 3);
		test.equal(lst[3], ' ', "Is fourth element now the third");
		test.equal(lst.size(), (size_t)10, "Is vector size smaller now");
	}
	{
		Test test("Erase range of elements");
		std::string str1("Hello World!");
		ft::vector<char> lst(str1.begin(), str1.end());
		test.equal(lst.size(), (size_t)12, "Is length 12");
		test.equal(lst[0], 'H', "Is first element 'H'");
		lst.erase(lst.begin(), lst.begin() + 2);
		test.equal(lst[0], 'l', "Is third element now the first");
		test.equal(lst.size(), (size_t)10, "Is vector size smaller now");
		lst.erase(lst.end() - 2, lst.end());
		test.equal(lst[7], 'l', "Is third last element now the last");
		test.equal(lst.size(), (size_t)8, "Is vector size smaller now");
	}
	{
		Test test("Swap two vectors");
		std::string str1("Hello World!");
		std::string str2("This is nice");
		ft::vector<char> lst1(str1.begin(), str1.end());
		ft::vector<char> lst2(str2.begin(), str2.end());
		ft::vector<char>::iterator it = lst1.begin() + 2;
		lst1.swap(lst2);
		test.equal(it, lst2.begin() + 2);
		swap(lst1, lst2);
		test.equal(it, lst1.begin() + 2);
	}
	{
		Test test("Equal/Unequal operator");
		std::string str1("Hello World!");
		std::string str2("This is nice");
		std::string str3("Hello World?");
		ft::vector<char> lst1(str1.begin(), str1.end());
		ft::vector<char> lst2(str2.begin(), str2.end());
		ft::vector<char> lst3(str3.begin(), str3.end());
		test.equal(lst1 == lst2, false);
		test.equal(lst1 != lst2, true);
		test.equal(lst3 == lst1, false);
	}
	{
		Test test("Comparison operators");
		std::string str1("Hello World!");
		std::string str2("This is nice");
		std::string str3("Hello World?");
		ft::vector<char> lst1(str1.begin(), str1.end());
		ft::vector<char> lst2(str2.begin(), str2.end());
		ft::vector<char> lst3(str3.begin(), str3.end());
		test.equal(lst1 < lst2, true);
		test.equal(lst1 >= lst2, false);
		test.equal(lst1 <= lst1, true);
		test.equal(lst3 > lst1, true);
	}
	{
		Test test("Iterators: rbegin() get the beginning of the reverse_iterator");
		std::string test_str("Hello World");
		ft::vector<char> lst(test_str.begin(), test_str.end());
		test.equal(lst.empty(), false);
		ft::vector<char>::reverse_iterator start = lst.rbegin();
		test.equal(*start, 'd');
		start++;
		test.equal(*start, 'l');
	}
	{
		Test test("Iterators: end() get the end of the reverse_iterator");
		std::string test_str("Hello World");
		ft::vector<char> lst(test_str.begin(), test_str.end());
		test.equal(lst.empty(), false);
		ft::vector<char>::reverse_iterator it = lst.rbegin();
		std::string::reverse_iterator ref = test_str.rbegin();
		while (it != lst.rend() && ref != test_str.rend()) {
			if (!test.equal(*it, *ref))
				break;
			ref++;
			it++;
		}
		test.equal(it == lst.rend(), true);
		test.equal(ref == test_str.rend(), true);
	}
}
