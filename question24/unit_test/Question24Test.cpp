#include "my_class.h"

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using ::testing::Eq;
using ::testing::Test;

namespace Question24 {

namespace testing {

    class Question24Test : public Test
    {
       protected:
        Question24Test(){}
        ~Question24Test(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        MyClass my_class;

        static const size_t taskCount = 3;
        static const string default_str_repr;
    };

    const string Question24Test::default_str_repr = "My repr!";

    TEST_F(Question24Test, constructor_hasDefaultStrRepr)
    {
        EXPECT_THAT(my_class.str_repr(), Eq(Question24Test::default_str_repr));
    }

    TEST_F(Question24Test, basic_listReversal)
    {
#if 1
        //vector<int> initial({ 2, 4, 6, 5, 8 }), final({ 8, 5, 6, 4, 2 }), check;
        vector<int> initial({ 2 }), final({ 2 }), check;
        LinkedListNode *input, *output, *loop;
        input = new LinkedListNode(initial[0]);
        loop = input;
        for(auto it = initial.begin() + 1; it < initial.end(); it++) {
            loop->next_ = new LinkedListNode(*it);
            loop = loop->next_;
        }
        loop->next_ = nullptr;
        output = MyClass::reverse_list(input);
        loop = output;
        while (loop) {
            check.push_back(loop->intValue_);
            loop = loop->next_;
        }
        EXPECT_THAT(check, ::testing::ContainerEq(final));
        loop = output;
        while (loop) {
            output = loop;
            loop = loop->next_;
            delete output;
        }
#else
        EXPECT_THAT(MyClass::reverse_list(nullptr), Eq(nullptr));
#endif
    }

} // namespace testing

} // namespace Question24

