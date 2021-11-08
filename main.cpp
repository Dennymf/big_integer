#include <iostream>
#include "big_integer.h"
#include <cstdlib>

int main()
{
    std::string str;
    std::cin >> str;
    auto a = big_integer(str);
    std::cin >> str;
    auto b = big_integer(str);
    //std::cout << to_string(a * b);
    std::cout << to_string(a % b);
	//int a, b;
	//std::cin >> a >> b;
	//std::cout << a % b;
}
