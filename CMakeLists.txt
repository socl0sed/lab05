cmake_minimum_required(VERSION 3.5)
project(BankingApp)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TESTS "Build tests" OFF)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/banking)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)

# Add source files to the library
add_library(BankingLib STATIC
    ${SOURCE_DIR}/Account.cpp
    ${SOURCE_DIR}/Transaction.cpp
)

# Include directories for the library
target_include_directories(BankingLib PUBLIC ${SOURCE_DIR})

# Add tests if BUILD_TESTS is enabled
# Add tests if BUILD_TESTS is enabled
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(${THIRD_PARTY_DIR}/gtest)

    # Specify the test source file
    set(TEST_SOURCES ${TEST_DIR}/Account_test.cpp)

    # Create the test executable
    add_executable(ProtoBank ${TEST_SOURCES})

    # Link the test executable with gtest and BankingLib
    target_link_libraries(ProtoBank gtest gtest_main BankingLib)

    # Include the header files from the banking directory
    include_directories(${SOURCE_DIR})

    # Add the test to the build
    add_test(NAME ProtoBank COMMAND ProtoBank)

    # Disable the warning for the gtest-death-test.cc file
    target_compile_options(gtest PRIVATE -Wno-error=maybe-uninitialized)
    target_compile_options(gtest_main PRIVATE -Wno-error=maybe-uninitialized)
endif()
