#include <iostream>
#include "big_integer.h"

int main()
{
    std::string str;
    std::cin >> str;
    auto a = big_integer(str);
    std::cin >> str;
    auto b = big_integer(str);
    a += b;
    std::cout << to_string(a);
}
