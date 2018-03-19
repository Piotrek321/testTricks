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

void testObject::getUniquePtrAsParameter(unique_ptr<int> uptr) {
  cout << "*uptr: " << *uptr << "\nuptr.get(): " << uptr.get()
       << "\n*uptr.get(): " << *uptr.get() << "\n&uptr: " << &uptr << endl;

  m_externalDependency->getStdUniquePtr(std::move(uptr));
}

void testObject::getStructAsParameter() {
  SomeValuesStruct struct_;
  struct_.str = "string";
  struct_.value1 = 1;
  struct_.setValue2(2);

  m_externalDependency->getStructAsParameter(struct_);
}

void testObject::getVectorOfStructAsParameter() {
  vector<SomeValuesStruct> vecStruct_;
  SomeValuesStruct struct_;
  struct_.str = "string";
  struct_.value1 = 1;
  struct_.setValue2(2);
  vecStruct_.push_back(struct_);

  m_externalDependency->getVectorOfStructAsParameter(vecStruct_);
}

void testObject::getVectorOfSharedPtrOfIntsAsParameter() {

  vector<shared_ptr<int>> vec;
  shared_ptr<int> ptr;
  for (int i = 0; i < 5; i++) {
    ptr = make_shared<int>(i);
    vec.push_back(ptr);
  }

  m_externalDependency->getVectorOfSharedPtrOfIntsAsParameter(vec);
}

void testObject::uniquePtrAsParameter() {
  m_externalDependency->sharedPtrAsParameterCreatedInside(
      make_shared<CustomClass>("Object from function"));
}
