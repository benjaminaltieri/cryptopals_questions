#include <iostream>
using namespace std;

string myFunction (const string& arg)
{
    // write the body of your function here
    return "running with " + arg;
}

int main ()
{
    // run your function through some test cases here
    // remember: debugging is half the battle!
    cout << myFunction ("test input");
    return 0;
}
