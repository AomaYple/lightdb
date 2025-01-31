cmake_minimum_required(VERSION 3.30)

project(lightdb)

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CXX_STANDARD ${CMAKE_CXX_STANDARD_LATEST}
        CXX_STANDARD_REQUIRED ON
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
)
target_sources(${PROJECT_NAME}
        PRIVATE
        ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME}
            PRIVATE
            -Wall -Wextra -Wpedantic
            $<$<CONFIG:Debug>:-g3 -ggdb3 -Og -fsanitize=address -fsanitize=leak -fsanitize=undefined>
            $<$<CONFIG:Release>:-Ofast>
    )
    target_link_options(${PROJECT_NAME}
            PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address -fsanitize=leak -fsanitize=undefined>
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}
            PRIVATE
            -Weverything
            -stdlib=libc++
            $<$<CONFIG:Debug>:-g3 -glldb -Og -fsanitize=address -fsanitize=leak -fsanitize=undefined>
            $<$<CONFIG:Release>:-O3 -ffast-math>
    )
    target_link_options(${PROJECT_NAME}
            PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address -fsanitize=leak -fsanitize=undefined>
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME}
            PRIVATE
            /utf-8 /Wall /MP /permissive-
            $<$<CONFIG:Debug>:/sdl /fsanitize=address>
            $<$<CONFIG:Release>:/Ob3 /GT /Gy /fp:fast>
    )

    target_link_options(${PROJECT_NAME}
            PRIVATE
            $<$<CONFIG:Release>:/OPT:REF,ICF /LTCG:incremental>
    )
endif ()

option(NATIVE "Enable native optimization")
if (CMAKE_BUILD_TYPE STREQUAL "Release" AND NATIVE)
    target_compile_options(${PROJECT_NAME}
            PRIVATE
            $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-march=native>
    )
endif ()

set(installTargets ${PROJECT_NAME}Targets)
install(TARGETS ${PROJECT_NAME}
        EXPORT ${installTargets}
)

install(EXPORT ${installTargets}
        FILE ${PROJECT_NAME}Config.cmake
        DESTINATION lib/cmake/${PROJECT_NAME}
)

install(DIRECTORY include/
        DESTINATION include
)
