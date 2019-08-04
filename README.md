# Stantz, Ray (Tracer)

## clang-format versions

The version of clang-format used by Visual Studio appears to be v6 for 2017, and v8 for 2019. To get the latest features of clang-format, you'll need to update the version of the exe you are using:

- Download the [latest LLVM snapshot build](https://llvm.org/builds/) for Windows
- Extract the contents of the downloaded installer (you do not need to run the installer to do this)
  - If you have 7-Zip installed with the shell extension
    - Right-click `LLVM-<version>-win64.exe`
    - Choose the `7-Zip` context menu, then `Extract to "LLVM-<version>-win64\"`
    - Find where Visual Studio has installed `clang-format.exe`
      - For me, it was in `C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\Llvm\8.0.0\bin\`
    - rename original `clang-format.exe` to `clang-format.exe.original`
    - copy `clang-format.exe` from the extract `LLVM-<version>-win64\bin` folder into the VS folder

## notes

### Naming

- class names: `CapitalCamelCase`
- file names: `lower_case.ext`
- function names: `lower_case_underscores`
- struct names: `lower_case_underscores`
- variable names: `lower_case_underscores`

### Googletest

Test Fixture class allows resources to be shared across Test Suites.

Historically, Googletest used `Test Case` to mean test suite. They are now transitioning their naming to the latter.

A `Test` is a basic test case.

- Assertions
  - `ASSERT_*` fails immediately
  - `EXPECT_*` fails later, allowing more tests to run before displaying output
  - add messages by streaming them into the ASSERT() macro
    - `ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";`
  - macros include
    - `_TRUE`, `_FALSE`
    - `_EQ`, `_NE`
    - `_LT`, `_LE`, `_GT`, `_GE`
  - arguments evaluated only once, but order is undefined
  - `_EQ` does pointer equality, even on `char*`
  - C strings: `_STREQ`, `_STRNE`, `_STRCASEEQ`, `_STREQCASENE`
    - `CASE` means "ignore case"
    - `nullptr` and empty string are different
- Test
  - `TEST(<suite-name>, <test-name>)`
  - names must be valid C++ identifiers, and they should not contain underscores

```c
// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(Factorial(0), 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(Factorial(1), 1);
  EXPECT_EQ(Factorial(2), 2);
  EXPECT_EQ(Factorial(3), 6);
  EXPECT_EQ(Factorial(8), 40320);
}
```
