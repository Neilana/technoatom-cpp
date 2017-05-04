// usefull headers and usings
#include <iostream>
#include <cassert>
#include <string>
#include <exception>
#include <new>
#include <fstream>
#include <typeinfo>
#include <ctime>
#include <bitset>


using std::size_t;
using std::string;
using std::exception;

#include "ContainerInterface.h"

using IlluminatiConfirmed::ContainerInterface;

// bool
void ContainerInterface<bool>::dump(string str) const
{
    std::ofstream file;
    file.open("dump.txt",std::ofstream::out | std::ofstream::app);
    if(file.is_open())
    {
        auto space = [](unsigned int i) -> string
        {
            string sp = "";
            while (i-- > 0) sp += "    ";
            return sp;
        };
        std::time_t result = std::time(nullptr);
        file << std::asctime(std::localtime(&result)) << std::endl;

        //  file << "Array::" << str << std::endl << "{" << std::endl;
        file << str << std::endl << "{" << std::endl;
        file << space(1) << "My address: " << this->m_dataPtr << std::endl;
        file << space(1) << NAME_VAR(m_size) << " " << m_size << std::endl;
        file << space(1) << NAME_VAR(m_dataPtr) << " " << m_size << std::endl;
        file << space(2) << "{" << std::endl;
        std::string type(typeid(bool).name());

        if (m_dataPtr != nullptr)
        {
            if(type.size() < 4)         //I'm tired of catching bugs from the dump
            {
                for (size_t j = 0; j <= m_size/8; j++)
                    file << space(2) << "[" << j << "]" << " = " <<  std::bitset<8>(m_dataPtr[j]) << std::endl;
            }
            else { file<< space(3)<<"I cannot show array. It isn't a primitive data type."<<std::endl;}
        }
        file << space(2) << "}" << std::endl;
        file << space(1) << "}" << std::endl;
    }
    file.close();
}

