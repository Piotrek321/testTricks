#ifndef MOCKKLASA_H
#define MOCKKLASA_H
#include "ClassIf.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>
class mockClass : public ClassIf {
public:
  mockClass() {}
  ~mockClass() {}
  void getStdUniquePtr(std::unique_ptr<int> uniqueptr) {
    getStdUniquePtrProxy(uniqueptr.get());
  }

  MOCK_METHOD2(sum, int &(int &a, int b));
  MOCK_METHOD1(print_, void(string &str));
  MOCK_METHOD1(printPtr, void(string *str));
  MOCK_METHOD0(returnUnique, unique_ptr<int>());
  MOCK_METHOD1(methodToBeCalledToInvokeAnotherMethodOnIt,
               void(anotherClass &anotherC));
  MOCK_METHOD1(getStdFunctionAsParameter, void(std::function<void(int)> fnc));
  MOCK_METHOD1(getStdUniquePtrProxy, void(int *uniqueptr));
  MOCK_METHOD1(getStructAsParameter, void(SomeValuesStruct &vec));
  MOCK_METHOD1(getVectorOfStructAsParameter,
               void(vector<SomeValuesStruct> &vec));
  MOCK_METHOD1(getVectorOfSharedPtrOfIntsAsParameter,
               void(vector<shared_ptr<int>> &vec));

  MOCK_METHOD1(sharedPtrAsParameterCreatedInside,
               void(shared_ptr<CustomClass> up));
};

#endif // MOCKKLASA_H
