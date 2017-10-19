#pragma once

#include <string>
#include <vector>

class MyClass {
   public:
    MyClass();
    ~MyClass();

    std::string str_repr() const;

    static long int make_change(int money, std::vector<int> coins);

   private:
    std::string str_repr_ = "My repr!";
};
