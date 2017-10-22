#include "my_class.h"

using namespace std;

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

std::string MyClass::str_repr() const
{
    return str_repr_;
}

static void reverse_chars(char* left, char* right)
{
    while(left < right)
    {
        *left ^= *right;
        *right ^= *left;
        *left ^= *right;
        left++;
        right--;
    }
}

void MyClass::reverse_chars(void)
{
    char *left = &str_repr_[0], *right = &str_repr_[str_repr_.length() - 1];
    ::reverse_chars(left, right);
}

void MyClass::reverse_words(void)
{
    char *left = &str_repr_[0], *right = &str_repr_[0];
    reverse_chars();
    for(char* c = left + 1; c < &str_repr_[str_repr_.length()]; c++)
    {
        if (*c == ' ') {
            if (right > left) ::reverse_chars(left, right);
            left = c + 1;
        }
        right++;
    }
    if (right > left) ::reverse_chars(left, right);
}
