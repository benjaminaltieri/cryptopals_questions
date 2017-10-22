#pragma once

#include <string>
#include <vector>

class MyClass {
   public:
    MyClass();
    MyClass(std::string s) : str_repr_(s) {}
    ~MyClass();

    std::string str_repr() const;

    void reverse_chars(void);
    void reverse_words(void);

   private:
    std::string str_repr_ = "My repr!";
};
