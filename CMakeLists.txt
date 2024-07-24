cmake_minimum_required(VERSION 3.25)
project(risucont)

set(CMAKE_C_STANDARD 90)

add_executable(risucont
        test/main.c
        risucont/map.c
        risucont/set.c
)

target_compile_options(risucont PUBLIC
        -Wall -Wextra -Wpedantic -Werror
        -D RISUCONT_MAP_BUCKET_SIZE_LOG2=5
)
