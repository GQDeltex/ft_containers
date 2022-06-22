#include "../include/ft/vector_iterator.hpp"
#include "Test.hpp"
#include <exception>

void TestIterator() {
	{
		Test test("Constructor Default");
		ft::vector_iterator<char> it;
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
		ft::vector_iterator<char> it(&str[0]);
		test.equal(*it, 'H');
	}
	{
		Test test("Constructor Copy");
		std::string str = "Hello World";
		ft::vector_iterator<char> it(&str[0]);
		ft::vector_iterator<char> it2(it);
		test.equal(*it, 'H');
		test.equal(*it2, 'H');
	}
	{
		Test test("Assignment Operator");
		std::string str = "Hello World";
		ft::vector_iterator<char> it(&str[0]);
		ft::vector_iterator<char> it2 = it;
		test.equal(*it, 'H');
		test.equal(*it2, 'H');
	}
	{
		Test test("Comparison equal operator");
		std::string str1 = "Hello World";
		ft::vector_iterator<char> it1(&str1[0]);
		ft::vector_iterator<char> it2(&str1[0]);
		test.equal(it1, it2);
	}
	{
		Test test("Comparison unequal operator");
		std::string str1 = "Hello World";
		std::string str2 = "Nice Day";
		ft::vector_iterator<char> it1(&str1[0]);
		ft::vector_iterator<char> it2(&str2[0]);
		test.unequal(it1, it2);
	}
	{
		Test test("Comparison smaller/greater/equal operator");
		std::string str1 = "Hello World";
		ft::vector_iterator<char> it1(&str1[0]);
		ft::vector_iterator<char> it2 = it1;
		test.equal(it1 == it2, true);
		test.equal(it1 <= it2, true);
		test.equal(it1 >= it2, true);
		it2++;
		test.equal(it1 != it2, true);
		test.equal(it1 >= it2, false);
		test.equal(it1 <= it2, true);
		test.equal(it1 < it2, true);
		test.equal(it1 > it2, false);
		it2--;
		test.equal(it1, it2);
	}
	{
		Test test("Offset Dereference Operator");
		std::string str = "Hello World";
		ft::vector_iterator<char> it(&str[0]);
		test.equal(it[3], 'l');
		test.equal(it[0], 'H');
	}
	{
		Test test("Arithmetic Operators");
		std::string str = "Hello World";
		ft::vector_iterator<char> it(&str[0]);
		ft::vector_iterator<char> it1 = it + 3;
		ft::vector_iterator<char> it2 = 5 + it;
		test.equal(*it1, 'l');
		test.equal(*it2, ' ');
		test.equal(it2 - it1, 2);
	}
	{
		Test test("Compound Operators");
		std::string str = "Hello World";
		ft::vector_iterator<char> it(&str[0]);
		it += 3;
		test.equal(*it, 'l');
		it -= 3;
		test.equal(*it, 'H');
		it += 5;
		test.equal(*it, ' ');
	}
}
