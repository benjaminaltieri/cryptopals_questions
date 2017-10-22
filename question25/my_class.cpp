#include "my_class.h"

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

LinkedListNode* MyClass::kth_to_last(int k, LinkedListNode* head)
{
    LinkedListNode *kth_to_last = head, *cur_node = head;
    if (k == 0) throw std::exception();
    while (cur_node != nullptr) {
        if (k > 0) {
            k--;
        } else {
            kth_to_last = kth_to_last->next_;
        }
        cur_node = cur_node->next_;
    }
    if (k > 0) throw std::exception();

    return kth_to_last;
}
