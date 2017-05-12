#pragma once

#include "../Exceptions/Exception.h"

template <class Tp>
const Tp& IlluminatiConfirmed::ContainerInterface<Tp>::operator[](
    size_type index) const {
  DUMP("in mb out");
  ASSERT_OK((index < m_size));
  if (index < m_size) {
    return m_dataPtr[index];
  } else {
    ASSERT_OK(!"Out of range");
    throw std::out_of_range("ERRROOOORRRRR");
  }
}

template <class Tp>
Tp& IlluminatiConfirmed::ContainerInterface<Tp>::at(size_type index) {
  DUMP("in mb out");
  // ASSERT_OK((index < m_size));
  if (index < m_size) {
    return m_dataPtr[index];
  } else {
    ASSERT_OK(!"Out of range");
    throw EXCEPTION("out of range", nullptr);
    // throw std::out_of_range("ERRROOOORRRRR");
  }
}

template <class Tp>
void IlluminatiConfirmed::ContainerInterface<Tp>::dump(std::string str) const {
  std::ofstream file;
  file.open("dump.txt", std::ofstream::out | std::ofstream::app);
  if (file.is_open()) {
    auto space = [](unsigned int i) -> std::string {
      std::string sp;
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
    std::string type(typeid(Tp).name());

    if (m_dataPtr != nullptr) {
      if (type.size() < 4)  // I'm tired of catching bugs from the dump
      {
        for (size_t j = 0; j < m_size; j++)
          file << space(2) << "[" << j << "]"
               << " = " << m_dataPtr[j] << std::endl;
      } else {
        file << space(3)
             << "I cannot show array. It isn't a primitive data type."
             << std::endl;
      }
    }
    file << space(2) << "}" << std::endl;
    file << space(1) << "}" << std::endl;
  }
  file.close();
}

template <class Tp>
bool IlluminatiConfirmed::ContainerInterface<Tp>::operator==(
    const ContainerInterface<Tp>& rhs) const {
  DUMP("in");
  if (m_size != rhs.m_size) return false;

  auto itRhs =
      rhs.begin();  // wtf why const auto it = rhs.begin(); doesnt compile
  for (auto const& itThis : *this)
    if (*(itRhs++) != itThis) return false;
  DUMP("out");
  return true;
}

template <class Tp>
IlluminatiConfirmed::ContainerInterface<Tp>::~ContainerInterface() {
  DUMP("in/out");
}
