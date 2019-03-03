#pragma once

#include <stdint.h>
#include <limits>
#include <string>
#include <vector>
#include <fstream>

namespace cryptopals {

namespace decode {

    typedef struct {
        std::string decoded_string = "";
        size_t file_line = 0;
        char single_char_cipher = '\0';
        int64_t etaoin_shrdlu_score = std::numeric_limits<int64_t>::min();
    } Result;

} /* decode */

namespace util {

    std::vector<uint8_t> decode_base16(std::string base16);
    std::vector<uint8_t> decode_base64(std::string base64);
    std::string encode_base64(std::vector<uint8_t> data);
    std::string encode_base16(std::vector<uint8_t> data);
    std::string base16_to_base64(std::string base16);
    std::string base64_to_base16(std::string base64);
    std::vector<uint8_t> fixed_xor(std::vector<uint8_t> data_a, std::vector<uint8_t> data_b);
    int64_t score_etaoin_shrdlu(std::vector<uint8_t> data);
    std::vector<uint8_t> decipher_single_char_xor(std::vector<uint8_t> data, uint8_t key);
    uint8_t find_single_char_cipher(std::vector<uint8_t> data);
    decode::Result find_single_char_cipher_in_file(std::ifstream &input_file);

} /* util */

} /* cryptopals */
