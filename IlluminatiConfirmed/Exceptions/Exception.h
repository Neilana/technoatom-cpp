#pragma once

#include <string>
#include <sstream>
#include <iostream>
using std::string;

namespace IlluminatiConfirmed
{
    class Exception
    {
    public:

        /*!
         * \brief Exception Forms a string with information about the error.
         * Each constructor increments a static counter for a beautiful display,
         * so you shouldn't create extra objects of this type, otherwise you will see too much tabs.
         * \param code Error code
         * \param mess Message
         * \param line Line of code where it have happened
         * \param file File of line where it have happened
         * \param func Function of file where it have happened
         */
        Exception(int code, const char *mess, int line, const char *file, const char *func) : m_number(count++)
        {
            ++countObjects;
            std::stringstream os;
            m_str = new string();
            os<<std::noskipws<<"#"<<m_number<<"Error code: "<<code<<".\n On line: "<<line<<".\n In file: "<<file<<".\n In func: "<<func<<".\n Message: "<<mess<<"\n%";
            *m_str = os.str();
        }

        /*!
         * \brief Exception Overload
         * \param other
         */
        Exception (const Exception &other) : m_number(other.m_number)
        {
            ++countObjects;
            m_str = new string(*(other.m_str));
        }

        /*!
         * \brief operator + Allows you to accumulate information about errors
         * \param rhs The exception which has just been captured
         * \return Copy
         */
        const Exception operator+(const Exception &rhs)
        {
            if (m_number >= rhs.m_number)
            {
                Exception temp(*this);
                *(temp.m_str) += *rhs.m_str;
                return temp;
            } else
            {
                Exception temp(rhs);
                *(temp.m_str) += *m_str;
                return temp;
            }

        }

        ~Exception()
        {
            --countObjects;
            if (countObjects == 0) count = 0;
            delete m_str;
        }

        /*!
         * \brief what Returns the explanatory string.
         * \return String
         */
        const string what() const
        {
            auto space = [](int j) -> const string
            {
                    string sp = "";
                    while (j-- > 0) sp += "  ";
                    return sp;
            };
            std::stringstream os;
            os <<std::noskipws<< *m_str;
            string azz;
            char ch;
            int sp;
            while(os>>ch)
            {
                switch (ch)
                {
                case '#':
                    os >> sp;
                    azz += ' ';
                    azz +=space(sp);
                    break;
                case '\n':
                    azz += ch;
                    azz += space(sp);
                    break;
                case '%':
                    azz += '\n';
                    break;
                default:
                    azz += ch;
                    break;
                }
            }
            return azz;
        }
    private:
        int m_number;
        std::string *m_str;
        static int count;
        static int countObjects; //нужно больше говнокода
    };
    int IlluminatiConfirmed::Exception::count = 0;
    int IlluminatiConfirmed::Exception::countObjects = 0;
}

