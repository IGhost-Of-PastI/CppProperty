// CppProperty.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "rproperty.h"

class Test
{

public:
    Test() :field2(1, [](int val) {return ++val; }) {};
    rproperty<int,0,Test> field = 1;
    rproperty<int, 0, Test> field2;//(1, [](int val) {return val++; });
    //rproperty<int> field2=rproperty(1, [](int val)->int {});
};

int main() {
    Test test;
    std::cout << test.field << std::endl;
    std::cout << test.field2 << std::endl;
    return 0;
}