cmake_minimum_required(VERSION 3.10)

add_subdirectory(prebuilt)

add_library(skia STATIC
        include/skia-utils/skia_svg.h
        include/skia-utils/skia_utils.h
        src/skia_svg.cpp
        src/skia_utils.cpp
        )

target_include_directories(skia PUBLIC include)
target_include_directories(skia PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/prebuilt")

if (APPLE)
    target_link_libraries(skia PUBLIC skia_base)
elseif (ANDROID)
    target_link_libraries(skia PUBLIC skia_resource skia_svg skia_shader skia_unicode skia_base libexpat onyx_icu onyx_icudata)
elseif (UNIX)
    target_link_libraries(skia PUBLIC skia_resource skia_svg skia_shader skia_unicode skia_base expat harfbuzz fontconfig freetype pthread png jpeg z icui18n icuuc icudata GL)
endif()

