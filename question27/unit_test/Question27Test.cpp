#include "my_class.h"

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using std::string;
using ::testing::Eq;
using ::testing::Test;

namespace Question27 {

namespace testing {

    class Question27Test : public Test
    {
       protected:
        Question27Test(){}
        ~Question27Test(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        MyClass my_class;

        static const size_t taskCount = 3;
        static const string default_str_repr;
        static const string reversed_str_repr;
    };

    const string Question27Test::default_str_repr = "My repr!";
    const string Question27Test::reversed_str_repr = "repr! My";

    TEST_F(Question27Test, constructor_hasDefaultStrRepr)
    {
        EXPECT_THAT(my_class.str_repr(), Eq(Question27Test::default_str_repr));
    }

    TEST_F(Question27Test, reverse_DefaultTest)
    {
        my_class.reverse_words();
        EXPECT_THAT(my_class.str_repr(), Eq(Question27Test::reversed_str_repr));
    }

    TEST_F(Question27Test, reverse_CakeExampleTest)
    {
        string message = "find you will pain only go you recordings security the into if";
        string reversed_message = "if into the security recordings you go only pain will you find";
        my_class = MyClass(message);
        my_class.reverse_words();
        EXPECT_THAT(my_class.str_repr(), Eq(reversed_message));
    }


} // namespace testing

} // namespace Question27

