#include "my_class.h"

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using std::string;
using ::testing::Eq;
using ::testing::Test;

namespace ExampleQuestion {

namespace testing {

    class ExampleQuestionTest : public Test
    {
       protected:
        ExampleQuestionTest(){}
        ~ExampleQuestionTest(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        MyClass my_class;

        static const size_t taskCount = 3;
        static const string default_str_repr;
    };

    const string ExampleQuestionTest::default_str_repr = "My repr!";

    TEST_F(ExampleQuestionTest, constructor_hasDefaultStrRepr)
    {
        EXPECT_THAT(my_class.str_repr(), Eq(ExampleQuestionTest::default_str_repr));
    }

} // namespace testing

} // namespace ExampleQuestion

