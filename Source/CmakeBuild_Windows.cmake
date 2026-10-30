cmake_minimum_required(VERSION 4.0)

set(Platform "SDL3")

message("Compiling for ${Platform}")

file(GLOB PLATFORM_FILES "${Platform}/*")
file(GLOB ENGINE_FILES "Engine/*")

file(COPY ${PLATFORM_FILES} DESTINATION "build_stage_2")
file(COPY ${ENGINE_FILES} DESTINATION "build_stage_2")

if(Platform STREQUAL "SDL3")
    file(COPY "Libs/SDL3/lib/x64/SDL3.dll" DESTINATION "build")
    
    if(NOT EXISTS "build/SDL3.dll")
        message(FATAL_ERROR "SDL3.dll not found")
    endif()

    file(COPY "Libs/SDL3_image/lib/x64/SDL3_image.dll" DESTINATION "build")

    file(COPY "test wads/DOOM_SHAREWERE.WAD" DESTINATION "build")

    if(NOT EXISTS "build/SDL3_image.dll")
        message(FATAL_ERROR "SDL3_image.dll not found")
    endif()
endif()