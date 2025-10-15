# Testing your App

Lavandula provides a built-in testing framework for writing unit tests for your application.

The following example defines a new test that is being run.

```c
void testOne() {
    int x = 10;
    expect(x, toBe(10));
}

runTest(testOne);
testResults();
```

Call `runTest` with a function pointer argument to run a test. Call `testResults` to see the outcome of all of your tests.