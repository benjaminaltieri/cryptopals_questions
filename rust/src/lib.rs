use std::collections::HashMap;
use std::vec::Vec;

pub fn nibble_to_char(nibble: u8) -> char {
    let index: usize = nibble as usize;
    let hex_chars = String::from("0123456789abcdef");
    let hex_map: HashMap<usize, char> = hex_chars.char_indices().collect();
    *hex_map.get(&index).expect("Nibble value is out of bounds.")
}

pub fn char_to_nibble(c: char) -> u8 {
    c.to_digit(16).expect("Char value is out of bounds.") as u8
}

/// Decode a hex string into a vector of bytes
///
/// ```rust
/// # use cryptopals::*;
/// assert_eq!(decode_base16("0A11fe".into()), vec![0x0A, 0x11, 0xFE]);
/// ```
///
pub fn decode_base16(base16: String) -> Vec<u8> {
    if base16.len() % 2 != 0 {
        panic!("Hex string with unmatched nibble.");
    }
    let mut data: Vec<u8> = Vec::new();
    let mut it = base16.chars();
    while let Some(c) = it.next() {
        let upper = char_to_nibble(c);
        let c = it.next().expect("Really unexpected unmatched!");
        let lower = char_to_nibble(c);
        data.push((upper << 4) + lower);
    }
    data
}

pub fn encode_base16(data: Vec<u8>) -> String {
    let mut base16 = String::new();
    for datum in data {
        base16.push_str(&format!("{:x}", datum));
    }
    base16
}

const BASE64_CHAR_SET: &str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

fn sextet_to_char(sextet: u8) -> char {
    let index: usize = sextet as usize;
    let hex_map: HashMap<usize, char> = BASE64_CHAR_SET.char_indices().collect();
    *hex_map.get(&index).expect("Sextet value is out of bounds.")
}

fn octets_to_string(octets: &[u8]) -> String {
    let valid_octets = octets.len();
    if valid_octets > 3 {
        panic!("invalid number of octets");
    }
    let mut encoded_chars = String::new();
    if valid_octets > 0 {
        // Encode and add first term
        let first_index = 0x3F & ((octets[0] & 0xFC) >> 2);
        encoded_chars.push(sextet_to_char(first_index));
        // Second term depends on whether second octet is valid
        let mut second_index = 0x30 & ((octets[0] & 0x03) << 4);
        if valid_octets > 1 {
            second_index |= 0x0F & ((octets[1] & 0xF0) >> 4);
        }
        encoded_chars.push(sextet_to_char(second_index));
        // Here we branch to cover the single octet case
        if valid_octets == 1 {
            encoded_chars.push('=');
        } else {
            // Again this term will change based on having the third octet
            let mut third_index = 0x3C & ((octets[1] & 0x0F) << 2);
            if valid_octets > 2 {
                third_index |= 0x03 & ((octets[2] & 0xC0) >> 6);
            }
            encoded_chars.push(sextet_to_char(third_index));
            // Final term is added only if all three octets are valid
            if valid_octets > 2 {
                let fourth_index = 0x3F & octets[2];
                encoded_chars.push(sextet_to_char(fourth_index));
            }
        }
        // If two octets or less we will need this additional equal sign
        if valid_octets < 3 {
            encoded_chars.push('=');
        }
    }
    encoded_chars
}

pub fn encode_base64(data: Vec<u8>) -> String {
    let mut base64: String = String::new();
    let mut it = data.iter();
    let mut octet_set: Vec<u8> = Vec::with_capacity(3);
    loop {
        match it.next() {
            Some(c) => octet_set.push(*c),
            None => {
                if !octet_set.is_empty() {
                    base64.push_str(&octets_to_string(&octet_set));
                }
                break;
            }
        };
        if octet_set.len() == 3 {
            base64.push_str(&octets_to_string(&octet_set));
            octet_set.clear();
        }
    }
    base64
}

pub fn base16_to_base64(base16: String) -> String {
    encode_base64(decode_base16(base16))
}

pub fn fixed_xor(data_a: &[u8], data_b: &[u8]) -> Vec<u8> {
    if data_a.len() != data_b.len() {
        panic!("Mismatched vector length inputs");
    }
    let mut xored: Vec<u8> = Vec::new();
    for (datum1, datum2) in data_a.iter().zip(data_b) {
        xored.push(datum1 ^ datum2);
    }
    xored
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_codec() {
        assert_eq!(nibble_to_char(0x00), '0');
        assert_eq!(nibble_to_char(0x05), '5');
        assert_eq!(nibble_to_char(0x0A), 'a');
        assert_eq!(char_to_nibble('0'), 0x00);
        assert_eq!(char_to_nibble('5'), 0x05);
        assert_eq!(char_to_nibble('a'), 0x0A);
        assert_eq!(char_to_nibble('A'), 0x0A);
        assert_eq!(decode_base16(String::from("0A11fe")), vec![10, 17, 254]);
        assert_eq!(decode_base16(String::from("")), vec![]);
        assert_eq!(
            decode_base16(String::from("FF00ff00")),
            vec![255, 0, 255, 0]
        );
    }

    #[test]
    #[should_panic]
    fn test_codec_bad_hex_string() {
        decode_base16(String::from("01234"));
    }

}
