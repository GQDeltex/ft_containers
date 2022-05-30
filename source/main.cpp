#include "../include/ft/vector.hpp"
#include <vector>
#include "Test.hpp"
#include "Dummy.hpp"

int main(void) {
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
		ft::vector<Dummy> lst;
		lst.push_back(Dummy());
		lst.push_back(Dummy());
		lst.push_back(Dummy());
	}
	Test test;
	test.summary();
}
