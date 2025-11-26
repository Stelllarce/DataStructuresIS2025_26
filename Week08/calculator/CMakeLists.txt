cmake_minimum_required(VERSION 3.14)

project(CalculatorTests)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests.cpp CalcDriver.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
