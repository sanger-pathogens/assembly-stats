add_library(fasta fasta.cpp)
add_library(fastq fastq.cpp)
add_library(filetype filetype.cpp)
add_library(stats stats.cpp)

target_link_libraries(stats fasta fastq filetype)

add_executable(assembly-stats assembly-stats.cpp)
target_link_libraries(assembly-stats stats)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include" DESTINATION include)
install(TARGETS stats DESTINATION lib)
install(TARGETS assembly-stats RUNTIME DESTINATION bin)
