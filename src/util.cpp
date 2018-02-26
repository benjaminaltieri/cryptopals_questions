#include <assert.h>

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

    int32_t get_etaoin_shrdlu_score(uint8_t value)
    {
        static bool built_yet = false;
        static vector<int32_t> etaoin_shrdlu_score_book;
        if (!built_yet) {
            // Build scorebook
            vector<int32_t> below_bounds_indices(0x20, -10);
            vector<int32_t> lettered_indices(0x60, 0);
            vector<int32_t> above_bounds_indices(0x80, -10);
            etaoin_shrdlu_score_book.reserve(below_bounds_indices.size()
                                             + lettered_indices.size()
                                             + above_bounds_indices.size());
            etaoin_shrdlu_score_book.insert(etaoin_shrdlu_score_book.end(),
                                            below_bounds_indices.begin(),
                                            below_bounds_indices.end());
            etaoin_shrdlu_score_book.insert(etaoin_shrdlu_score_book.end(),
                                            lettered_indices.begin(),
                                            lettered_indices.end());
            etaoin_shrdlu_score_book.insert(etaoin_shrdlu_score_book.end(),
                                            above_bounds_indices.begin(),
                                            above_bounds_indices.end());
            assert(etaoin_shrdlu_score_book.size() == 0x100);
            etaoin_shrdlu_score_book[0x7F] = -10;
            etaoin_shrdlu_score_book['e'] = 10;
            etaoin_shrdlu_score_book['t'] = 10;
            etaoin_shrdlu_score_book['a'] = 10;
            etaoin_shrdlu_score_book['o'] = 10;
            etaoin_shrdlu_score_book['i'] = 10;
            etaoin_shrdlu_score_book['n'] = 10;
            etaoin_shrdlu_score_book[' '] = 10;
            etaoin_shrdlu_score_book['s'] = 10;
            etaoin_shrdlu_score_book['h'] = 10;
            etaoin_shrdlu_score_book['r'] = 10;
            etaoin_shrdlu_score_book['d'] = 10;
            etaoin_shrdlu_score_book['l'] = 10;
            etaoin_shrdlu_score_book['u'] = 10;
            etaoin_shrdlu_score_book['E'] = 10;
            etaoin_shrdlu_score_book['T'] = 10;
            etaoin_shrdlu_score_book['A'] = 10;
            etaoin_shrdlu_score_book['O'] = 10;
            etaoin_shrdlu_score_book['I'] = 10;
            etaoin_shrdlu_score_book['N'] = 10;
            etaoin_shrdlu_score_book['S'] = 10;
            etaoin_shrdlu_score_book['H'] = 10;
            etaoin_shrdlu_score_book['R'] = 10;
            etaoin_shrdlu_score_book['D'] = 10;
            etaoin_shrdlu_score_book['L'] = 10;
            etaoin_shrdlu_score_book['U'] = 10;
            built_yet = true;
        }
        return etaoin_shrdlu_score_book[value];
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

    int64_t score_etaoin_shrdlu(vector<uint8_t> data)
    {
        int64_t score = 0;
        for (const uint8_t& datum : data)
        {
            score += get_etaoin_shrdlu_score(datum);
        }
        return score;
    }

} /* util */

} /* cryptopals */
