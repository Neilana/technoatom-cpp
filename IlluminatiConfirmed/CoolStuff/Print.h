#pragma once

#include <iostream>
#include <exception>

namespace IlluminatiConfirmed
{
    void print(const char *s)
    {
        while (*s) {
            if (*s == '#') {
                if (*(s + 1) == '#') {
                    ++s;
                }
                else {
                    throw std::runtime_error("Invalid format string: missing arguments.");
                }
            }
            std::cout << *s++;
        }
    }

    template<typename Tp, typename... Args>
    void print(const char *s, const Tp &value, const Args&... args)
    {
        while (*s) {
            if (*s == '#') {
                if (*(s + 1) == '#') {
                    ++s;
                }
                else {
                    std::cout << value;
                    print(++s, args...);
                    return;
                }
            }
            std::cout << *s++;
        }
    }
}
