#include "Test.hpp"

#ifndef USE_STD
# define USE_STD 0
#endif

#if USE_STD == 1
# include <stack>
  namespace ft = std;
#else
# include "../include/ft/stack.hpp"
#endif

void TestStack() {
	{
		Test test("Default Constructor");
		ft::stack<std::string> stk;
	}
	{
		Test test("Stack empty");
		ft::stack<std::string> stk;
		test.equal(stk.empty(), true);
		stk.push("Hello World!");
		test.equal(stk.empty(), false);
	}
	{
		Test test("Stack size");
		ft::stack<std::string> stk;
		test.equal(stk.size(), (size_t)0);
		stk.push("Hello World");
		test.equal(stk.size(), (size_t)1);
	}
	{
		Test test("Stack top");
		ft::stack<std::string> stk;
		stk.push("Hello World");
		test.equal(stk.top(), std::string("Hello World"), "First element top");
		stk.push("Hi there");
		test.equal(stk.top(), std::string("Hi there"), "Second element top");
	}
	{
		Test test("Stack pop");
		ft::stack<std::string> stk;
		stk.push("Hello World");
		test.equal(stk.top(), std::string("Hello World"), "First element top");
		stk.push("Hi there");
		test.equal(stk.top(), std::string("Hi there"), "Second element top");
		stk.pop();
		test.equal(stk.top(), std::string("Hello World"), "First back on top");
	}
	{
		Test test("Comparison operators");
		std::string str1("Hello World!");
		std::string str2("This is nice");
		std::string str3("Hello World?");
		ft::vector<char> lst1(str1.begin(), str1.end());
		ft::vector<char> lst2(str2.begin(), str2.end());
		ft::vector<char> lst3(str3.begin(), str3.end());
		ft::stack<char> stk1(lst1);
		ft::stack<char> stk2(lst2);
		ft::stack<char> stk3(lst3);
		test.equal(stk1 < stk2, true);
		test.equal(stk1 >= stk2, false);
		test.equal(stk1 <= stk1, true);
		test.equal(stk3 > stk1, true);
	}
}
