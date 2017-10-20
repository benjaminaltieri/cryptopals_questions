add_library(Question6 my_class.cpp)
target_include_directories(Question6
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_executable(Question6Main main.cpp)
target_link_libraries(Question6Main Question6)

add_subdirectory(unit_test)
