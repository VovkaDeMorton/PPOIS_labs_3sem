cmake_minimum_required(VERSION 3.15)
project(lab1_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(lab1_app
    src/main.cpp
    src/TicTacToe.cpp
)

# --- Подключение GoogleTest ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Для Windows: предотвращает переопределение флагов компиляции
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Настройка тестового исполняемого файла ---
enable_testing()

add_executable(lab1_tests
    tests/test_tictactoe.cpp
    src/TicTacToe.cpp  # Подключаем наш класс, чтобы тестировать его
)

# Линкуем GoogleTest
target_link_libraries(lab1_tests GTest::gtest_main)

# --- Включаем сбор покрытия (только для GCC) ---
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab1_tests PRIVATE --coverage)
    target_link_options(lab1_tests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(lab1_tests)