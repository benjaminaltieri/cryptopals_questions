#pragma once

#include <string>
#include <vector>

class ExampleClass {
   public:
    ExampleClass();
    ~ExampleClass();

    std::string str_repr() const;

   private:
    std::string str_repr_ = "My repr!";
};

void PrintTo(ExampleClass e, std::ostream* os);
