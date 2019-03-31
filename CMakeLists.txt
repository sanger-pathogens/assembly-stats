cmake_minimum_required(VERSION 3.10)
project(assembly-stats
        VERSION 1.0.1
        LANGUAGES CXX
        DESCRIPTION "Get assembly statistics from FASTA and FASTQ files"
        HOMEPAGE_URL "https://github.com/sanger-pathogens/assembly-stats")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo"
            FORCE)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(src)

option(ASMSTATS_ENABLE_TESTS "Enable building & running unit tests" ON)
if (ASMSTATS_ENABLE_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(test)
endif ()
