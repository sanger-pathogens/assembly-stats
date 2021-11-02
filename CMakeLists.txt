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

## Download dependencies if not provided
## bxzstr
if (DEFINED CMAKE_BXZSTR_HEADERS)
  message(STATUS "bxzstr headers provided in: ${CMAKE_BXZSTR_HEADERS}")
else()
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/CMakeLists-bxzstr.txt.in ${CMAKE_BINARY_DIR}/external/bxzstr-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external/bxzstr-download )
  if(result)
    message(FATAL_ERROR "CMake step for bxzstr failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external/bxzstr-download )
  if(result)
    message(FATAL_ERROR "Build step for bxzstr failed: ${result}")
  endif()
  set(CMAKE_BXZSTR_HEADERS ${CMAKE_CURRENT_BINARY_DIR}/external/bxzstr/include)
endif()
include_directories(${CMAKE_BXZSTR_HEADERS})

add_library(fasta fasta.cpp)
add_library(fastq fastq.cpp)
add_library(filetype filetype.cpp)
add_library(stats stats.cpp)

## Check supported compression types
find_package(BZip2)
if (BZIP2_FOUND)
  include_directories(${BZIP2_INCLUDE_DIRS})
  target_link_libraries(fasta fastq filetype stats ${BZIP2_LIBRARIES})
endif()
find_package(LibLZMA)
if (LIBLZMA_FOUND)
  include_directories(${LIBLZMA_INCLUDE_DIRS})
  target_link_libraries(fasta fastq filetype stats ${LIBLZMA_LIBRARIES})
endif()
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
  include_directories(${ZLIB_INCLUDE_DIRS})
  target_link_libraries(fasta fastq filetype stats ${ZLIB_LIBRARIES})
endif()

target_link_libraries(stats fasta fastq filetype)
add_executable(assembly-stats assembly-stats.cpp)
target_link_libraries(assembly-stats stats)

set(INSTALL_DIR /usr/local/bin CACHE PATH "Installation directory for executables")
install(TARGETS assembly-stats DESTINATION ${INSTALL_DIR})
