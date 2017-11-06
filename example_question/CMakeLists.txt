set(TargetBase ExampleQuestion)

add_library(${TargetBase} example_class.cpp)
target_include_directories(${TargetBase}
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

add_executable(${TargetBase}.bin main.cpp)
target_link_libraries(${TargetBase}.bin ${TargetBase})

add_subdirectory(unit_test)


add_custom_target(${TargetBase}.run DEPENDS ${TargetBase}.bin)
add_dependencies(${TargetBase}.run ${TargetBase}.bin)
add_custom_command(TARGET ${TargetBase}.run POST_BUILD
                   COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${TargetBase}.bin
                   )

