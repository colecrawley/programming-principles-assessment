[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/HlGqMSF0)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21841326)
# CMP9133 — Distributed Compression/Decompression System 🧩

![Build & Tests](https://github.com/UoL-SoCS/compression-assignment-public/actions/workflows/ci.yml/badge.svg)

This repository is the **starter template** for *Assessment 2* of the module  
**Programming Principles (CMP9133)** at the *University of Lincoln*.

---

## 🎯 Overview

In this assessment, you will design and implement a **distributed file compression/decompression system** in **C++**, demonstrating your ability to write clean, modular and concurrent software.

The system should allow **clients** to send files to a **server** for **compression** or **decompression**, simulating a lightweight distributed data-processing service.  
You are expected to apply concepts from this module including **object-oriented programming**, **multi-threading**, and **network programming**.

---

## 🧠 Learning Outcomes

- **[LO2]** Propose and implement a solution to a typical programming problem.  
  → Demonstrated through your implemented system and code quality.  
- **[LO3]** Critically evaluate different solutions for typical programming problems.  
  → Demonstrated through your written report submitted on Blackboard.

---

## 🧩 Requirements

Your program must:

1. **Implement at least one compression algorithm**, such as Run-Length Encoding (RLE).  
2. **Support decompression** to reconstruct the original file.  
3. Apply **OOP principles**: inheritance, polymorphism, and encapsulation.  
4. Use **multi-threading** or other forms of concurrency to process multiple tasks.  
5. Implement a **client–server model** using TCP sockets for communication.  
6. Be **modular, maintainable**, and **extensible**.

You may extend the baseline code to include additional compression algorithms or architectural improvements for higher marks.

---

## 🧰 Project Structure

```
CMP9133-Compression-System/
├── include/
│   ├── CompressionAlgorithm.h      # Abstract base class
│   ├── RLECompression.h            # Run-Length Encoding definition
│   ├── FileHandler.h               # File input/output helper definition
│   ├── Client.h                    # Client definition
│   ├── Server.h                    # Server definition
├── src/
│   ├── RLECompression.cpp          # Run-Length Encoding declaration
│   ├── FileHandler.cpp             # File input/output helper declaration
│   ├── Server.cpp                  # Server class
│   ├── ServerMain.cpp              # Example server
│   └── Client.cpp                  # Client class
│   └── ClientMain.cpp              # Example client
├── tests/                          # Public Catch2 tests (automatically built)
├── CMakeLists.txt                  # Build configuration
└── .github/workflows/ci.yml        # CI workflow running all tests
```

---

## ⚙️ Build Instructions (CMake)

### 🧩 Configure & Build

```bash
mkdir build && cd build
cmake ..
cmake --build . -j
```

CMake will automatically **fetch Catch2** from GitHub if not already installed.

### ▶️ Run the Example Programs

The repository includes example executables that demonstrate how to use the Server and Client classes:

```bash
./server    # run in one terminal
./client    # run in another terminal
```

**How to use these for debugging:**
- **Manual testing**: Run the server and client to verify your implementations work end-to-end
- **Debugging**: Use a debugger (e.g., `gdb ./server` or VS Code) to step through the code
- **Reference**: Review `src/ServerMain.cpp` and `src/ClientMain.cpp` to see how to instantiate and use the classes
- **Modify**: Feel free to modify these files to test different scenarios or add print statements

These are **example programs only** — you should focus on implementing the core classes correctly to pass the automated tests.

### 🧪 Run the Tests

```bash
ctest --output-on-failure
```

> **Note**: Public tests use randomised input to prevent hard-coded answers.  
> **Do not modify or create your own test files** — only the provided tests will be used for grading.

---

## 🧾 Marking and Automated Tests

This assignment uses **automated grading** via **unit tests** executed by **GitHub Actions**.  
There are two categories of tests:

### 🟢 Public Tests (Visible to Students)
Located in the `tests/` folder.  
They verify:
- Compression/decompression correctness  
- File I/O functionality  
- Networking (single and multi-client echo)  
- Thread safety and multi-threading  
- Handling of edge cases and scalability  

Public tests are run automatically when you **push commits** to GitHub.  
Results are visible in the **Actions** tab of your repository.

### 🔒 Hidden Tests (Private to Staff)
Executed only during final marking.  
They assess:
- Large-scale performance and concurrency  
- Handling of malformed or extreme inputs  
- Resource management and memory safety (RAII)  
- Boundary conditions (e.g., RLE runs > 255)  
- Scalability and stress under multiple concurrent clients  

Hidden tests are stored in a private staff repository and automatically fetched during the internal CI marking pipeline.  
Students cannot access them.

---

## 🧮 Marking Scheme

| Grade Range | Description | Typical Test Coverage |
|--------------|-------------|-----------------------|
| **Fail (<50%)** | Incomplete or non-compiling solution. Few core tests pass. | <10 public tests |
| **Pass (50–59%)** | Basic functionality working; some OOP and network logic implemented. | 10–11 tests |
| **Merit (60–69%)** | Reliable compression/decompression; clear modular structure; multi-threading and client-server working. | 12–14 tests |
| **Distinction (70%+)** | Well-structured, robust, and scalable system with advanced C++ features, excellent design, and full test coverage. | ≥15 total tests (including hidden) |

Each test contributes proportionally to the overall mark.  
Passing **all 20 tests** (10 public + 10 hidden) corresponds to full marks for the coding component (60% of module grade).

---

## 🧩 Tips for Success

✅ Separate **class declarations** (.h) from **definitions** (.cpp).  
✅ Use **inheritance** and **virtual functions** appropriately.  
✅ Keep code **modular and readable**.  
✅ Use **threads** responsibly; avoid race conditions.  
✅ Validate all **I/O** and **network operations**.  
✅ Test your program locally before submission using `ctest`.  
✅ Use the example programs (`./server` and `./client`) to manually test and debug your implementations.  
✅ Add comments and follow consistent naming conventions.  
✅ **Do not modify test files** — focus on implementing the classes correctly.

---

## 🚀 Submission

1. Push your **code** to GitHub Classroom before the deadline.  
2. Submit your **written report** (PDF) via Blackboard — not through GitHub.  
3. Ensure your repository builds correctly from a clean clone.

---

## ⚠️ Academic Integrity

Use of AI tools (e.g. ChatGPT, Copilot) to **generate code or text** is **not permitted** unless explicitly authorised.  
All code must be your own work.  
Plagiarism detection tools and manual code inspection will be used.

---

© *University of Lincoln – School of Engineering and Physical Sciences*  
*CMP9133 Programming Principles — Assessment 2 (2025–26)*
