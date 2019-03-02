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

    const string Challenge4::cipher_file = "../data/4.txt";

    TEST_F(Challenge4, decipher_with_rank)
    {
#if 0
        int handle = fopen(Challenge4::cipher_file, 'r');
        vector<uint8_t> data = util::decode_base16(Challenge4::cipher_file);
		uint8_t result = util::find_single_char_cipher(data);
		vector<uint8_t> deciphered = util::decipher_single_char_xor(data, result);
		string result_string = string(deciphered.begin(), deciphered.end());
        cout << "Best key is '" << result << "' resulting in:" << endl << result_string << endl;
#endif
    }

} // namespace test

} // namespace cryptopals

