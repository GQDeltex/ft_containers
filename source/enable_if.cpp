#include "Test.hpp"

#ifndef USE_STD
# define USE_STD 0
#endif

#if USE_STD == 0
# include "../include/ft/enable_if.hpp"
# include "../include/ft/is_integral.hpp"
#else
# include <type_traits>
  namespace ft = std;
#endif

std::string negate(int in, int sum) {
	(void)in;
	(void)sum;
	return "Integer";
}

template <
	typename T
//> void negate(T in) {
//> T negate(typename ft::enable_if<!ft::is_integral<T>::value>::type in) {
> std::string negate(T in, typename ft::enable_if<!ft::is_integral<T>::value, T>::type sum) {
	(void)in;
	(void)sum;
	return ("Others");
}

void TestEnableIf() {
	{
		Test test("Enable if working correctly");
		test.equal(negate(3.4, 3.4), std::string("Others"));
		test.equal(negate(4, 4), std::string("Integer"));
		test.equal(negate("Hi", "Hello World"), std::string("Others"));
	}
}
