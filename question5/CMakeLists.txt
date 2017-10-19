add_library(Question5 my_class.cpp)
target_include_directories(Question5
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_executable(Question5Main main.cpp)
target_link_libraries(Question5Main Question5)

add_subdirectory(unit_test)
