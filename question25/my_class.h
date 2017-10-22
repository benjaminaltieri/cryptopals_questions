#pragma once

#include <string>
#include <vector>

#include "LinkedListNode.h"

class MyClass {
   public:
    MyClass();
    ~MyClass();

    std::string str_repr() const;

    static LinkedListNode* kth_to_last(int k, LinkedListNode* head);

   private:
    std::string str_repr_ = "My repr!";
};
