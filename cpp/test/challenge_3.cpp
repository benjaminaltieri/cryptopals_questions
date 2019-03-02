/*
Single-byte XOR cipher

The hex encoded string:

1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736

has been XOR'd against a single character. Find the key, decrypt the message.

You can do this by hand. But don't: write code to do it for you.

How? Devise some method for "scoring" a piece of English plaintext. Character frequency is a good metric. Evaluate each output and choose the one with the best score.

Achievement Unlocked
You now have our permission to make "ETAOIN SHRDLU" jokes on Twitter.
 */
#include <iostream>

#include "util.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::ContainerEq;
using ::testing::Test;

using namespace std;

namespace cryptopals {

namespace test {

    class Challenge3 : public Test
    {
       protected:
        Challenge3(){}
        ~Challenge3(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        static const string single_byte_ciphered;
    };

    const string Challenge3::single_byte_ciphered = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    TEST_F(Challenge3, decipher_with_rank)
    {
        vector<uint8_t> data = util::decode_base16(Challenge3::single_byte_ciphered);
		uint8_t result = util::find_single_char_cipher(data);
		vector<uint8_t> deciphered = util::decipher_single_char_xor(data, result);
		string result_string = string(deciphered.begin(), deciphered.end());
        cout << "Best key is '" << result << "' resulting in:" << endl << result_string << endl;
    }

} // namespace test

} // namespace cryptopals

