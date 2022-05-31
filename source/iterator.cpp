#include "../include/ft/iterator.hpp"
#include "Test.hpp"
#include <exception>

void TestIterator() {
	{
		Test test("Constructor Default");
		ft::iterator<char> it;
		try {
			*it;
		} catch(const std::runtime_error& e) {
			std::string msg = e.what();
			std::cout << "Caught exception: " << msg << std::endl;
			test.equal(msg, std::string("Cannot dereference NULL Pointer"));
		}
	}
	{
		Test test("Constructor Value");
		std::string str = "Hello World";
		ft::iterator<char> it(&str[0]);
		test.equal(*it, 'H');
	}
	{
		Test test("Constructor Copy");
		std::string str = "Hello World";
		ft::iterator<char> it(&str[0]);
		ft::iterator<char> it2(it);
		test.equal(*it, 'H');
		test.equal(*it2, 'H');
	}
	{
		Test test("Assignment Operator");
		std::string str = "Hello World";
		ft::iterator<char> it(&str[0]);
		ft::iterator<char> it2 = it;
		test.equal(*it, 'H');
		test.equal(*it2, 'H');
	}
}
