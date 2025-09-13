# BUILDING.md

## Prerequisites

Before building the project, ensure you have the following tools installed:

- [go-task](https://taskfile.dev/#/installation) — task runner used to simplify commands
- [CMake](https://cmake.org/download/) ≥ 3.20 — build system generator
- [Conan](https://conan.io/downloads) ≥ 2.0 — C++ package manager
- A modern C++ compiler with **C++23** support
  - macOS: Xcode (AppleClang ≥ 15)
  - Linux: GCC ≥ 14 or Clang ≥ 15
  - Windows: MSVC (Visual Studio 2022) or Clang via WSL

---

## ⚙️ Setup

**Detect Conan Profile**
1. Run once to initialize Conan for your environment:
```bash
conan profile detect
```

2. Ensure your profile supports C++23.
Edit ~/.conan2/profiles/default and set:
```bash
compiler.cppstd=gnu23
```

## Build Instructions

Install dependencies:
```bash
task deps
```

Configure CMake:
```bash
task init
```

Build the project:
```bash
task build
```

Run tests:
```bash
task test
```
