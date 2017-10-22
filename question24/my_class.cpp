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

LinkedListNode* MyClass::reverse_list(LinkedListNode* head)
{
    LinkedListNode *new_head = nullptr, *cur_node = head;

    while (cur_node != nullptr) {
        LinkedListNode* last_head = new_head;
        new_head = cur_node;
        cur_node = cur_node->next_;
        new_head->next_ = last_head;
    }

    return new_head;
}
