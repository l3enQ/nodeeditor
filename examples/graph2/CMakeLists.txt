file(GLOB_RECURSE CPPS  ./*.cpp )

add_executable(graph2 ${CPPS})

target_link_libraries(graph2 QtNodes)
