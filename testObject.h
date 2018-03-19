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
  void getUniquePtrAsParameter(unique_ptr<int> uptr);
  void getStructAsParameter();
  void getVectorOfStructAsParameter();
  void getVectorOfSharedPtrOfIntsAsParameter();
  void uniquePtrAsParameter();

  ClassIf *m_externalDependency;
};

#endif // testObject_H
