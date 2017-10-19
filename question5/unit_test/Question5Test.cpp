#include "my_class.h"

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::Test;

using namespace std;

namespace Question5 {

namespace testing {

    class Question5Test : public Test
    {
       protected:
        Question5Test(){}
        ~Question5Test(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        MyClass my_class;

        static const size_t taskCount = 3;
        static const string default_str_repr;
    };

    const string Question5Test::default_str_repr = "My repr!";

    TEST_F(Question5Test, constructor_hasDefaultStrRepr)
    {
        EXPECT_THAT(my_class.str_repr(), Eq(Question5Test::default_str_repr));
    }

    TEST_F(Question5Test, simple_input_case_1)
    {
        int amount = 4;
        vector<int> coins = {1, 2, 3};
        long int expected = 4;
        EXPECT_THAT(MyClass::make_change(amount, coins), Eq(expected));
    }

    TEST_F(Question5Test, simple_input_case_2)
    {
        int amount = 5;
        vector<int> coins = {1, 3, 5};
        long int expected = 3;
        EXPECT_THAT(MyClass::make_change(amount, coins), Eq(expected));
    }

} // namespace testing

} // namespace Question5

