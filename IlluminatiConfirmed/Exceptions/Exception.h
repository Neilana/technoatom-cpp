#pragma once

#include <string>
#include <sstream>
#include <vector>
using std::string;
using std::vector;

#define EXCEPTION(message, ptr_on_Exception_or_nullptr) IlluminatiConfirmed::Exception(__LINE__, __FILE__, __PRETTY_FUNCTION__, message, ptr_on_Exception_or_nullptr );

namespace IlluminatiConfirmed
{
    class Exception
    {
        /*!
         * \brief The ExceptionData struct Struct of data of exceptions
         */
        struct ExceptionData
        {
            ExceptionData() : line(0), file(""), func(""), message("") {}
            ExceptionData(int l, string &&fu, string &&fi, string &&m) : line(l), file(fi), func(fu), message(m) {}
            int line;
            string file;
            string func;
            string message;
        };
    public:

        /*!
         * \brief Exception Forms a string with information about the error.
         * \param code Error code
         * \param mess Message
         * \param line Line of code where it have happened
         * \param file File of line where it have happened
         * \param func Function of file where it have happened
         */
        Exception(int line, const char *file, const char *func, const char *message, const Exception *other = nullptr) : m_exceptionStorage(0)
        {
            if (other != nullptr)
            {
                m_exceptionStorage = other->m_exceptionStorage;
            }
            m_exceptionStorage.push_back(ExceptionData(line, string(file), string(func), string(message)));
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
            int j = 0;
            for(auto it : m_exceptionStorage)
            {
                os<<std::noskipws<<space(j)<<"On line: "<<it.line<<".\n"<<space(j)<<"In file: "<<it.file<<".\n"<<space(j)<<"In func: "<<it.func<<".\n"<<space(j)<<"Message: "<<it.message<<"\n";
                ++j;
            }
            return os.str();
        }
    private:

        /*!
         * \brief m_exceptionStorage Data of a exception keep here
         */
        vector<ExceptionData> m_exceptionStorage;
    };
}


