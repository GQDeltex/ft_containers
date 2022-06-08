#include "Test.hpp"

int Test::_total_cases = 0;
int Test::_failed_cases = 0;

void TestVector();
void TestIterator();
void TestReverseIterator();
void TestIsIntegral();

int main(void) {
	TestIterator();
	TestReverseIterator();
	TestVector();
	TestIsIntegral();
	Test test;
	test.summary();
}
