#pragma once

#include <string>
using std::string;

namespace IlluminatiConfirmed
{
    class Exception
    {
    public:
        Exception(int code, const char *mess, const char *line, const char *file) : m_str("")
        {
            m_str = string("#")  + std::to_string(code) + string(mess) + string(line) + string(file) + string("\n");
        }

        const Exception operator+( const Exception &rhs)
        {
            m_str += rhs.m_str;
            return *this;
        }

        const char* what() const
        {
/* FIXME: Боже я в душе не понимаю что от меня хочет этот компилятор! Что значит "ошибка: passing 'const string
 *          {aka const std::__cxx11::basic_string<char>}' as 'this' argument discards qualifiers [-fpermissive]"?!
 *                    m_str.erase(i, 1);
 *                                    ^
            auto space = []() -> const string
            {
                    static int j;
                    int i = j++;
                    string sp = "";
                    while (i-- > 0) sp += "    ";
                    return sp;
        };

            for (int i = 0; i < m_str.size(); ++i)
            {
                if (m_str.at(i) == '#')
                {
                    m_str.erase(i, 1);
                    m_str.insert(i, space());
                }
            }
*/
            return m_str.c_str();
        }
    private:
        std::string m_str;
    };
}

