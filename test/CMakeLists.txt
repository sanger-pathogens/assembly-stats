file(COPY "${CMAKE_SOURCE_DIR}/test_files" DESTINATION "${CMAKE_BINARY_DIR}/bin")

add_executable(run_unit_tests
        fasta_unittest.cpp
        fastq_unittest.cpp
        filetype_unittest.cpp
        stats_unittest.cpp)

target_link_libraries(run_unit_tests
        ${GTEST_BOTH_LIBRARIES}
        fasta
        fastq
        filetype
        stats)

add_test(run_unit_tests run_unit_tests)

install(TARGETS run_unit_tests RUNTIME DESTINATION bin)