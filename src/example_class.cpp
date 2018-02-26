#include "example_class.h"

using namespace std;

ExampleClass::ExampleClass()
{
}

ExampleClass::~ExampleClass()
{
}

std::string ExampleClass::str_repr() const
{
    return str_repr_;
}
