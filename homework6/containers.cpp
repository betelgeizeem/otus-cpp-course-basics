#include <iostream>
#include "list.hpp"
//#include "vector.hpp"

int main() {

	auto a = List<int>();
	for (auto i = 0; i < 10; ++i)
		a.pushBack(i);

	std::cout << a << std::endl;
	std::cout << a.size() << std::endl;
	a.erase(2);
	std::cout << a << std::endl;
	a.erase(4);
	std::cout << a << std::endl;
	a.erase(6);
	std::cout << a << std::endl;
	
	//auto b = Vector<double>();

	return 0;
}