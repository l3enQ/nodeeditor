file(GLOB_RECURSE CPPS  ./*.cpp )

set(CPP_SOURCE_FILES
    widgets/modelswidget.cpp
    widgets/loadedtreewidget.cpp
    widgets/filtermodel.cpp
)

add_executable(graph2 ${CPPS})

target_link_libraries(graph2 QtNodes)
