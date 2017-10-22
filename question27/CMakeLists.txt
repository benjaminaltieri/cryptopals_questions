add_library(Question27 my_class.cpp)
target_include_directories(Question27
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_executable(Question27Main main.cpp)
target_link_libraries(Question27Main Question27)

add_subdirectory(unit_test)
