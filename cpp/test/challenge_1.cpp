/*
Convert hex to base64

The string:

49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d

Should produce:

SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

So go ahead and make that happen. You'll need to use this code for the rest of the exercises.

Cryptopals Rule
Always operate on raw bytes, never on encoded strings. Only use hex and base64 for pretty-printing.
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

    class Challenge1 : public Test
    {
       protected:
        Challenge1(){}
        ~Challenge1(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        static const string test_input_string;
        static const string test_output_string;
    };

    const string Challenge1::test_input_string = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    const string Challenge1::test_output_string = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

    TEST_F(Challenge1, simple_three_octet_to_base64)
    {
        vector<uint8_t> bytes = {'M', 'a', 'n'};
        EXPECT_THAT(util::encode_base64(bytes), Eq("TWFu"));
    }

    TEST_F(Challenge1, simple_two_octet_to_base64)
    {
        vector<uint8_t> bytes = {'M', 'a'};
        EXPECT_THAT(util::encode_base64(bytes), Eq("TWE="));
    }

    TEST_F(Challenge1, single_octet_to_base64)
    {
        vector<uint8_t> bytes = {'M'};
        EXPECT_THAT(util::encode_base64(bytes), Eq("TQ=="));
    }

    TEST_F(Challenge1, base16_to_base64)
    {
        EXPECT_THAT(util::base16_to_base64(Challenge1::test_input_string), Eq(Challenge1::test_output_string));
    }

} // namespace test

} // namespace cryptopals

