set(SRC_FILES
    example_class.cpp
    util.cpp
    )

add_library(cryptopals ${SRC_FILES})
target_include_directories(cryptopals
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

