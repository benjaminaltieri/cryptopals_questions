#pragma once

#include <string>
#include <vector>

#include "LinkedListNode.h"

class MyClass {
   public:
    MyClass();
    ~MyClass();

    std::string str_repr() const;

    static LinkedListNode* reverse_list(LinkedListNode* head);

   private:
    std::string str_repr_ = "My repr!";
};
