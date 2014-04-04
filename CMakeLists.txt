cmake_minimum_required (VERSION 2.6)
project (assembly-stats)

set (CMAKE_CXX_FLAGS "-Wall -O3")

file(COPY test_files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runUnitTests fasta_unittest.cpp fastq_unittest.cpp filetype_unittest.cpp stats_unittest.cpp)
target_link_libraries(runUnitTests gtest gtest_main fasta fastq filetype stats)
add_test(runUnitTests runUnitTests)

add_library(fasta fasta.cpp)
add_library(fastq fastq.cpp)
add_library(filetype filetype.cpp)
add_library(stats stats.cpp)
target_link_libraries(stats fasta fastq filetype)
add_executable(assembly-stats assembly-stats.cpp)
target_link_libraries(assembly-stats stats)

set(INSTALL_DIR /usr/local/bin CACHE PATH "Installation directory for executables")
install(TARGETS assembly-stats DESTINATION ${INSTALL_DIR})
