extern crate cryptopals;

#[test]
fn challenge1_convert_hex_to_base64() {
    let input = String::from(
        "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d",
    );
    let expected = String::from("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
    assert_eq!(cryptopals::base16_to_base64(input), expected);
}

#[test]
fn challenge2_fixed_xor() {
    let input1: String = "1c0111001f010100061a024b53535009181c".into();
    let input2: String = "686974207468652062756c6c277320657965".into();
    let expected: String = "746865206b696420646f6e277420706c6179".into();
    let result = cryptopals::encode_base16(cryptopals::fixed_xor(
        &cryptopals::decode_base16(input1),
        &cryptopals::decode_base16(input2),
    ));
    assert_eq!(result, expected);
}

#[test]
fn challenge3_single_char_xor() {
    let single_byte_ciphered: String =
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736".into();
    let data = cryptopals::decode_base16(single_byte_ciphered);
    let result = cryptopals::find_single_char_cipher(&data);
    let deciphered = cryptopals::decipher_single_char_xor(&data, result);
    let result_string = String::from_utf8(deciphered).unwrap();
    let result: char = result.into();
    println!("Best key is '{}' resulting in: {}", result, result_string);
}
