cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(check_tests)

add_executable(test_check src/check_tests.c)

# Link Check library
find_package(Check REQUIRED)
target_link_libraries(test_check PRIVATE Check::Check)
