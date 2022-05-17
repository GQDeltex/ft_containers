#ifndef TEST_H
# define TEST_H

# include <iostream>

class Test {
	private:
		static int _total_cases;
		static int _failed_cases;
		bool _sum;
		int	_failed;
	public:
		Test(void) {
			this->_sum = true;
		}
		Test(std::string topic) {
			this->_sum = false;
			this->_failed = 0;
			this->_total_cases++;
			std::cout << "Testing " << topic << std::endl;
		}
		template<
			class T
		> bool equal(T lhs, T rhs, std::string desc="is lhs equal to rhs") {
			if (lhs == rhs)
				return true;
			this->_failed++;
			std::cout << desc << " -> NO!" << std::endl;
			return false;
		}
		template<
			class T
		> bool notnull(T trgt, std::string desc="OBJECT is NULL") {
			if (!trgt.empty())
				return true;
			this->_failed++;
			std::cout << desc << " -> NO!" << std::endl;
			return false;
		}
		void summary(void) {
			std::cout << std::endl;
			std::cout << "Test Summary:" << std::endl;
			std::cout << this->_total_cases << " tests ran" << std::endl;
			std::cout << this->_failed_cases << " tests failed" << std::endl;
			if (this->_failed_cases > 0)
				std::cout << "== FAIL ==" << std::endl;
			else
				std::cout << "== PASS ==" << std::endl;

		}
		~Test(void) {
			if (this->_sum)
				return;
			if (this->_failed > 0) {
				this->_failed_cases++;
				std::cout << "== FAIL ==" << std::endl;
				return;
			}
			std::cout << "== PASS ==" << std::endl;
		}
};

int Test::_total_cases = 0;
int Test::_failed_cases = 0;

#endif
