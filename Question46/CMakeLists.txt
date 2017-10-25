add_library(Question46 my_class.cpp)
target_include_directories(Question46
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_executable(Question46Main main.cpp)
target_link_libraries(Question46Main Question46)

add_subdirectory(unit_test)
