add_library(Question4 my_class.cpp)
target_include_directories(Question4
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_executable(Question4Main main.cpp)
target_link_libraries(Question4Main Question4)

add_subdirectory(unit_test)
