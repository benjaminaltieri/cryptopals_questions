#pragma once

#include <string>
#include <vector>

class MyClass {
   public:
    MyClass();
    ~MyClass();

    std::string str_repr() const;

   private:
    std::string str_repr_ = "My repr!";
};
