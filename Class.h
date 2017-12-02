#ifndef KLASA_H
#define KLASA_H
#include "ClassIf.h"

class Base {
public:
  Base(int i) { cout << "Base(int i)\n"; }

protected:
  Base();
};
// Object of Derived cannot be created
class Derived : virtual public Base {
public:
  Derived() { cout << "Derived()\n"; }
};
class Createable : virtual public Derived {
public:
  Createable(int x) : Base(x) { cout << "Createable()\n"; }
};

class Class : public ClassIf {
public:
  Class();
  int &sum(int &a, int b);
  void print_(string &str);
  void printPtr(string *str);
  virtual unique_ptr<int> returnUnique();
  void methodToBeCalledToInvokeAnotherMethodOnIt(anotherClass &anotherC);
  virtual void getStdFunctionAsParameter(std::function<void(int)> fnc);
  virtual void getStdUniquePtr(std::unique_ptr<int> uniqueptr);
  virtual void getStructAsParameter(SomeValuesStruct &vec);
  virtual void getVectorOfStructAsParameter(vector<SomeValuesStruct> &vec);
  virtual void
  getVectorOfSharedPtrOfIntsAsParameter(vector<shared_ptr<int>> &vec);

  SomeValuesStruct m_someValuesStruct;
};

#endif // KLASA_H
