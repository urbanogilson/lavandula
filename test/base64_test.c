#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../src/include/lavandula_test.h"
#include "../src/include/base64.h"

// RFC 4648 - Test Vectors
// https://www.ietf.org/archive/id/draft-josefsson-rfc4648bis-01.html#name-test-vectors

void testBase64EncodeEmpty() {
    char *encoded = base64Encode("");
    expect(strcmp(encoded, ""), toBe(0));
    free(encoded);
}

void testBase64EncodeSingleChar() {
    char *encoded = base64Encode("f");
    expect(strcmp(encoded, "Zg=="), toBe(0));
    free(encoded);
}

void testBase64EncodeTwoChars() {
    char *encoded = base64Encode("fo");
    expect(strcmp(encoded, "Zm8="), toBe(0));
    free(encoded);
}

void testBase64EncodeThreeChars() {
    char *encoded = base64Encode("foo");
    expect(strcmp(encoded, "Zm9v"), toBe(0));
    free(encoded);
}

void testBase64EncodeFourChars() {
    char *encoded = base64Encode("foob");
    expect(strcmp(encoded, "Zm9vYg=="), toBe(0));
    free(encoded);
}

void testBase64EncodeFiveChars() {
    char *encoded = base64Encode("fooba");
    expect(strcmp(encoded, "Zm9vYmE="), toBe(0));
    free(encoded);
}

void testBase64EncodeSixChars() {
    char *encoded = base64Encode("foobar");
    expect(strcmp(encoded, "Zm9vYmFy"), toBe(0));
    free(encoded);
}

void testBase64EncodePaddingOne() {
    // Input length % 3 == 2, should have one '=' padding
    char *encoded = base64Encode("ab");
    expect(strcmp(encoded, "YWI="), toBe(0));
    expect(encoded[3], toBe('='));
    expectNot(encoded[2], toBe('='));
    free(encoded);
}

void testBase64EncodePaddingTwo() {
    // Input length % 3 == 1, should have two '==' padding
    char *encoded = base64Encode("a");
    expect(strcmp(encoded, "YQ=="), toBe(0));
    expect(encoded[2], toBe('='));
    expect(encoded[3], toBe('='));
    free(encoded);
}

void testBase64EncodeNoPadding() {
    // Input length % 3 == 0, should have no padding
    char *encoded = base64Encode("abc");
    expect(strcmp(encoded, "YWJj"), toBe(0));
    expectNot(encoded[3], toBe('='));
    free(encoded);
}

