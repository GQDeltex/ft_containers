#include <iostream>
#include "../include/ft/vector.hpp"

int main(void) {
	ft::vector<std::string> lst;
	lst.push_back("Hello World!");
	std::cout << "First element: " << lst.front() << std::endl;
	std::cout << "First element: " << lst[0] << std::endl;
	lst.push_back("Hi there!");
	std::cout << "First element: " << lst[0] << std::endl;
	std::cout << "Second element: " << lst[1] << std::endl;
	ft::vector<std::string> lst2(3, "Works though");
	std::cout << "First element: " << lst2[0] << std::endl;
	std::cout << "Second element: " << lst2[1] << std::endl;
	std::cout << "Third element: " << lst2[2] << std::endl;
}
