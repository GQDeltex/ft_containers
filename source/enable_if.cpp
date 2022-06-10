#include "Test.hpp"

#ifndef USE_STD
# define USE_STD 1
#endif

#if USE_STD == 0
# include "../include/ft/enable_if.hpp"
# include "../include/ft/is_integral.hpp"
#else
# include <type_traits>
  namespace ft = std;
#endif

void negate(int in, int sum) {
	(void)in;
	(void)sum;
	std::cout << "Integer" << std::endl;
}

template <
	typename T
//> void negate(T in) {
//> T negate(typename ft::enable_if<!ft::is_integral<T>::value>::type in) {
> void negate(T in, typename ft::enable_if<!ft::is_integral<T>::value, T>::type sum) {
	(void)in;
	(void)sum;
	std::cout << "Others" << std::endl;
}

void TestEnableIf() {
	{
		negate(3.4, 3.4);
		negate(4, 4);
		negate("Hi", "Hello World");
	}
}
