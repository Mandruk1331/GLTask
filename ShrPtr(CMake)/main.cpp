#include <iostream>
#include "SharedPointer.hpp"

#define CNT_LOOPS 15

int main(void)
{

	MyStd::_shared_pointer_<int> p1(new int(10));
	MyStd::_shared_pointer_<int> p2(p1);
	MyStd::_shared_pointer_<int> p3(new int(15));
	
	{
		MyStd::_shared_pointer_<int> p4 = p2;
		std::cout<< "P4: " << p4.GetDataPtr() << " | " << p4.UseCount() << std::endl;
	}
	
	for (int i = 0; i < CNT_LOOPS; i++) 
	{
		p1.SwapPtr(p3);
	}
	
	std::cout << "P1: " << p1.GetDataPtr() << " | " << p1.UseCount() << std::endl;
	std::cout << "P2: " << p2.GetDataPtr() << " | " << p2.UseCount() << std::endl;
	std::cout << "P3: " << p3.GetDataPtr() << " | " << p3.UseCount() << std::endl;

	return 0;
}
