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
}
