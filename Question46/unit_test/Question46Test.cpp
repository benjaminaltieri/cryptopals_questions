#include "my_class.h"

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::ContainerEq;
using ::testing::Test;

using namespace std;

namespace Question46 {

namespace testing {

    class Question46Test : public Test
    {
       protected:
        Question46Test(){}
        ~Question46Test(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        MyClass my_class;

        static const size_t taskCount = 3;
        static const string default_str_repr;
    };

    const string Question46Test::default_str_repr = "My repr!";

    TEST_F(Question46Test, constructor_hasDefaultStrRepr)
    {
        EXPECT_THAT(my_class.str_repr(), Eq(Question46Test::default_str_repr));
    }

    TEST_F(Question46Test, mesh_FindPathEmpty)
    {
        unordered_map<string, vector<string> > empty;
        EXPECT_THAT(MyClass::mesh_path(empty, {}), ContainerEq(vector<string>()));
    }

    TEST_F(Question46Test, mesh_FindPathBadName)
    {
        unordered_map<string, vector<string> > solo = { {"han", {"Chewy", "Luke", "Leia"} } };
        EXPECT_THAT(MyClass::mesh_path(solo, {}), ContainerEq(vector<string>()));
    }

    TEST_F(Question46Test, mesh_FindPath)
    {
        unordered_map<string, vector<string> > input = {
            { "Min",     { "William", "Jayden", "Omar" } },
            { "William", { "Min", "Noam" } },
            { "Jayden",  { "Min", "Amelia", "Ren", "Noam" } },
            { "Ren",     { "Jayden", "Omar" } },
            { "Amelia",  { "Jayden", "Adam", "Miguel" } },
            { "Adam",    { "Amelia", "Miguel", "Sofia", "Lucas" } },
            { "Miguel",  { "Amelia", "Adam", "Liam", "Nathan" } },
        };
        vector<string> output = { "Jayden", "Amelia", "Adam" };
        EXPECT_THAT(MyClass::mesh_path(input, pair<string, string>("Jayden", "Adam")), ContainerEq(output));
    }

    TEST_F(Question46Test, mesh_FindDeadEnd)
    {
        unordered_map<string, vector<string> > input = {
            { "Min",     { "William", "Jayden", "Omar" } },
            { "William", { "Min", "Noam" } },
            { "Jayden",  { "Min", "Amelia", "Ren", "Noam" } },
            { "Ren",     { "Jayden", "Omar" } },
            { "Amelia",  { "Jayden", "Adam", "Miguel" } },
            { "Adam",    { "Amelia", "Miguel", "Sofia", "Lucas" } },
            { "Miguel",  { "Amelia", "Adam", "Liam", "Nathan" } },
        };
        vector<string> output = {};
        EXPECT_THAT(MyClass::mesh_path(input, pair<string, string>("Jayden", "Maurice")), ContainerEq(output));
    }

} // namespace testing

} // namespace Question46

