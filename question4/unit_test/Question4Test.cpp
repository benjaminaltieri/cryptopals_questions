#include "my_class.h"

#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::Test;

using namespace std;

::std::ostream& operator<<(::std::ostream& os, const Meeting& meeting) {
    return os << "Meeting(start: " << meeting.getStartTime() << ", end: " << meeting.getEndTime() << ")";
}
// It's important that PrintTo() is defined in the SAME
// namespace that defines Bar.  C++'s look-up rules rely on that.
void PrintTo(const Meeting& meeting, ::std::ostream* os) {
  *os << meeting;
}

namespace Question4 {

namespace testing {

    class Question4Test : public Test
    {
       protected:
        Question4Test(){}
        ~Question4Test(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        MyClass my_class;

        static const size_t taskCount = 3;
        static const string default_str_repr;
    };

    const string Question4Test::default_str_repr = "My repr!";

    TEST_F(Question4Test, firstSampleInput)
    {
        vector<Meeting> input = {Meeting(0, 1), Meeting(3, 5), Meeting(4, 8), Meeting(10, 12), Meeting(9, 10)},
                       output = {Meeting(0, 1), Meeting(3, 8), Meeting(9, 12)};
        EXPECT_THAT(MyClass::mergeRanges(input), Eq(output));
    }

    TEST_F(Question4Test, secondSampleInput)
    {
        vector<Meeting> input = {Meeting(0, 5), Meeting(0, 2), Meeting(0, 10), Meeting(0, 12), Meeting(0, 20)},
                       output = {Meeting(0, 20)};
        EXPECT_THAT(MyClass::mergeRanges(input), Eq(output));
    }

    TEST_F(Question4Test, noOverlapsInput)
    {
        vector<Meeting> input = {Meeting(4, 5), Meeting(0, 2), Meeting(50, 60), Meeting(10, 12), Meeting(18, 20)},
                       output = {Meeting(0, 2), Meeting(4, 5), Meeting(10, 12), Meeting(18, 20), Meeting(50, 60)};
        EXPECT_THAT(MyClass::mergeRanges(input), Eq(output));
    }

} // namespace testing

} // namespace Question4

