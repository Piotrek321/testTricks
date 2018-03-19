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
    m_mock = new ::testing::StrictMock<mockClass>;
    m_testObject = new testObject(m_mock);
  }

  virtual void TearDown() {
    delete m_mock;
    delete m_testObject;
  }
};

// PROTIP getValue1 must (?) be const to make it work
MATCHER_P(compareStructs, struct_, "") {
  return (arg.value1 == struct_.value1 && arg.str == struct_.str &&
          arg.getValue2() == struct_.getValue2());
};

MATCHER_P(compareVecStructs, vecStruct_, "") {
  return (arg[0].value1 == vecStruct_[0].value1 &&
          arg[0].str == vecStruct_[0].str &&
          arg[0].getValue2() == vecStruct_[0].getValue2());
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

/*
 * Test was writen to show how to handle methods which returns unique_ptr.
 * First case is the dummiest one. It just return unique_ptr, it does not verify
 * anything.
 */
TEST_F(test1, handleReturnUniquePtr) {
  auto handleReturnUniquePtr = []() {
    unique_ptr<int> ptr = make_unique<int>(int(4));
    return ptr;
  };

  EXPECT_CALL(*m_mock, returnUnique()).WillOnce(Invoke(handleReturnUniquePtr));
  m_testObject->callReturnUniquePtr();
}

/*
 * Test was writen to show how to handle methods which returns unique_ptr.
 * Second case is also not the best one. It will just return nullptr.
 */
TEST_F(test1, handleReturnUniquePtrReturnsNullptr) {

  EXPECT_CALL(*m_mock, returnUnique()).WillOnce(ReturnNull());
  m_testObject->callReturnUniquePtr();
}

/*
 * Test was writen to show how to handle methods which returns unique_ptr.
 * In third case, we have to "capture" pointer retunred by test object. After
 * method call, we verify that both unique_ptr and raw pointer points to the
 * same address.
 */
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
       << "&ptr1: " << &ptr1 << "\n"
       << "*ptr1.get(): " << *ptr1.get() << "\n"
       << "ptr1.get(): " << ptr1.get() << endl;
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
 * this course of action is (realizable) doable only if object under test
 * (our method) contains mocked method which takes as parameter (by reference or
 * by pointer) object mentioned above (this one which is created inside of
 * method).
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

TEST_F(test1, getUniquePtrAsArgument) {
  unique_ptr<int> uptr = make_unique<int>(50);
  EXPECT_CALL(*m_mock, getStdUniquePtrProxy(uptr.get()));

  m_testObject->getUniquePtrAsParameter(move(uptr));
}

TEST_F(test1, getStructAsParameter) {
  SomeValuesStruct struct_;
  struct_.str = "string";
  struct_.value1 = 1;
  struct_.setValue2(2);

  EXPECT_CALL(*m_mock, getStructAsParameter(compareStructs(struct_)));
  m_testObject->getStructAsParameter();
}

TEST_F(test1, getStructAsParameterSecondMethod) {
  SomeValuesStruct struct_;
  struct_.str = "string";
  struct_.value1 = 1;
  struct_.setValue2(2);

  //  EXPECT_CALL(*m_mock, getStructAsParameter((AllOf(
  //                           Field(&SomeValuesStruct::value1, Eq(1)),
  //                           Field(&SomeValuesStruct::str, Eq("string")),
  //                           Property(&SomeValuesStruct::getValue2,
  //                           Eq(2))))));
  //
  // OR
  //
  //  EXPECT_CALL(
  //      *m_mock,
  //      getStructAsParameter((AllOf(
  //          Field(&SomeValuesStruct::value1, Eq(struct_.value1)),
  //          Field(&SomeValuesStruct::str, Eq(struct_.str)),
  //          Property(&SomeValuesStruct::getValue2,
  //          Eq(struct_.getValue2()))))));
  //
  // OR
  EXPECT_CALL(*m_mock, getStructAsParameter(compareStructs(struct_)));

  m_testObject->getStructAsParameter();
}

TEST_F(test1, getVectorOfStructAsParameter) {
  vector<SomeValuesStruct> vecStruct_;
  SomeValuesStruct struct_;
  struct_.str = "string";
  struct_.value1 = 1;
  struct_.setValue2(2);
  vecStruct_.push_back(struct_);

  EXPECT_CALL(*m_mock,
              getVectorOfStructAsParameter(compareVecStructs(vecStruct_)));

  m_testObject->getVectorOfStructAsParameter();
}

TEST_F(test1, getVectorOfSharedPtrOfIntsAsParameter) {
  vector<shared_ptr<int>> vec;
  shared_ptr<int> ptr;
  for (int i = 0; i < 5; i++) {
    ptr = make_shared<int>(i);
    vec.push_back(ptr);
  }

  EXPECT_CALL(*m_mock, getVectorOfSharedPtrOfIntsAsParameter(_));

  m_testObject->getVectorOfSharedPtrOfIntsAsParameter();
}

TEST_F(test1, uniquePtrAsParameter) {
  auto pt = make_shared<CustomClass>("Object from test");
  EXPECT_CALL(*m_mock, sharedPtrAsParameterCreatedInside(_))
      .WillOnce(SetArgPointee<0>(*pt));

  m_testObject->uniquePtrAsParameter();
}

TEST_F(test1, uniquePtrAsParameterInvoke) {
  auto someLambda = [] {
    auto pt = make_shared<CustomClass>("Object from test");
  };
  EXPECT_CALL(*m_mock, sharedPtrAsParameterCreatedInside(_))
      .WillOnce(InvokeWithoutArgs(someLambda));

  m_testObject->uniquePtrAsParameter();
}
