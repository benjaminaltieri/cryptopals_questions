/*
Fixed XOR

Write a function that takes two equal-length buffers and produces their XOR combination.

If your function works properly, then when you feed it the string:

1c0111001f010100061a024b53535009181c

after hex decoding, and when XOR'd against:

686974207468652062756c6c277320657965

should produce:

746865206b696420646f6e277420706c6179
 */
#include "util.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::ContainerEq;
using ::testing::Test;

using namespace std;

namespace cryptopals {

namespace test {

    class Challenge2 : public Test
    {
       protected:
        Challenge2(){}
        ~Challenge2(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        static const string test_input_string1;
        static const string test_input_string2;
        static const string test_output_string;
    };

    const string Challenge2::test_input_string1 = "1c0111001f010100061a024b53535009181c";
    const string Challenge2::test_input_string2 = "686974207468652062756c6c277320657965";
    const string Challenge2::test_output_string = "746865206b696420646f6e277420706c6179";

    TEST_F(Challenge2, xor_test_challenge2)
    {
        std::vector<uint8_t> input1 = util::decode_base16(Challenge2::test_input_string1);
        std::vector<uint8_t> input2 = util::decode_base16(Challenge2::test_input_string2);
        std::vector<uint8_t> output = util::fixed_xor(input1, input2);
        std::string result = util::encode_base16(output);
        EXPECT_THAT(result, Eq(Challenge2::test_output_string));
    }

} // namespace test

} // namespace cryptopals

