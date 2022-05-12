#include <iostream>
#include <assert.h>
#include "../include/ft/vector.hpp"

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
		> bool equal(T lhs, T rhs) {
			if (lhs == rhs)
				return true;
			this->_failed++;
			std::cout << lhs << " is not equal to " << rhs << std::endl;
			return false;
		}
		template<
			class T
		> bool notnull(T trgt) {
			if (!trgt.empty())
				return true;
			this->_failed++;
			std::cout << "OBJECT is NULL" << std::endl;
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

int main(void) {
	{
		Test test("Constructor Default");
		ft::vector<std::string> lst;
		test.equal(lst.empty(), true);
	}
	{
		Test test("Constructor Fill");
		ft::vector<std::string> lst(3, "Works though");
		test.notnull(lst[0]);
		test.notnull(lst[1]);
		test.notnull(lst[2]);
		test.equal(lst[0], std::string("Works though"));
		test.equal(lst[1], std::string("Works though"));
		test.equal(lst[2], std::string("Works though"));
	}
	{
		Test test("push_back() add to end");
		ft::vector<std::string> lst;
		lst.push_back("Hello World!");
		test.notnull(lst[0]);
		test.equal(lst[0], std::string("Hello World!"));
		lst.push_back("Hi there!");
		test.notnull(lst[1]);
		test.equal(lst[1], std::string("Hi there!"));
		lst.push_back("Ok cool");
		test.notnull(lst[2]);
		test.equal(lst[2], std::string("Ok cool"));
	}
	{
		Test test("Front() get first item");
		ft::vector<std::string> lst;
		lst.push_back("Hello World!");
		lst.push_back("Hi there!");
		test.equal(lst.front(), std::string("Hello World!"));
	}
	Test test;
	test.summary();
}
