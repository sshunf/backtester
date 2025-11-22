# Backtester

A high-performance C++ backtesting engine designed for trading strategies, emphasizing high-throughput and low-latency.

## Motivation
After a summer as an intern at Point72, I was inspired to deepen my understanding of financial markets. At the same time, I had become increasingly interested in C++ and wanted a personal project that would push my systems-level skills further. Building a backtester felt like a great way to expose myself to both, forcing me to learn about market microstructure, data modeling, and trading logic while also requiring me to learn good engineering practices, performance considerations, and clean abstractions.

This project is my attempt at trying to make a lightweight, modular, and high-performance backtesting engine written in modern C++23, designed to help me practice low-level programming while gaining intuition for how trading systems operate under the hood.

<!-- Language -->
![C++23](https://img.shields.io/badge/C%2B%2B-23-00599C?logo=c%2B%2B&logoColor=white)

<!-- Build & Tooling -->
![CMake](https://img.shields.io/badge/CMake-3.22+-064F8C?logo=cmake&logoColor=white)
![Taskfile](https://img.shields.io/badge/Taskfile-Automation-28A0F0?logo=task&logoColor=white)
![Conan](https://img.shields.io/badge/Conan-Package%20Manager-3399FF?logo=conan&logoColor=white)

<!-- Quality -->
![Clang-Tidy](https://img.shields.io/badge/Clang--Tidy-Static%20Analysis-yellow?logo=llvm&logoColor=white)
![Clang-Format](https://img.shields.io/badge/Clang--Format-Code%20Style-orange?logo=llvm&logoColor=white)

<!-- Testing -->
![GoogleTest](https://img.shields.io/badge/GoogleTest-Unit%20Tests-34A853?logo=google&logoColor=white)
