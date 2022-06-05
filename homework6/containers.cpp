#include <iostream>
#include "list.hpp"
#include "vector.hpp"

template<class Container>
void test(Container a)
{
	for (auto i = 0; i < 10; ++i)
		a.pushBack(i);

	std::cout << "Container: " << std::endl;
	std::cout << a << std::endl;
	std::cout << "Container size: " << std::endl;
	std::cout << a.size() << std::endl;

	std::cout << "Erase elements 2, 4, 6 from container: ( HELP :( )" << std::endl;
	auto toRemove = BidirectionalList<size_t>();
	toRemove.pushBack(6);
	toRemove.pushBack(4);
	toRemove.pushBack(6);
	//a.erase(toRemove);
	std::cout << a << std::endl;
	
	std::cout << "Insert 10 at the beginning" << std::endl;
	a.insert(0, 10);
	std::cout << a << std::endl;

	std::cout << "Insert 20 in the middle" << std::endl;
	a.insert(a.size() / 2, 20);
	std::cout << a << std::endl;

	std::cout << "Insert 30 at the end" << std::endl;
	a.insert(a.size(), 30);
	std::cout << a << std::endl;
}

int main() {
	std::cout << "-----------TEST OF LIST<INT>-----------" << std::endl;
	BidirectionalList<int> list;
	test(list);
	std::cout << "-----------TEST OF VECTOR<INT>-----------" << std::endl;
	Vector<int> vector;
	test(vector);
	return 0;
}