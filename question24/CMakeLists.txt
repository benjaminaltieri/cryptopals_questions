add_library(Question24 my_class.cpp)
target_include_directories(Question24
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_executable(Question24Main main.cpp)
target_link_libraries(Question24Main Question24)

add_subdirectory(unit_test)
