/**
 * @file circ_array_test.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include <iostream>
#include "circ_array.h"

using namespace cs225;

int main()
{
    circ_array<int> arr{6};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i + 1;

//    for (int i = 0; i < arr.size(); ++i)
//    {
//        std::cout << arr[i] << ";";
//    }
//    std::cout << std::endl;

    arr.push_front(0);

//    for (int i = 0; i < arr.size(); ++i)
//    {
//        std::cout << arr[i] << ";";
//    }
//    std::cout << std::endl;

    arr.push_back(7);
    //
//    for (int i = 0; i < arr.size(); ++i)
//    {
//        std::cout << arr[i] << ";";
//    }
//    std::cout << std::endl;


    for (uint64_t i = 0; i < arr.size(); ++i)
        assert(arr.at(i) == i);
    assert(arr.size() == 8);

    arr.pop_front();
    assert(arr[0] == 1);
    arr.pop_front();
    assert(arr[0] == 2);

    arr.pop_back();
    assert(arr[arr.size() - 1] == 6);
    arr.pop_back();
    assert(arr[arr.size() - 1] == 5);
    assert(arr.size() == 4);

//    for (int i = 0; i < arr.size(); ++i)
//    {
//        std::cout << arr[i] << ";";
//    }
//    std::cout << std::endl;

    arr.erase(2);
//    for (int i = 0; i < arr.size(); ++i)
//    {
//        std::cout << arr[i] << ";";
//    }
//    std::cout << std::endl;

    assert(arr[0] == 2);
    assert(arr[1] == 3);
    assert(arr[2] == 5);
    assert(arr.size() == 3);

    return 0;
}
