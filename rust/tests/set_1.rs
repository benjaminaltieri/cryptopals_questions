extern crate hex;
extern crate cryptopals;

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
    let deciphered = cryptopals::decipher_single_char_xor(&data, result);
    let result_string = String::from_utf8(deciphered).unwrap();
    let result: char = result.into();
    println!("Best key is '{}' resulting in: {}", result, result_string);
}
