// CppProperty.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "property.hpp"

class Test
{

public:
    Test() :field2(1, [](int val) {return ++val; }) {};
    rproperty<int,Test> field = 1;
    rproperty<int, Test> field2;
    //wproperty<int, Test> wfield;
    //rwproperty<int, Test> rwfield;//(1, [](int val) {return val++; });
    //rproperty<int> field2=rproperty(1, [](int val)->int {});
};

int main() {
    Test test;
    std::cout << test.field << std::endl;
    std::cout << test.field2 << std::endl;
    return 0;
}