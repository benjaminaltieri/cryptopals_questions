#include <iostream>

#include "example_class.h"

using namespace std;

string ExampleFunction(const string& arg)
{
    // for when a single function will do (no class/lib needed)
    return "running with " + arg;
}

int main ()
{
    // old school test cases and console output here
    cout << ExampleFunction("test input") << endl;

    return 0;
}
