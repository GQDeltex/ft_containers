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

int negate(int in) {
	std::cout << "Integer" << std::endl;
	return -in;
}

template <
	typename T
> T negate(typename ft::enable_if<!ft::is_integral<T>::value>::type in) {
	std::cout << "Others" << std::endl;
	return -in;
}

void TestEnableIf() {
	{
		std::cout << negate(3.4) << std::endl;
		std::cout << negate(4) << std::endl;
	}
}
