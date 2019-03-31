extern crate hex;
extern crate cryptopals;

use std::fs::File;
use std::io::prelude::*;

#[test]
fn challenge1_convert_hex_to_base64() {
    let input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    let expected = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    assert_eq!(cryptopals::base16_to_base64(input), expected);
}

#[test]
fn challenge2_fixed_xor() {
    let input1 = "1c0111001f010100061a024b53535009181c";
    let input2 = "686974207468652062756c6c277320657965";
    let expected = "746865206b696420646f6e277420706c6179";
    let result = hex::encode(&cryptopals::fixed_xor(
        &hex::decode(input1).unwrap(),
        &hex::decode(input2).unwrap(),
    ));
    assert_eq!(result, expected);
}

#[test]
fn challenge3_single_char_xor() {
    let single_byte_ciphered = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    let data = hex::decode(single_byte_ciphered).unwrap();
    let result = cryptopals::find_single_char_cipher(&data);
    match result.decoded {
        Some(decoded) => {
            println!("Best key is '{}' resulting in: {}", result.cipher as char, decoded);
        }
        None => {
            println!("No valid decoding found. Best char: {}, Best score: {}", result.cipher as char, result.score);
        }
    }
}

#[test]
fn challenge4_detect_single_char_xor() {
    let data_file_path = "../data/4.txt";

    let mut f = File::open(data_file_path).expect("file not found");

    let mut contents = String::new();
    f.read_to_string(&mut contents)
        .expect("something went wrong reading the file");

    let result = cryptopals::find_single_char_xor_in_lines(&contents);
    match result.decoded {
        Some(decoded) => {
            println!("Final key is '{}' resulting in: {}", result.cipher as char, decoded);
        }
        None => {
            println!("No valid decoding found. Best char: {}, Best score: {}", result.cipher as char, result.score);
        }
    }
}

#[test]
fn challenge5_repeating_xor() {
    let key = "ICE";
    let stanza = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    let expected = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    let result = hex::encode(cryptopals::repeating_xor(key.as_bytes(), stanza.as_bytes()));
    assert_eq!(result, expected);
}

