#include "Class.h"
#include "anotherClass.h"
#include "mockClass.h"
#include "testObject.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <iostream>

using namespace testing;
class test1 : public ::testing::Test {

protected:
  mockClass *m_mock;
  std::unique_ptr<testObject> m_testObject_Uptr;
  testObject *m_testObject;

  virtual void SetUp() {
    m_mock = new mockClass;
    m_testObject = new testObject(m_mock);
  }

  virtual void TearDown() {
    delete m_mock;
    delete m_testObject;
  }
};

/*
 * Test is used to show how does SetArgReferee and SaveArgPointee works.
 * It could be used to "capture" or set variables we dont have direct access to.
 * I.e to set some local varible which is passed to one of our mocked method.
 */

TEST_F(test1, SaveArgPointeeAndSetArgReferee) {
  string *str = new string();
  string sss("ABC");

  EXPECT_CALL(*m_mock, printPtr(_))
      .WillOnce(SaveArgPointee<0>(str)); // srt == HELLO after function call
  EXPECT_CALL(*m_mock, print_(_)).WillOnce(SetArgReferee<0>(sss));

  testing::internal::CaptureStdout();
  EXPECT_EQ(*str, "");

  m_testObject->zrobCos();

  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(*str, "HELLO");
  EXPECT_EQ("str2 before mocked function was called: STR2\nstr2 after mocked "
            "function was called: ABC\n",
            output);

  delete str;
}

TEST_F(test1, handleReturnUniquePtr) {
  auto handleReturnUniquePtr = []() {
    unique_ptr<int> ptr = make_unique<int>(int(4));
    return ptr;
  };

  EXPECT_CALL(*m_mock, returnUnique()).WillOnce(Invoke(handleReturnUniquePtr));
  m_testObject->callReturnUniquePtr();
}

TEST_F(test1, handleReturnUniquePtrAndVerifyAddress) {
  int *ptrToBeVerified = new int(100);
  auto handleReturnUniquePtr = [&ptrToBeVerified]() {
    unique_ptr<int> ptr;
    ptr.reset(ptrToBeVerified);
    return ptr;
  };

  EXPECT_CALL(*m_mock, returnUnique()).WillOnce(Invoke(handleReturnUniquePtr));

  unique_ptr<int> ptr1 = m_testObject->callReturnUniquePtr();

  EXPECT_EQ(ptrToBeVerified, ptr1.get()) << "Pointer should not differ";
  cout << "ptrToBeVerified: " << ptrToBeVerified
       << "\n*ptrToBeVerified: " << *ptrToBeVerified << " "
       << "\n&ptrToBeVerified: " << &ptrToBeVerified << "\n";

  cout << "*ptr1: " << *ptr1 << "\n"
       << "&ptr1: " << &ptr1 << "\n";
  cout << "*ptr1.get(): " << *ptr1.get() << "\nptr1.get(): " << ptr1.get()
       << "\n";
}

TEST_F(test1, throwingException) {

  auto handleReturnUniquePtr = []() {
    string exception_ = "division by zero!";
    throw exception_;
    unique_ptr<int> ptr = make_unique<int>(int(4));
    return ptr;
  };
  // Another way of doing it is:
  // string exception_ = "division by zero!";
  // EXPECT_CALL(*m_mock, returnUnique()).WillOnce(Throw(exception_));

  EXPECT_CALL(*m_mock, returnUnique()).WillOnce(Invoke(handleReturnUniquePtr));
  m_testObject->callReturnUniquePtr();
}

TEST_F(test1, test4) {

  EXPECT_CALL(*m_mock, methodToBeCalledToInvokeAnotherMethodOnIt(_));
  m_testObject->methodCreateSomeObjectInside();
}

/*
 * Test is used to show how to handle situation where there is no dependency
 * injection patter.
 * So that object is created inside of the method of object under tests, and
 * there is also i.e if-else which
 * check (depends on) state of that barely created object. There are at least
 * two method to handle that.
 * DISCLAIMER:
 *   this course of action is (realizable) doable only if in object under test
 * (in our method)
 *   contains mocked method which takes as parameter (by reference or by
 * pointer) object mentioned above (this one which is created inside of method).
 */

TEST_F(test1, WithArgInvoke) {

  anotherClass another;
  testing::internal::CaptureStdout();

  EXPECT_CALL(*m_mock, methodToBeCalledToInvokeAnotherMethodOnIt(_))
      .WillOnce(WithArgs<0>(Invoke(
          [](anotherClass &another) { another.setShouldIfBeVisited(); })));

  // Another way of doing it is:
  // another.setShouldIfBeVisited();
  //  EXPECT_CALL(*m_mock, methodToBeCalledToInvokeAnotherMethodOnIt(_))
  //      .WillOnce(SetArgReferee<0>(another));

  m_testObject->methodCreateSomeObjectInside();

  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ("IF WAS VISITED\n", output);
}

void functionToBeInvoked(int x) {
  cout << "functionToBeInvoked(int x): x==" << x << endl;
}

TEST_F(test1, DoNotInvokeArgument) {
  std::function<void(int)> function = functionToBeInvoked;
  EXPECT_CALL(*m_mock, getStdFunctionAsParameter(_));

  m_testObject->getStdFunctionAsParameter(function);
}

TEST_F(test1, InvokeArgument) {
  std::function<void(int)> function = functionToBeInvoked;
  EXPECT_CALL(*m_mock, getStdFunctionAsParameter(_))
      .WillOnce(InvokeArgument<0>(50));

  testing::internal::CaptureStdout();
  m_testObject->getStdFunctionAsParameter(function);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ("functionToBeInvoked(int x): x==50\n", output);
}
