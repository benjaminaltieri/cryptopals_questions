extern crate hex;

use std::collections::HashMap;
use std::vec::Vec;

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

const SCORING_CHAR_SET: &str = "etaoin shrdluETAOINSHRDLU";

pub fn get_etaoin_shrdlu_score(to_score: char) -> i64 {
    let scoring_chars = String::from(SCORING_CHAR_SET);
    match scoring_chars.find(to_score) {
        Some(_) => 10,
        None => {
            if to_score.is_ascii_graphic() {
                //0x20..0x80
                0
            } else {
                -10
            }
        }
    }
}

pub fn encode_base64(data: &[u8]) -> String {
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

pub fn base16_to_base64(base16: &str) -> String {
    encode_base64(&hex::decode(base16).unwrap())
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

pub fn score_etaoin_shrdlu(data: &[u8]) -> i64 {
    let mut score: i64 = 0;
    for datum in data {
        score += get_etaoin_shrdlu_score((*datum).into());
    }
    score
}

pub fn decipher_single_char_xor(data: &[u8], key: u8) -> Vec<u8> {
    let cipher_vector = vec![key; data.len()];
    //iter::repeat(0).take(size).collect()
    fixed_xor(data, &cipher_vector)
}

pub fn find_single_char_cipher(data: &[u8]) -> u8 {
    let mut best_key: u8 = 0;
    let mut max_score: i64 = i64::min_value();
    for trial_key in 0..u8::max_value() {
        let trial = decipher_single_char_xor(data, trial_key);
        let current_score: i64 = score_etaoin_shrdlu(&trial);
        if max_score < current_score {
            max_score = current_score;
            best_key = trial_key;
        }
    }
    best_key
}

/*
#[cfg(test)]
mod tests {
    use super::*;

}
*/
