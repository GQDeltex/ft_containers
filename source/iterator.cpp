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
}
