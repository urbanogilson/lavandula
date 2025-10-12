#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/include/lavandula_test.h"
#include "../src/include/http.h"
#include "../src/include/auth.h"
#include "../src/include/base64.h"

void testBasicAuthInit() {
    BasicAuthenticator auth = initBasicAuth();
    expect(auth.credentialsCount, toBe(0));
    expect(auth.credentialsCapacity, toBe(1));
    expect(auth.credentials != NULL, toBe(true));
    freeBasicAuth(auth);
}

void testBasicAuthSingleCredential() {
    BasicAuthenticator auth = initBasicAuth();
    addBasicCredentials(&auth, "user1", "pass1");

    char *credentials = base64Encode("user1:pass1");
    expect(checkBasicCredentials(&auth, credentials), toBe(true));
    expect(auth.credentialsCount, toBe(1));
    free(credentials);
    freeBasicAuth(auth);
}

void testBasicAuthMultipleCredentials() {
    BasicAuthenticator auth = initBasicAuth();
    addBasicCredentials(&auth, "user1", "pass1");
    addBasicCredentials(&auth, "admin", "secret");
    addBasicCredentials(&auth, "test", "123");

    char *cred1 = base64Encode("user1:pass1");
    char *cred2 = base64Encode("admin:secret");
    char *cred3 = base64Encode("test:123");

    expect(checkBasicCredentials(&auth, cred1), toBe(true));
    expect(checkBasicCredentials(&auth, cred2), toBe(true));
    expect(checkBasicCredentials(&auth, cred3), toBe(true));
    expect(auth.credentialsCount, toBe(3));

    free(cred1);
    free(cred2);
    free(cred3);
    freeBasicAuth(auth);
}

void testBasicAuthInvalidCredentials() {
    BasicAuthenticator auth = initBasicAuth();
    addBasicCredentials(&auth, "user1", "pass1");

    char *wrongCred = base64Encode("user1:wrongpass");
    char *wrongUser = base64Encode("wronguser:pass1");
    char *notFound = base64Encode("admin:admin");

    expect(checkBasicCredentials(&auth, wrongCred), toBe(false));
    expect(checkBasicCredentials(&auth, wrongUser), toBe(false));
    expect(checkBasicCredentials(&auth, notFound), toBe(false));

    free(wrongCred);
    free(wrongUser);
    free(notFound);
    freeBasicAuth(auth);
}

void testBasicAuthEmptyCredentials() {
    BasicAuthenticator auth = initBasicAuth();
    
    char *emptyCred = base64Encode(":");
    expect(checkBasicCredentials(&auth, emptyCred), toBe(false));
    
    free(emptyCred);
    freeBasicAuth(auth);
}

void testBasicAuthNullInput() {
    BasicAuthenticator auth = initBasicAuth();
    addBasicCredentials(&auth, "user1", "pass1");

    expect(checkBasicCredentials(&auth, NULL), toBe(false));
    
    freeBasicAuth(auth);
}

void testBasicAuthSpecialCharacters() {
    BasicAuthenticator auth = initBasicAuth();
    addBasicCredentials(&auth, "user@domain.com", "p@$$w0rd!");
    addBasicCredentials(&auth, "user with spaces", "pass with spaces");

    char *cred1 = base64Encode("user@domain.com:p@$$w0rd!");
    char *cred2 = base64Encode("user with spaces:pass with spaces");

    expect(checkBasicCredentials(&auth, cred1), toBe(true));
    expect(checkBasicCredentials(&auth, cred2), toBe(true));

    free(cred1);
    free(cred2);
    freeBasicAuth(auth);
}

void testBasicAuthEmptyUsernamePassword() {
    BasicAuthenticator auth = initBasicAuth();
    addBasicCredentials(&auth, "", "password");
    addBasicCredentials(&auth, "username", "");
    addBasicCredentials(&auth, "", "");

    char *cred1 = base64Encode(":password");
    char *cred2 = base64Encode("username:");
    char *cred3 = base64Encode(":");

    expect(checkBasicCredentials(&auth, cred1), toBe(true));
    expect(checkBasicCredentials(&auth, cred2), toBe(true));
    expect(checkBasicCredentials(&auth, cred3), toBe(true));

    free(cred1);
    free(cred2);
    free(cred3);
    freeBasicAuth(auth);
}

void testConstTimeStrcmp() {
    expect(consttimeStrcmp("hello", "hello"), toBe(true));
    expect(consttimeStrcmp("hello", "world"), toBe(false));
    expect(consttimeStrcmp("", ""), toBe(true));
    expect(consttimeStrcmp("a", ""), toBe(false));
    expect(consttimeStrcmp("", "a"), toBe(false));
    expect(consttimeStrcmp("test123", "test124"), toBe(false));
}

void testBasicAuthCaseSensitive() {
    BasicAuthenticator auth = initBasicAuth();
    addBasicCredentials(&auth, "User1", "Pass1");

    char *lowerCase = base64Encode("user1:pass1");
    char *upperCase = base64Encode("USER1:PASS1");
    char *correct = base64Encode("User1:Pass1");

    expect(checkBasicCredentials(&auth, lowerCase), toBe(false));
    expect(checkBasicCredentials(&auth, upperCase), toBe(false));
    expect(checkBasicCredentials(&auth, correct), toBe(true));

    free(lowerCase);
    free(upperCase);
    free(correct);
    freeBasicAuth(auth);
}

void testBasicAuthLongCredentials() {
    BasicAuthenticator auth = initBasicAuth();
    
    char longUser[1000], longPass[1000];
    memset(longUser, 'a', 999);
    longUser[999] = '\0';
    memset(longPass, 'b', 999);
    longPass[999] = '\0';
    
    addBasicCredentials(&auth, longUser, longPass);

    char longCred[2000];
    snprintf(longCred, sizeof(longCred), "%s:%s", longUser, longPass);
    char *encoded = base64Encode(longCred);

    expect(checkBasicCredentials(&auth, encoded), toBe(true));

    free(encoded);
    freeBasicAuth(auth);
}

void testFreeBasicAuthEmpty() {
    BasicAuthenticator auth = initBasicAuth();
    freeBasicAuth(auth);
}

void testFreeBasicAuthWithCredentials() {
    BasicAuthenticator auth = initBasicAuth();
    addBasicCredentials(&auth, "user1", "pass1");
    addBasicCredentials(&auth, "user2", "pass2");
    freeBasicAuth(auth);
}

void runAuthTests() {
    runTest(testBasicAuthInit);
    runTest(testBasicAuthSingleCredential);
    runTest(testBasicAuthMultipleCredentials);
    runTest(testBasicAuthInvalidCredentials);
    runTest(testBasicAuthEmptyCredentials);
    runTest(testBasicAuthNullInput);
    runTest(testBasicAuthSpecialCharacters);
    runTest(testBasicAuthEmptyUsernamePassword);
    runTest(testConstTimeStrcmp);
    runTest(testBasicAuthCaseSensitive);
    runTest(testBasicAuthLongCredentials);
    runTest(testFreeBasicAuthEmpty);
    runTest(testFreeBasicAuthWithCredentials);
}