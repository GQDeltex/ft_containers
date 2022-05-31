#include "Test.hpp"

int Test::_total_cases = 0;
int Test::_failed_cases = 0;

void TestVector();
void TestIterator();

int main(void) {
	TestIterator();
	TestVector();
	Test test;
	test.summary();
}
