#ifndef MOCKKLASA_H
#define MOCKKLASA_H
#include "ClassIf.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>
class mockClass : public ClassIf {
public:
  mockClass(){};
  ~mockClass(){};
  MOCK_METHOD2(sum, int &(int &a, int b));
  MOCK_METHOD1(print_, void(string &str));
  MOCK_METHOD1(printPtr, void(string *str));
  MOCK_METHOD0(returnUnique, unique_ptr<int>());
  MOCK_METHOD1(methodToBeCalledToInvokeAnotherMethodOnIt,
               void(anotherClass &anotherC));
  MOCK_METHOD1(getStdFunctionAsParameter, void(std::function<void(int)> fnc));
};

#endif // MOCKKLASA_H
