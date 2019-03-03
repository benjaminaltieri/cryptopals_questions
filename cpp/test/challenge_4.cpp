/*
Detect single-character XOR
One of the 60-character strings in this file has been encrypted by single-character XOR.

Find it.

(Your code from #3 should help.)
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

    class Challenge4 : public Test
    {
       protected:
        Challenge4(){}
        ~Challenge4(){}

        virtual void SetUp(){}
        virtual void TearDown(){}

        static const string cipher_file;
    };

    //const string Challenge4::cipher_file = "/Users/ben/Coding/Crypto/cryptopals/data/4.txt"; // non-relative on my lappy
    const string Challenge4::cipher_file = "../../../data/4.txt"; // works from build dir with cmake

    TEST_F(Challenge4, decipher_with_rank)
    {
        std::ifstream input_file(Challenge4::cipher_file);
        decode::Result result = util::find_single_char_cipher_in_file(input_file);
        cout << "Best matched line is " << result.file_line
             << " with score of " << result.etaoin_shrdlu_score
             << " and key '" << result.single_char_cipher
             << "' resulting in:" << endl << result.decoded_string << endl;
    }

} // namespace test

} // namespace cryptopals

