# README: Building C++ Projects with CMake

## Introduction to CMake

**For more about CMake, see:**
[📖 Official Documentation](https://cmake.org/documentation/)

CMake is a **cross-platform build system generator**.  
It allows you to write build instructions once (in `CMakeLists.txt`) and generate platform-specific build files (like Makefiles, Ninja builds, or Visual Studio solutions).

---

## Basic Structure of a CMake Project

Every CMake project needs a `CMakeLists.txt` file. A minimal example:

```cmake
cmake_minimum_required(VERSION 3.15)
project(MyProject VERSION 1.0 LANGUAGES CXX)

add_executable(MyApp main.cpp)
```

Steps to build:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Common CMake Commands

Here are the most commonly used commands when building C++ projects with CMake:

- **Project setup**
  ```cmake
  cmake_minimum_required(VERSION 3.15)
  project(MyProject VERSION 1.0 LANGUAGES CXX)
  ```

- **Executable**
  ```cmake
  add_executable(MyApp main.cpp other.cpp)
  ```

- **Library**
  ```cmake
  add_library(MyLib STATIC lib.cpp)
  target_include_directories(MyLib PUBLIC include)
  ```

- **Linking**
  ```cmake
  target_link_libraries(MyApp PRIVATE MyLib)
  ```

- **C++ standard**
  ```cmake
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
  ```

- **Options**
  ```cmake
  option(ENABLE_LOGGING "Enable logging feature" ON)
  ```

- **Installation**
  ```cmake
  install(TARGETS MyApp DESTINATION bin)
  install(FILES config.h DESTINATION include)
  ```

- **Tests**
  ```cmake
  enable_testing()
  add_test(NAME MyTest COMMAND MyApp)
  ```

- **FetchContent (Dependency Management)**
  ```cmake
  include(FetchContent)
  FetchContent_Declare(
    mylib
    GIT_REPOSITORY https://github.com/example/mylib.git
    GIT_TAG v1.0.0
  )
  FetchContent_MakeAvailable(mylib)
  ```
  Downloads and makes available external dependencies (such as libraries or test frameworks) directly from a Git repository at configure time.  
  This is the **modern alternative** to manually downloading libraries or using submodules.  

---

## CMake Templates Repository

For practical starting points and real-world templates, see:  
[📂 **CMake Templates Repository**](https://github.com/semerdzhiev/cmake-templates)

---

## Types of Testing

When building C++ projects, testing can take different forms depending on the **scope** and **style**.  
Here are the most important categories to understand:

### 1. Unit Testing
- **Definition:** Tests the smallest pieces of code (functions, classes).  
- **Goal:** Verify that each unit works correctly in isolation.  
- **Example:** Check that a sorting function correctly sorts a small list.

### 2. Integration Testing
- **Definition:** Tests how multiple modules work together.  
- **Goal:** Ensure combined parts function as expected.  
- **Example:** Testing a database module together with a user authentication module.

### 3. System Testing
- **Definition:** Tests the complete application end-to-end.  
- **Goal:** Validate that the whole system meets the requirements.  
- **Example:** Launching a compiled program and checking its input/output behavior.

### 4. Regression Testing
- **Definition:** Tests to ensure previously fixed bugs don’t reappear.  
- **Goal:** Prevent accidental reintroduction of old issues.  
- **Example:** Re-running test cases after a bug fix.

### 5. Behavior-Driven Development (BDD) Testing
- **Definition:** A style of testing where test cases are written in terms of system behavior, often in plain English or domain-specific language.  
- **Goal:** Improve communication between developers, testers, and non-technical stakeholders.  
- **Example:**  
  ```text
  Given a user is logged in
  When they click "Logout"
  Then they should be redirected to the login page
  ```

### 6. Test-Driven Development (TDD)
- **Definition:** Write tests *before* writing the code, then implement the minimum functionality to pass the test.  
- **Cycle:** **Red → Green → Refactor**.  
- **Goal:** Ensure code correctness and maintainability.  

### 7. Performance and Stress Testing
- **Definition:** Test how the system behaves under heavy load or high input size.  
- **Goal:** Measure speed, scalability, and stability.  
- **Example:** Benchmarking algorithm execution on inputs of size \( 10^6 \).

---

## Test Frameworks in C++

Two popular libraries for implementing these testing strategies with CMake:

- **Catch2**  
  - Great for **unit tests** and **BDD-style tests**.  
  - Documentation: https://github.com/catchorg/Catch2  

- **GoogleTest (gtest)**  
  - Great for **unit tests**, **integration tests**, and **TDD workflows**.  
  - Documentation: https://github.com/google/googletest  

Both frameworks can be integrated with **CTest** in CMake to automatically discover and run tests.

---


### Catch2

**Catch2** is a modern, header-only unit testing framework.  
It integrates easily with CMake.

**Setup Example:**
```cmake
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(catch2)

add_executable(tests test_main.cpp test_math.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)
```

📖 Documentation:  
https://github.com/catchorg/Catch2

---

### GoogleTest (gtest)

**GoogleTest (gtest)** is one of the most widely used C++ test frameworks.  
It supports advanced features like mocking, parameterized tests, and death tests.

**Setup Example:**
```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.13.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests test_main.cpp test_math.cpp)
target_link_libraries(tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
```

📖 Documentation:  
https://github.com/google/googletest
 
