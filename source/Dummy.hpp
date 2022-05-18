#ifndef DUMMY_H
# define DUMMY_H
# include <iostream>

class Dummy {
	protected:
		int	*numbers;
	public:
		Dummy(void) {
			std::cout << "\e[1;34m------- DUMMY CONSTRUCTOR ----------\e[0m" << std::endl;
			numbers = new int[4];
		}
		Dummy(const Dummy& dum) {
			std::cout << "\e[1;34m------- DUMMY COPY CONSTRUCTOR ----------\e[0m" << std::endl;
			numbers = new int[4];
			(*this) = dum;
		}
		Dummy& operator=(const Dummy& dum) {
			std::cout << "\e[1;34m------- DUMMY ASSIGNMENT OPERATOR ----------\e[0m" << std::endl;
			(void)&dum;
			return (*this);
		}
		~Dummy(void) {
			std::cout << "\e[1;34m------- DUMMY DESTRUCTOR ----------\e[0m" << std::endl;
			delete[] numbers;
		}
};

#endif
