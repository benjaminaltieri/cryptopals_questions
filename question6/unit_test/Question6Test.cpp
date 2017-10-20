#include "my_class.h"

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::Test;

using namespace std;

::std::ostream& operator<<(::std::ostream& os, const Rectangle& r) {
    os << "Rectangle(Left: " << r.getLeftX() << ", Bottom: " << r.getBottomY();
    os << ", Width: " << r.getWidth() << ", Height: " << r.getHeight() << ")";
    return os;
}
// It's important that PrintTo() is defined in the SAME
// namespace that defines Bar.  C++'s look-up rules rely on that.
void PrintTo(const Rectangle& r, ::std::ostream* os) {
  *os << r;
}

namespace Question6 {

namespace testing {

    class Question6Test : public Test
    {
       protected:
        Question6Test(){}
        ~Question6Test(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        MyClass my_class;

        static const size_t taskCount = 3;
        static const string default_str_repr;
    };

    const string Question6Test::default_str_repr = "My repr!";

    TEST_F(Question6Test, constructor_hasDefaultStrRepr)
    {
        EXPECT_THAT(my_class.str_repr(), Eq(Question6Test::default_str_repr));
    }

    TEST_F(Question6Test, basic_intersectingRects)
    {
        Rectangle r1(2, 1, 3, 3), r2(4, 2, 2, 4), intersect(4, 2, 1, 2);
        EXPECT_THAT(MyClass::find_intersection(r1, r2), Eq(intersect));
    }

    TEST_F(Question6Test, inside_intersectingRects)
    {
        Rectangle r1(2, 1, 5, 5), r2(4, 2, 2, 2), intersect(4, 2, 2, 2);
        EXPECT_THAT(MyClass::find_intersection(r1, r2), Eq(intersect));
    }

    TEST_F(Question6Test, not_intersectingRects)
    {
        Rectangle r1(2, 1, 2, 2), r2(1, 5, 2, 2), intersect(0, 0, 0, 0);
        EXPECT_THAT(MyClass::find_intersection(r1, r2), Eq(intersect));
    }

    TEST_F(Question6Test, sharedEdge_intersectingRects)
    {
        Rectangle r1(2, 1, 2, 2), r2(1, 3, 2, 2), intersect(0, 0, 0, 0);
        EXPECT_THAT(MyClass::find_intersection(r1, r2), Eq(intersect));
    }

} // namespace testing

} // namespace Question6

