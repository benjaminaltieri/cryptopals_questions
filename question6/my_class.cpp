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

#define CAKE_BASED_ANSWER 1
#if CAKE_BASED_ANSWER
class Overlap {
   public:
    Overlap(int start, int length) : start_(start), length_(length) {}
    Overlap() : Overlap(0, 0) {}

    int start() { return start_; }
    int length() { return length_; }
    bool has_overlap() { return length_ > 0; }

    static Overlap find_overlap(int start1, int length1, int start2, int length2);
   private:
    int start_;
    int length_;
};

Overlap Overlap::find_overlap(int start1, int length1, int start2, int length2)
{
    int end1 = start1 + length1, end2 = start2 + length2;
    int upper_start = start2 > start1 ? start2 : start1;
    int lower_end = end2 > end1 ? end1 : end2;
    return Overlap(upper_start, lower_end - upper_start);
}

Rectangle MyClass::find_intersection(Rectangle& r1, Rectangle& r2)
{
    Rectangle intersection;
    Overlap x_overlap = Overlap::find_overlap(r1.getLeftX(),
                                              r1.getWidth(),
                                              r2.getLeftX(),
                                              r2.getWidth()
                                              );
    Overlap y_overlap = Overlap::find_overlap(r1.getBottomY(),
                                              r1.getHeight(),
                                              r2.getBottomY(),
                                              r2.getHeight()
                                              );
    if (x_overlap.has_overlap() && y_overlap.has_overlap()) {
        intersection = Rectangle(x_overlap.start(),
                                 y_overlap.start(),
                                 x_overlap.length(),
                                 y_overlap.length()
                                 );
    }
    return intersection;
}
#else
Rectangle MyClass::find_intersection(Rectangle& r1, Rectangle& r2)
{
    Rectangle intersection;
    // test for x intersection
    Rectangle* lower_x = r1.getLeftX() > r2.getLeftX() ? &r2 : &r1;
    Rectangle* upper_x = lower_x == &r1 ? &r2 : &r1;
    Rectangle* lower_y = r1.getBottomY() > r2.getBottomY() ? &r2 : &r1;
    Rectangle* upper_y = lower_y == &r1 ? &r2 : &r1;
    int x_overlap = lower_x->getWidth() - (upper_x->getLeftX() - lower_x->getLeftX());
    int y_overlap = lower_y->getHeight() - (upper_y->getBottomY() - lower_y->getBottomY()) ;

    if (x_overlap > 0 && y_overlap > 0) {
        int new_left = upper_x->getLeftX();
        int new_bottom = upper_y->getBottomY();
        int new_width = x_overlap < upper_x->getWidth() ? x_overlap : upper_x->getWidth();
        int new_height = y_overlap < upper_y->getHeight() ? y_overlap : upper_y->getHeight();
        intersection = Rectangle(new_left, new_bottom, new_width, new_height);
    }
    return intersection;
}
#endif

