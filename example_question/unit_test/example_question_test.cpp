#include "example_class.h"

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::ContainerEq;
using ::testing::Test;

using namespace std;

#ifdef GTEST_CUSTOM_TYPE_PRINTING
::std::ostream& operator<<(::std::ostream& os, const CustomType& custom_type) {
    return os << "CustomType(value: " << custom_type.value() << ")";
}

void PrintTo(const CustomType& custom_type, ::std::ostream* os) {
  *os << custom_type;
}
#endif

namespace ExampleQuestion {

namespace testing {

    class ExampleQuestionTest : public Test
    {
       protected:
        ExampleQuestionTest(){}
        ~ExampleQuestionTest(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        ExampleClass example_class;

        static const size_t taskCount = 3;
        static const string default_str_repr;
    };

    const string ExampleQuestionTest::default_str_repr = "My repr!";

    TEST_F(ExampleQuestionTest, constructor_hasDefaultStrRepr)
    {
        EXPECT_THAT(example_class.str_repr(), Eq(ExampleQuestionTest::default_str_repr));
    }

} // namespace testing

} // namespace ExampleQuestion

