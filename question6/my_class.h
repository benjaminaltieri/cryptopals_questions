#pragma once

#include <string>
#include <vector>

#include "Rectangle.h"

class MyClass {
   public:
    MyClass();
    ~MyClass();

    std::string str_repr() const;

    static Rectangle find_intersection(Rectangle& r1, Rectangle& r2);

   private:
    std::string str_repr_ = "My repr!";
};
