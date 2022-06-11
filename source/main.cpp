#include "Test.hpp"

int Test::_total_cases = 0;
int Test::_failed_cases = 0;

void TestVector();
void TestIterator();
void TestReverseIterator();
void TestIsIntegral();
void TestEnableIf();
void TestStack();

int main(void) {
	TestIterator();
	TestReverseIterator();
	TestVector();
	TestIsIntegral();
	TestEnableIf();
	TestStack();
	Test test;
	test.summary();
}