void testBase64EncodeAlphabet() {
    char *encoded = base64Encode("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    expect(strcmp(encoded, "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVo="), toBe(0));
    free(encoded);
}

void testBase64EncodeNumbers() {
    char *encoded = base64Encode("0123456789");
    expect(strcmp(encoded, "MDEyMzQ1Njc4OQ=="), toBe(0));
    free(encoded);
}

void testBase64EncodeSpecialChars() {
    char *encoded = base64Encode("Hello, World!");
    expect(strcmp(encoded, "SGVsbG8sIFdvcmxkIQ=="), toBe(0));
    free(encoded);
}

void testBase64EncodeSymbols() {
    char *encoded = base64Encode("!@#$%^&*()");
    expect(strcmp(encoded, "IUAjJCVeJiooKQ=="), toBe(0));
    free(encoded);
}

void testBase64EncodeLongString() {
    char *encoded = base64Encode("The quick brown fox jumps over the lazy dog");
    expect(strcmp(encoded, "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="), toBe(0));
    free(encoded);
}

void testBase64EncodeSentence() {
    char *encoded = base64Encode("Obviously, the person who had most influence on my career was Ken Thompson. Unix was basically his, likewise C's predecessor, likewise much of the basis of Plan 9 (though Rob Pike was the real force in getting it together). And in the meantime Ken created the first computer chess master and pretty much rewrote the book on chess endgames. He is quite a phenomenon.");
    expectNotNull(encoded);
    expect(strlen(encoded) > 0, toBe(true));
    free(encoded);
}

// Decoding tests - RFC 4648 Test Vectors
void testBase64DecodeEmpty() {
    char *decoded = base64Decode("");
    expect(strcmp(decoded, ""), toBe(0));
    free(decoded);
}

void testBase64DecodeSingleChar() {
    char *decoded = base64Decode("Zg==");
    expect(strcmp(decoded, "f"), toBe(0));
    free(decoded);
}

void testBase64DecodeTwoChars() {
    char *decoded = base64Decode("Zm8=");
    expect(strcmp(decoded, "fo"), toBe(0));
    free(decoded);
}

void testBase64DecodeThreeChars() {
    char *decoded = base64Decode("Zm9v");
    expect(strcmp(decoded, "foo"), toBe(0));
    free(decoded);
}

void testBase64DecodeFourChars() {
    char *decoded = base64Decode("Zm9vYg==");
    expect(strcmp(decoded, "foob"), toBe(0));
    free(decoded);
}

void testBase64DecodeFiveChars() {
    char *decoded = base64Decode("Zm9vYmE=");
    expect(strcmp(decoded, "fooba"), toBe(0));
    free(decoded);
}

void testBase64DecodeSixChars() {
    char *decoded = base64Decode("Zm9vYmFy");
    expect(strcmp(decoded, "foobar"), toBe(0));
    free(decoded);
}

void testBase64DecodeWithPadding() {
    char *decoded = base64Decode("SGVsbG8sIFdvcmxkIQ==");
    expect(strcmp(decoded, "Hello, World!"), toBe(0));
    free(decoded);
}

void testBase64DecodeNoPadding() {
    char *decoded = base64Decode("YWJj");
    expect(strcmp(decoded, "abc"), toBe(0));
    free(decoded);
}

void testBase64RoundTripSimple() {
    char *original = "Hello";
    char *encoded = base64Encode(original);
    char *decoded = base64Decode(encoded);

    expect(strcmp(decoded, original), toBe(0));

    free(encoded);
    free(decoded);
}

void testBase64RoundTripLong() {
    char *original = "The C Programming Language by Kernighan and Ritchie";
    char *encoded = base64Encode(original);
    char *decoded = base64Decode(encoded);

    expect(strcmp(decoded, original), toBe(0));

    free(encoded);
    free(decoded);
}

void testBase64RoundTripSpecialChars() {
    char *original = "Special: !@#$%^&*()_+-=[]{}|;':\",./<>?";
    char *encoded = base64Encode(original);
    char *decoded = base64Decode(encoded);

    expect(strcmp(decoded, original), toBe(0));

    free(encoded);
    free(decoded);
}

void testBase64RoundTripPaddingOne() {
    char *original = "ab";
    char *encoded = base64Encode(original);
    char *decoded = base64Decode(encoded);

    expect(strcmp(decoded, original), toBe(0));

    free(encoded);
    free(decoded);
}

void testBase64RoundTripPaddingTwo() {
    char *original = "a";
    char *encoded = base64Encode(original);
    char *decoded = base64Decode(encoded);

    expect(strcmp(decoded, original), toBe(0));

    free(encoded);
    free(decoded);
}

void testBase64RoundTripNoPadding() {
    char *original = "abc";
    char *encoded = base64Encode(original);
    char *decoded = base64Decode(encoded);

    expect(strcmp(decoded, original), toBe(0));

    free(encoded);
    free(decoded);
}

void testBase64EncodeSpaces() {
    char *encoded = base64Encode("   ");
    expect(strcmp(encoded, "ICAg"), toBe(0));
    free(encoded);
}

void testBase64EncodeNewlines() {
    char *encoded = base64Encode("line1\nline2");
    expectNotNull(encoded);
    expect(strlen(encoded) > 0, toBe(true));
    free(encoded);
}

void testBase64EncodeTab() {
    char *encoded = base64Encode("a\tb");
    expectNotNull(encoded);
    expect(strlen(encoded) > 0, toBe(true));
    free(encoded);
}

void testBase64EncodeNullTerminated() {
    char *encoded = base64Encode("test");
    expect(encoded[strlen(encoded)], toBe('\0'));
    free(encoded);
}

void testBase64DecodeNullTerminated() {
    char *decoded = base64Decode("dGVzdA==");
    expect(decoded[strlen(decoded)], toBe('\0'));
    free(decoded);
}

void runBase64Tests(){
    // Basic encoding tests
    runTest(testBase64EncodeEmpty);
    runTest(testBase64EncodeSingleChar);
    runTest(testBase64EncodeTwoChars);
    runTest(testBase64EncodeThreeChars);
    runTest(testBase64EncodeFourChars);
    runTest(testBase64EncodeFiveChars);
    runTest(testBase64EncodeSixChars);

    // Padding tests
    runTest(testBase64EncodePaddingOne);
    runTest(testBase64EncodePaddingTwo);
    runTest(testBase64EncodeNoPadding);

    // Content type tests
    runTest(testBase64EncodeAlphabet);
    runTest(testBase64EncodeNumbers);
    runTest(testBase64EncodeSpecialChars);
    runTest(testBase64EncodeSymbols);
    runTest(testBase64EncodeLongString);
    runTest(testBase64EncodeSentence);

    // Decoding tests
    runTest(testBase64DecodeEmpty);
    runTest(testBase64DecodeSingleChar);
    runTest(testBase64DecodeTwoChars);
    runTest(testBase64DecodeThreeChars);
    runTest(testBase64DecodeFourChars);
    runTest(testBase64DecodeFiveChars);
    runTest(testBase64DecodeSixChars);
    runTest(testBase64DecodeWithPadding);
    runTest(testBase64DecodeNoPadding);

    // Round-trip tests
    runTest(testBase64RoundTripSimple);
    runTest(testBase64RoundTripLong);
    runTest(testBase64RoundTripSpecialChars);
    runTest(testBase64RoundTripPaddingOne);
    runTest(testBase64RoundTripPaddingTwo);
    runTest(testBase64RoundTripNoPadding);

    // Edge cases
    runTest(testBase64EncodeSpaces);
    runTest(testBase64EncodeNewlines);
    runTest(testBase64EncodeTab);
    runTest(testBase64EncodeNullTerminated);
    runTest(testBase64DecodeNullTerminated);
}