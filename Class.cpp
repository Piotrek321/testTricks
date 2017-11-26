#include "Class.h"

Class::Class() {}
unique_ptr<int> Class::returnUnique() {

  unique_ptr<int> uniquePtr;
  int *rawPtr;
  int val = 5;
  rawPtr = &val;
  uniquePtr.reset(rawPtr);
  return uniquePtr;
}

int &Class::sum(int &a, int b) {
  cout << "SUMA";
  a = a + b;
  return a;
}

void Class::print_(string &str) {
  cout << "Str: " << str;
  // return str;
}

void Class::printPtr(string *str) {
  *str = "XXXX";

  cout << "wyprintujPointer: " << *str;
  // return " ";
}

void Class::methodToBeCalledToInvokeAnotherMethodOnIt(anotherClass &anotherC) {
  cout << "void Class::methodToBeCalledToInvokeAnotherMethodOnIt(anotherClass& "
          "anotherC)"
       << endl;
}

void Class::getStdFunctionAsParameter(std::function<void(int)> fnc) {
  cout << "void Class::getStdFunctionAsParameter(std::function<void(int)> fnc)"
       << endl;
}
void Class::getStdUniquePtr(std::unique_ptr<int> uniqueptr) {
  cout << "void Class::getStdUniquePtr(std::unique_ptr<int> uniqueptr). "
          "*uniqueptr: "
       << *uniqueptr << endl;
}
