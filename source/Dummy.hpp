#ifndef DUMMY_H
# define DUMMY_H
# include <iostream>

class Dummy {
	protected:
		int	*numbers;
	public:
		Dummy(void) {
			std::cout << "------- DUMMY CONSTRUCTOR ----------" << std::endl;
			numbers = new int[4];
		}
		Dummy(const Dummy& dum) {
			std::cout << "------- DUMMY COPY CONSTRUCTOR ----------" << std::endl;
			numbers = new int[4];
			(*this) = dum;
		}
		Dummy& operator=(const Dummy& dum) {
			std::cout << "------- DUMMY ASSIGNMENT OPERATOR ----------" << std::endl;
			(void)&dum;
			return (*this);
		}
		~Dummy(void) {
			std::cout << "------- DUMMY DESTRUCTOR ----------" << std::endl;
			delete[] numbers;
		}
};

#endif
