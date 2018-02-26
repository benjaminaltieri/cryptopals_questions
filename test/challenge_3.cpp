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
        uint8_t best_key = 0;
        int64_t max_score = -1e6;
        vector<uint8_t> data = util::decode_base16(Challenge3::single_byte_ciphered);
        for (uint8_t trial_key = 0; trial_key <= 0x7F; trial_key++)
        {
            vector<uint8_t> trial_vector(data.size(), trial_key);
            vector<uint8_t> output = util::fixed_xor(data, trial_vector);
            int64_t current_score = util::score_etaoin_shrdlu(output);
            if (max_score < current_score) {
                max_score = current_score;
                best_key = trial_key;
                cout << "New top key '" << best_key << "': " << max_score << endl;
                string result = string(output.begin(), output.end());
                cout << result << endl;
            }
        }
        cout << "Best key with a score of " << max_score << " is '" << best_key << "'" << endl;
    }

} // namespace test

} // namespace cryptopals

