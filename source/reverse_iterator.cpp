#include "Test.hpp"
#include <exception>

#ifndef USE_STD
# define USE_STD 0
#endif

#if USE_STD == 1
# include <iterator>
  namespace ft = std;
#else
# include "../include/ft/reverse_iterator.hpp"
#endif


void TestReverseIterator() {
	{
		Test test("Constructor Default");
		ft::reverse_iterator<std::string::iterator> it;
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
		ft::reverse_iterator<std::string::iterator> it(str.end());
		test.equal(*it, 'd', "End is correct");
	}
	{
		Test test("Constructor Copy");
		std::string str = "Hello World";
		ft::reverse_iterator<std::string::iterator> it(str.end());
		ft::reverse_iterator<std::string::iterator> it2(it);
		test.equal(*it, 'd');
		test.equal(*it2, 'd');
	}
	{
		Test test("Assignment Operator");
		std::string str = "Hello World";
		ft::reverse_iterator<std::string::iterator> it(str.end());
		ft::reverse_iterator<std::string::iterator> it2 = it;
		test.equal(*it, 'd');
		test.equal(*it2, 'd');
	}
	{
		Test test("Comparison equal operator");
		std::string str1 = "Hello World";
		ft::reverse_iterator<std::string::iterator> it1(str1.begin());
		ft::reverse_iterator<std::string::iterator> it2(str1.begin());
		test.equal(it1, it2);
	}
	{
		Test test("Comparison unequal operator");
		std::string str1 = "Hello World";
		std::string str2 = "Nice Day";
		ft::reverse_iterator<std::string::iterator> it1(str1.begin());
		ft::reverse_iterator<std::string::iterator> it2(str2.begin());
		test.unequal(it1, it2);
	}
	{
		Test test("Comparison smaller/greater/equal operator");
		std::string str1 = "Hello World";
		ft::reverse_iterator<std::string::iterator> it1(str1.end());
		ft::reverse_iterator<std::string::iterator> it2 = it1;
		test.equal(it1 == it2, true, "They are equal");
		test.equal(it1 <= it2, true, "1 is smaller or equal to 2");
		test.equal(it1 >= it2, true, "1 is greater or equal to 2");
		it2++;
		test.equal(it1 != it2, true, "They are not equal");
		test.equal(it1 <= it2, true, "1 is smaller or equal to 2");
		test.equal(it1 >= it2, false, "1 is not greater or equal to 2");
		test.equal(it1 > it2, false, "1 is not greater than 2");
		test.equal(it1 < it2, true, "1 is smaller than 2");
		it2--;
		test.equal(it1, it2, "They are equal");
	}
	{
		Test test("Offset Dereference Operator");
		std::string str = "Hello World";
		ft::reverse_iterator<std::string::iterator> it(str.end());
		test.equal(it[3], 'o');
		test.equal(it[0], 'd');
	}
	{
		Test test("Arithmetic Operators");
		std::string str = "Hello World";
		ft::reverse_iterator<std::string::iterator> it(str.end());
		ft::reverse_iterator<std::string::iterator> it1 = it + 3;
		ft::reverse_iterator<std::string::iterator> it2 = 5 + it;
		test.equal(*it1, 'o', "End plus 3 is 'o'");
		test.equal(*it2, ' ', "End plus 5 is ' '");
		test.equal(it2 - it1, (long)2);
	}
	{
		Test test("Compound Operators");
		std::string str = "Hello World";
		ft::reverse_iterator<std::string::iterator> it(str.end());
		it += 3;
		test.equal(*it, 'o');
		it -= 3;
		test.equal(*it, 'd');
		it += 5;
		test.equal(*it, ' ');
	}
}
