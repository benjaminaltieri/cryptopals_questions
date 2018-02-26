#include "util.h"

using namespace std;

namespace { // module private helpers

    const string hex_map = "0123456789abcdef";

    char nibble_to_char(const uint8_t nibble) {
        if (nibble > 0x0F) {
            throw std::invalid_argument("Nibble value is out of bounds.");
        }
        return hex_map[nibble];
    }

    uint8_t char_to_nibble(const char c) {
        if (c < '0' || '9' < c) {
            if (c < 'a' || 'f' < c) {
                throw std::invalid_argument("Char value is out of bounds.");
            } else {
                return c - 'a' + 0x0A;
            }
        } else {
            return c - '0';
        }
    }

    const string base64_map = \
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    char sextet_to_char(uint8_t sextet) {
        if (sextet > 0x3F) {
            throw std::invalid_argument("Sextet value is out of bounds.");
        }
        return base64_map[sextet];
    }

    string octets_to_string(const uint8_t *octets, const uint8_t valid_octets)
    {
        if (octets == nullptr) {
            throw std::invalid_argument("null pointer passed to octets.");
        }
        if (valid_octets > 3) {
            throw std::invalid_argument("invalid number of octets");
        }
        string encoded_chars;
        if (valid_octets > 0) {
            // Encode and add first term
            uint8_t first_index = 0x3F & ((octets[0] & 0xFC) >> 2);
            encoded_chars += sextet_to_char(first_index);
            // Second term depends on whether second octet is valid
            uint8_t second_index = 0x30 & ((octets[0] & 0x03) << 4);
            if (valid_octets > 1) {
                second_index |= 0x0F & ((octets[1] & 0xF0) >> 4);
            }
            encoded_chars += sextet_to_char(second_index);
            // Here we branch to cover the single octet case
            if (valid_octets == 1) {
                encoded_chars += '=';
            } else {
                // Again this term will change based on having the third octet
                uint8_t third_index = 0x3C & ((octets[1] & 0x0F) << 2);
                if (valid_octets > 2) {
                    third_index |= 0x03 & ((octets[2] & 0xC0) >> 6);
                }
                encoded_chars += sextet_to_char(third_index);
                // Final term is added only if all three octets are valid
                if (valid_octets > 2) {
                    uint8_t fourth_index = 0x3F & octets[2];
                    encoded_chars += sextet_to_char(fourth_index);
                }
            }
            // If two octets or less we will need this additional equal sign
            if (valid_octets < 3) {
                encoded_chars += '=';
            }
        }
        return encoded_chars;
    }

}

namespace cryptopals {

namespace util {

    vector<uint8_t> decode_base16(string base16)
    {
        vector<uint8_t> data;
        if (base16.length() % 2 != 0) {
            throw std::invalid_argument("Hex string with unmatched nibble.");
        }
        for (auto it = base16.begin(); it < base16.end(); it += 2)
        {
            data.push_back((char_to_nibble(*it) << 4)
                           + char_to_nibble(*(it + 1)));
        }
        return data;
    }

    vector<uint8_t> decode_base64(string base64)
    {
        (void)base64;
        return vector<uint8_t>();
    }

    string encode_base64(vector<uint8_t> data)
    {
        string base64;
        for (auto it = data.begin(); it < data.end(); it += 3)
        {
            size_t remaining = data.end() - it;
            uint8_t valid = remaining < 3 ? remaining % 3 : 3;
            base64 += octets_to_string(&(*it), valid);
        }
        return base64;
    }

    string encode_base16(vector<uint8_t> data)
    {
        string base16;
        for (uint8_t byte : data)
        {
            char lower_nibble = nibble_to_char(byte & 0x0F);
            char upper_nibble = nibble_to_char((byte & 0xF0) >> 4);
            base16 += upper_nibble;
            base16 += lower_nibble;
        }
        return base16;
    }

    string base16_to_base64(string base16) {
        return encode_base64(decode_base16(base16));
    }

    string base64_to_base16(string base64) {
        return encode_base16(decode_base64(base64));
    }

    vector<uint8_t> fixed_xor(vector<uint8_t> data_a, vector<uint8_t> data_b)
    {
        if (data_a.size() != data_b.size()) {
            throw std::invalid_argument("Mismatched vector length inputs");
        }
        vector<uint8_t> xored;
        for (size_t i = 0; i < data_a.size(); i++) {
            xored.push_back(data_a[i] ^ data_b[i]);
        }
        return xored;
    }

} /* util */

} /* cryptopals */
