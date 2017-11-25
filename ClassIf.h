#ifndef KLASAIF_H
#define KLASAIF_H
#include <anotherClass.h>
#include <iostream>
#include <memory>
#include <string.h>
class anotherClass;
using namespace std;
class ClassIf {
public:
  ClassIf(){};
  virtual ~ClassIf(){};
  virtual int &sum(int &a, int b) = 0;
  virtual void print_(string &str) = 0;
  virtual void printPtr(string *str) = 0;
  virtual unique_ptr<int> returnUnique() = 0;
  virtual void
  methodToBeCalledToInvokeAnotherMethodOnIt(anotherClass &anotherC) = 0;
  virtual void getStdFunctionAsParameter(std::function<void(int)> fnc) = 0;
};

#endif // KLASAIF_H
