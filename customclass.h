#ifndef CUSTOMCLASS_H
#define CUSTOMCLASS_H
#include <iostream>

class CustomClass {
public:
  CustomClass(std::string echo);
  // CustomClass(const CustomClass &);
  // CustomClass &operator=(const CustomClass &) {
  //   std::cout << "CustomClass& operator =(const CustomClass &)\n";
  //  }
};

#endif // CUSTOMCLASS_H
