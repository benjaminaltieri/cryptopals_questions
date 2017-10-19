add_library(ExampleQuestion my_class.cpp)
target_include_directories(ExampleQuestion
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_executable(ExampleQuestionMain main.cpp)
target_link_libraries(ExampleQuestionMain ExampleQuestion)

add_subdirectory(unit_test)
