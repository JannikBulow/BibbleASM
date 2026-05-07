cmake_minimum_required(VERSION 3.26)

include(FetchContent)
include(GenerateExportHeader)

FetchContent_Declare(BibbleBytecode
    GIT_REPOSITORY https://github.com/JannikBulow/BibbleBytecode
    GIT_TAG master
)
FetchContent_MakeAvailable(BibbleBytecode)

FetchContent_Declare(BibbleOpcodes
    GIT_REPOSITORY https://github.com/JannikBulow/BibbleOpcodes
    GIT_TAG master
)
FetchContent_MakeAvailable(BibbleOpcodes)

set(SOURCES
    src/codegen/builder/class_builder.cpp
    src/codegen/builder/const_pool_builder.cpp
    src/codegen/builder/function_builder.cpp
    src/codegen/builder/module_builder.cpp

    src/codegen/assembler.cpp

    src/instruction/instruction.cpp

    src/lexer/lexer.cpp
    src/lexer/token.cpp
)

set(HEADERS
    include/BibbleASM/codegen/builder/class_builder.h
    include/BibbleASM/codegen/builder/const_pool_builder.h
    include/BibbleASM/codegen/builder/function_builder.h
    include/BibbleASM/codegen/builder/module_builder.h

    include/BibbleASM/codegen/assembler.h
    include/BibbleASM/codegen/opcodes.h

    include/BibbleASM/instruction/builder.h
    include/BibbleASM/instruction/builder_funcs.h
    include/BibbleASM/instruction/instruction.h
    include/BibbleASM/instruction/operand.h

    include/BibbleASM/lexer/lexer.h
    include/BibbleASM/lexer/token.h
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

target_link_libraries(BibbleASM-framework-shared BibbleBytecode-shared BibbleOpcodes)
target_link_libraries(BibbleASM-framework-static BibbleBytecode-static BibbleOpcodes)
