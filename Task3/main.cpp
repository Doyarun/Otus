#include <map>
#include <iostream>
#include <vector>
#include "Container.h"
#include "MyAllocator.h"
#include "utils.h"

int main(int argc, char const *argv[])
{
    std::map<int, int> numericMap{};
    std::map<int, int, std::less<int>, MyAllocator<
			std::pair<
				const int, int>, 10>> numericMapCustom{};

    for(auto i = 0; i < 10; i++)
    {
        numericMap.insert(std::make_pair(i, factorial(i)));
        numericMapCustom.insert(std::make_pair(i, factorial(i)));
    }

    for(auto it = numericMapCustom.begin(); it!= numericMapCustom.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }

    Container<int> container;
    Container<int, MyAllocator<int, 10>> containerCustom;

    for(auto i = 0; i < 10; i++)
    {
        container.push_back(i);
        containerCustom.push_back(i);
    }
    containerCustom.clear();
    for(auto i = 0; i < 5; i++)
    {
        container.push_back(i);
        containerCustom.push_back(i);
    }

    for(auto item : containerCustom)
    {
        std::cout << item << std::endl;
    }
}