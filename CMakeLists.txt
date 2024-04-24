cmake_minimum_required(VERSION 3.16)
project(Arcman LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Gather all .cpp files recursively in the src directory and its subdirectories
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*/*.cpp")

add_executable(Arcman ${SRC_FILES})
target_link_libraries(Arcman PRIVATE sfml-graphics)
target_compile_features(Arcman PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Arcman
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Arcman>
        VERBATIM)
endif()

install(TARGETS Arcman)
