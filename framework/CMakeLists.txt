cmake_minimum_required(VERSION 3.26)

include(FetchContent)
include(GenerateExportHeader)

FetchContent_Declare(BibbleBytecode
    GIT_REPOSITORY https://github.com/JannikBulow/BibbleBytecode
    GIT_TAG master
)
FetchContent_MakeAvailable(BibbleBytecode)

set(SOURCES
)

set(HEADERS
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_library(BibbleASM-framework-shared SHARED ${SOURCES} ${HEADERS})
add_library(BibbleASM-framework-static STATIC ${SOURCES} ${HEADERS})

generate_export_header(BibbleASM-framework-shared
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/BibbleASM/api.h
    EXPORT_MACRO_NAME BIBBLEASM_EXPORT
    NO_EXPORT_MACRO_NAME BIBBLEASM_NO_EXPORT
    STATIC_DEFINE BIBBLEASM_STATIC_DEFINE
)

target_compile_definitions(BibbleASM-framework-static PUBLIC BIBBLEASM_STATIC_DEFINE)

target_include_directories(BibbleASM-framework-shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(BibbleASM-framework-static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(BibbleASM-framework-shared PUBLIC cxx_std_20)
target_compile_features(BibbleASM-framework-static PUBLIC cxx_std_20)