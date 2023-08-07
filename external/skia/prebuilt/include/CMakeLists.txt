cmake_minimum_required(VERSION 3.10)

add_subdirectory(codec)
add_subdirectory(config)
add_subdirectory(core)
add_subdirectory(effects)
add_subdirectory(encode)
add_subdirectory(gpu)
add_subdirectory(pathops)
add_subdirectory(ports)
add_subdirectory(private)
add_subdirectory(sksl)
add_subdirectory(third_party)
add_subdirectory(utils)

target_include_directories(skia
        PUBLIC
        "."
        ".."
        )