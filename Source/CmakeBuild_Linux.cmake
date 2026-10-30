cmake_minimum_required(VERSION 4.0)

set(Platform "SDL3")

message("Compiling for ${Platform}")

file(GLOB PLATFORM_FILES "${Platform}/*")
file(GLOB ENGINE_FILES "Engine/*")

file(COPY ${PLATFORM_FILES} DESTINATION "build_stage_2")
file(COPY ${ENGINE_FILES} DESTINATION "build_stage_2")

if(Platform STREQUAL "SDL3")
    file(COPY "Libs/SDL3/lib/x64/SDL3.lib" DESTINATION "build")
    
    if(NOT EXISTS "build/SDL3.lib")
        message(FATAL_ERROR "SDL3.lib not found")
    endif()

    file(COPY "Libs/SDL3_image/lib/x64/SDL3_image.lib" DESTINATION "build")

    file(COPY "test wads/DOOM_SHAREWERE.WAD" DESTINATION "build")

    if(NOT EXISTS "build/SDL3_image.lib")
        message(FATAL_ERROR "SDL3_image.lib not found")
    endif()
endif()