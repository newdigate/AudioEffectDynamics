cmake_minimum_required(VERSION 3.10)

project(audio_effect_dynamics_example)
set(CMAKE_CXX_STANDARD 11)

option(OPT_BUILD_FOR_LINUX "Build for linux emulator" OFF)
if (OPT_BUILD_FOR_LINUX)
    set(BUILD_FOR_LINUX 1)
    add_definitions(-DBUILD_FOR_LINUX)
endif()

if (DEFINED BUILD_FOR_LINUX)
    find_package(teensy_x86_stubs)
    include_directories(${teensy_x86_stubs_INCLUDE_DIR})

    find_package(teensy_x86_sd_stubs)
    include_directories(${teensy_x86_sd_stubs_INCLUDE_DIR})

    find_package(teensy_audio_x86_stubs)
    include_directories(${teensy_audio_x86_stubs_INCLUDE_DIR})

    find_package(teensy_audio_x86_stubs_soundio)
    include_directories(${teensy_audio_x86_stubs_soundio_INCLUDE_DIR})

    include_directories(/usr/local/include)
    add_executable(audio_effect_dynamics_example
            main.cpp
            effect_dynamics.cpp
            effect_dynamics.h)

    target_link_libraries(audio_effect_dynamics_example ${teensy_x86_stubs_LIBS})
    target_link_libraries(audio_effect_dynamics_example ${teensy_x86_sd_stubs_LIBS})
    target_link_libraries(audio_effect_dynamics_example ${teensy_audio_x86_stubs_LIBS})
    target_link_libraries(audio_effect_dynamics_example ${teensy_audio_x86_stubs_soundio_LIBS})
    target_link_libraries(audio_effect_dynamics_example /usr/local/lib/libsoundio.a)
    if (APPLE)
        target_link_libraries(audio_effect_dynamics_example "-framework CoreServices" "-framework CoreAudio" "-framework Foundation" "-framework AudioUnit")
    endif()

else()

    include(teensy.options.cmake.in)
    include(teensy.build.cmake.in)

    add_custom_target(installarduino
            "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/install_arduino_library.cmake")

    teensy_add_executable(main main.cpp effect_dynamics.cpp)
    set(CMAKE_VERBOSE_MAKEFILE 1)
endif()