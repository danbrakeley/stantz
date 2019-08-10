# Stantz, Ray (Tracer)

## Overview

I did Peter Shirley's "[Ray Tracing in One Weekend](http://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf)" tutorial, and this repo contains the results.

Here's my final render, which used 500 rays per pixel and a max ray depth of 50 bounces, and took 16 minutes to run across 12 theads on an i7-8700K:

![final render](https://the.real.danbrakeley.com/github/stantz-final.png)

## clang-format

I love Go's built-in code formatting ([gofmt](https://blog.golang.org/go-fmt-your-code)), and I was excited to see that Visual Studio supports per-project C/C++ code formatting via the open [.clang-format](https://clang.llvm.org/docs/ClangFormat.html). I've added a .clang-format to this project that I've customized into something that I find fairly readable.

Unfortunately, VS ships with an older version of clang-format.exe, and I've made use of newer features that cause the older formatter to fail. Luckily, VS is literally calling a copy of clang-format.exe, and that exe can be swapped for a newer build. Here's how I did it:

- Download the [latest LLVM snapshot build](https://llvm.org/builds/) for Windows
- Extract the contents of the downloaded installer (you do not need to run the installer to do this)
  - If you have 7-Zip installed with the shell extension
    - Right-click `LLVM-<version>-win64.exe`
    - Choose the `7-Zip` context menu, then `Extract to "LLVM-<version>-win64\"`
  - Find where Visual Studio has installed `clang-format.exe`
    - For me, it was in `C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\Llvm\8.0.0\bin\`
  - rename original `clang-format.exe` to `clang-format.exe.original`
  - copy the downloaded `clang-format.exe` into this folder

## notes

### Naming

type | style
--- | ---
class names | `CapitalCamelCase`
class member names | `lower_case_trailing_underscore_`
file names | `lower_case.ext`
function names | `lower_case_underscores`
struct names | `lower_case_underscores`
variable names | `lower_case_underscores`
