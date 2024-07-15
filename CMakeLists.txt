# Template Solution

cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJECT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${PROJECT_FOLDER})
set(CMAKE_CXX_STANDARD 17)


file(GLOB_RECURSE GAME_SOURCES
    "Engine/Source/*.cpp"
    "Engine/Source/*.h"
    "Assets/*.h"
    "Assets/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${GAME_SOURCES})

add_executable(${PROJECT_FOLDER} ${GAME_SOURCES})

file(READ "Engine\\Saves\\enginepath.txt" FILE_CONTENT)
file(TO_CMAKE_PATH "${FILE_CONTENT}" FILE_CONTENT)
string(STRIP "${FILE_CONTENT}" FILE_CONTENT)
set(PATH_LIBRARIES "${FILE_CONTENT}/Core/Source/Include/LIB")

set(ENGINE_LIBRARY_DEBUG "${FILE_CONTENT}/Build/Engine/Debug/Engine.lib")
set(ENGINE_LIBRARY_RELEASE "${FILE_CONTENT}/Build/Engine/Release/Engine.lib")

set(ADDITIONAL_INCLUDE_PATHS
    Engine/Core/Source
    Framework/Source
    Engine
    ThirdParty
    ThirdParty/imgui
    ThirdParty/utility
    ThirdParty/imgui-sfml
)

foreach(PATH ${ADDITIONAL_INCLUDE_PATHS})
    list(APPEND FULL_PATHS "${FILE_CONTENT}/${PATH}")
endforeach()

include_directories(${FULL_PATHS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Assets)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine)

# Link libs
target_link_libraries(${PROJECT_FOLDER} PRIVATE
    Framework
)

if(MSVC)
    target_compile_options(${PROJECT_FOLDER} PRIVATE /W4)
endif()

add_subdirectory(C:/Dev/SpriteEngineUI/Engine/Engine Engine)
add_subdirectory(C:/Dev/SpriteEngineUI/Engine/ThirdParty/sfml SFML)
add_subdirectory(C:/Dev/SpriteEngineUI/Engine/ThirdParty ThirdParty)
add_subdirectory(C:/Dev/SpriteEngineUI/Engine/Framework Framework)
