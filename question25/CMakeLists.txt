add_library(Question25 my_class.cpp)
target_include_directories(Question25
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_executable(Question25Main main.cpp)
target_link_libraries(Question25Main Question25)

add_subdirectory(unit_test)
