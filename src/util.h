#pragma once

#include <stdint.h>
#include <string>
#include <vector>

namespace cryptopals {

namespace util {

    std::vector<uint8_t> decode_base16(std::string base16);
    std::vector<uint8_t> decode_base64(std::string base64);
    std::string encode_base64(std::vector<uint8_t> data);
    std::string encode_base16(std::vector<uint8_t> data);
    std::string base16_to_base64(std::string base16);
    std::string base64_to_base16(std::string base64);

} /* util */

} /* cryptopals */
