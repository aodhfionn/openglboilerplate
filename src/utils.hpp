#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

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

    void calcTime(float* last, float* dt)
    {
        float current;

        current = glfwGetTime();
        *dt = current - *last;
        *last = current;
    }
    
} // namespace util

#endif // UTILS_HPP