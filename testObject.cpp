#include "testObject.h"
#include <memory>
testObject::testObject(ClassIf *externalDependency) {
  m_externalDependency = externalDependency;
}
void testObject::zrobCos() {
  string *str1 = new string("HELLO");
  string str2("STR2");
  std::cout << "str2 before mocked function was called: " << str2 << endl;
  m_externalDependency->printPtr(str1);
  m_externalDependency->print_(str2);
  std::cout << "str2 after mocked function was called: " << str2 << endl;

  delete str1;
}

void testObject::methodCreateSomeObjectInside() {
  anotherClass anotherC;
  m_externalDependency->methodToBeCalledToInvokeAnotherMethodOnIt(anotherC);

  if (anotherC.shouldIfBeVisited) {
    std::cout << "IF WAS VISITED" << std::endl;
  } else {
    std::cout << "IF WAS NOT VISITED" << std::endl;
  }
}

unique_ptr<int> testObject::callReturnUniquePtr() {
  unique_ptr<int> upointer{nullptr};
  try {

    upointer = m_externalDependency->returnUnique();
    return upointer;
  } catch (string w) {
    cout << "Exception: " << w;
  }
  return upointer;
}

void testObject::getStdFunctionAsParameter(std::function<void(int)> fnc) {

  m_externalDependency->getStdFunctionAsParameter(fnc);
}
