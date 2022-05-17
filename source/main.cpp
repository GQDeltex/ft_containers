#include "../include/ft/vector.hpp"
#include <vector>
#include "Test.hpp"

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
		test.notnull(lst[0], "is lst[0] NULL");
		test.notnull(lst[1], "is lst[1] NULL");
		test.notnull(lst[2], "is lst[2] NULL");;
		test.equal(lst[0], std::string("Works though"), "is lst[0] right content");
		test.equal(lst[1], std::string("Works though"), "is lst[1] right content");
		test.equal(lst[2], std::string("Works though"), "is lst[1] right content");
	}
	{
		Test test("push_back(): add element to end");
		ft::vector<std::string> lst;
		lst.push_back("Hello World!");
		test.notnull(lst[0]);
		test.equal(lst[0], std::string("Hello World!"));
		lst.push_back("Hi there!");
		test.notnull(lst[1]);
		test.equal(lst[1], std::string("Hi there!"));
		lst.push_back("Ok cool");
		test.notnull(lst[2]);
		test.equal(lst[2], std::string("Ok cool"));
	}
	{
		Test test("empty(): check if list is empty");
		ft::vector<std::string> lst;
		test.equal(lst.empty(), true);
		lst.push_back("Hi there");
		test.equal(lst.empty(), false);
	}
	{
		Test test("size(): check list size");
		ft::vector<std::string> lst;
		test.equal(lst.size(), (size_t)0);
		lst.push_back("Hi there");
		test.equal(lst.size(), (size_t)1);
		lst.push_back("Hi there");
		test.equal(lst.size(), (size_t)2);
	}
	{
		Test test("front(): get first item");
		ft::vector<std::string> lst;
		lst.push_back("Hello World!");
		lst.push_back("Hi there!");
		test.equal(lst.front(), std::string("Hello World!"));
	}
	{
		Test test("get_allocator(): get the allocator");
		ft::vector<std::string> lst;
		test.equal(lst.get_allocator(), std::allocator<std::string>());
	}
	Test test;
	test.summary();
}
