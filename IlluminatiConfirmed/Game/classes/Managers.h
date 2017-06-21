#pragma once

#include "Base.h"

namespace IlluminatiConfirmed {
namespace experimental {

class BaseManager {
 public:
  BaseManager(std::vector<BaseInterface>* vector_of_obj)
      : m_vec_of_obj(vector_of_obj) {}
  virtual void contact(const BaseInterface* sender) = 0;
  virtual void DoIt(const BaseInterface* sender) = 0;
  virtual ~BaseManager() {}

 protected:
  std::vector<BaseInterface>* m_vec_of_obj;
};

class ManagerBullets : public BaseManager {
 public:
  ManagerBullets(std::vector<BaseInterface>* vector_of_obj)
      : BaseManager(vector_of_obj) {}
  ~ManagerBullets() {}
};
}
}
