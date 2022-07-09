#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>

namespace util
{
    template<typename T>
    int vectorSearch(T desired, std::vector<T> vector)
    {
        unsigned int i;
        for (auto& element : vector) {
            if (element == desired) return i;
            i++;
        }

        return -1;
    }

} // namespace util

#endif // UTILS_HPP