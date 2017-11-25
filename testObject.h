#ifndef testObject_H
#define testObject_H
#include "ClassIf.h"

class testObject {
public:
  testObject(ClassIf *externalDependency);
  unique_ptr<int> callReturnUniquePtr();
  void zrobCos();
  void methodCreateSomeObjectInside();
  void getStdFunctionAsParameter(std::function<void(int)> fnc);

  ClassIf *m_externalDependency;
};

#endif // testObject_H
