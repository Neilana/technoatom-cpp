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
         * \brief Exception Forms a string with information about the error
         * \param code Error code
         * \param mess Message
         * \param line Line of code where it have happened
         * \param file File of line where it have happened
         * \param func Function of file where it have happened
         */
        Exception(int code, const char *mess, int line, const char *file, const char *func)
        {
            std::stringstream os;
            m_str = new string();
            os<<"#"<<"Error code: "<<code<<".\n On line: "<<line<<".\n In file: "<<file<<"\n in func: "<<func<<".\n Message: "<<mess<<"\n\n%";
            *m_str = os.str();
        }

        /*!
         * \brief Exception Overload
         * \param other
         */
        Exception (const Exception &other)
        {
            m_str = new string(*(other.m_str));
        }

        /*!
         * \brief operator + Allows you to accumulate information about errors
         * \param rhs The exception which has just been captured
         * \return Copy
         */
        const Exception operator+(const Exception &rhs)
        {
            Exception temp(*this);
            *(temp.m_str) += *rhs.m_str;
            return temp;
        }

        ~Exception()
        {
            delete m_str;
        }

        /*!
         * \brief what Returns the explanatory string.
         * \return String
         */
        const char* what() const
        {
            auto space = [](int j) -> const string
            {
                    string sp = "";
                    while (j-- > 0) sp += "    ";
                    return sp;
        };
            for (int i = m_str->size() - 1, j = 0; i >= 0 ; --i)
            {
                if (m_str->at(i) == '#')
                {
                    m_str->erase(i, 1);
                    m_str->insert(i, space(++j));
                }
                if (m_str->at(i) == '\n')
                {
                    if (m_str->at(i + 1) != '%')
                    {
                        m_str->insert(i + 1, space(j));
                    } else m_str->erase(i + 1, 1);
                }
            }
            return m_str->c_str();
        }
    private:
        std::string *m_str;
    };
}

