﻿#include <iostream>
#include "big_integer.h"
#include <cstdlib>

int main()
{
    std::string str;
    std::cin >> str;
    auto a = big_integer(str);
    std::cin >> str;
    auto b = big_integer(str);
    std::cout << to_string(~a);
    int t = 5;
    std::cout << '\n' <<  ~t;
}
