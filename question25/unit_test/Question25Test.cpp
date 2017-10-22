#include "my_class.h"

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using ::testing::Eq;
using ::testing::Test;

namespace Question25 {

namespace testing {

    class Question25Test : public Test
    {
       protected:
        Question25Test(){}
        ~Question25Test(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        MyClass my_class;

        static const size_t taskCount = 3;
        static const string default_str_repr;
    };

    const string Question25Test::default_str_repr = "My repr!";

    TEST_F(Question25Test, constructor_hasDefaultStrRepr)
    {
        EXPECT_THAT(my_class.str_repr(), Eq(Question25Test::default_str_repr));
    }

    TEST_F(Question25Test, kth_to_lastTest)
    {
        LinkedListNode* a = new LinkedListNode(1);
        LinkedListNode* b = new LinkedListNode(2);
        LinkedListNode* c = new LinkedListNode(3);
        LinkedListNode* d = new LinkedListNode(4);
        LinkedListNode* e = new LinkedListNode(5);

        a->next_ = b;
        b->next_ = c;
        c->next_ = d;
        d->next_ = e;

        LinkedListNode* result;
        result = MyClass::kth_to_last(2, a);
        EXPECT_THAT(result, Eq(d));
        ASSERT_ANY_THROW(MyClass::kth_to_last(8, a));
        ASSERT_ANY_THROW(MyClass::kth_to_last(0, a));
    }

} // namespace testing

} // namespace Question25

