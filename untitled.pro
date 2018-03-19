include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS +=     tst_yes.h \
    Class.h \
    ClassIf.h \
    mockClass.h \
    tst_test1.h \
    testObject.h \
    anotherClass.h \
    customclass.h

SOURCES +=     main.cpp \
    Class.cpp \
    testObject.cpp \
    anotherClass.cpp \
    customclass.cpp
