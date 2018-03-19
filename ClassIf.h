#ifndef KLASAIF_H
#define KLASAIF_H
#include <anotherClass.h>
#include <customclass.h>
#include <iostream>
#include <memory>
#include <string.h>
#include <vector>
class anotherClass;
using namespace std;

struct SomeValuesStruct {
  vector<int> values;
  int value1;
  string str;
  int getValue2() const {
    return value2;
  } // CONST IS NECESSARY FOR Propert(...) in tests //TODO How to handle non
  // const getters?
  void setValue2(int x) { value2 = x; }

private:
  int value2;
};

class ClassIf {
public:
  ClassIf(){};
  virtual ~ClassIf() {}
  virtual int &sum(int &a, int b) = 0;
  virtual void print_(string &str) = 0;
  virtual void printPtr(string *str) = 0;
  virtual unique_ptr<int> returnUnique() = 0;
  virtual void
  methodToBeCalledToInvokeAnotherMethodOnIt(anotherClass &anotherC) = 0;
  virtual void getStdFunctionAsParameter(std::function<void(int)> fnc) = 0;
  virtual void getStdUniquePtr(std::unique_ptr<int> uniqueptr) = 0;
  ////////////////////////////////////////////////////////////////////////////
  virtual void getStructAsParameter(SomeValuesStruct &vec) = 0;
  virtual void getVectorOfStructAsParameter(vector<SomeValuesStruct> &vec) = 0;
  virtual void
  getVectorOfSharedPtrOfIntsAsParameter(vector<shared_ptr<int>> &vec) = 0;

  virtual void
  sharedPtrAsParameterCreatedInside(shared_ptr<CustomClass> up) = 0;
};

#endif // KLASAIF_H
