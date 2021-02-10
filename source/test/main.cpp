#include <iostream>
#include "hashlib/i_hashlib.h"
int main()
{
	auto md5 = getHashLib();
	md5->update("hello world!2");
	std::cout << md5->hexdigest() << std::endl;
	md5->update("hello world!");
	std::cout << md5->hexdigest() << std::endl;

	return 0;
}