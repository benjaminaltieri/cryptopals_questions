#pragma once

#include <vector>

#include "meeting.h"

class MyClass {
   public:
    MyClass();
    ~MyClass();
    static std::vector<Meeting> mergeRanges(std::vector<Meeting> meetings);
};

