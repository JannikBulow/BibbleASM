cmake_minimum_required(VERSION 3.26)

set(SOURCES
    src/main.cpp
)

set(HEADERS
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_executable(BibbleASM-main ${SOURCES} ${HEADERS})

target_include_directories(BibbleASM-main PUBLIC include)

target_compile_features(BibbleASM-main PUBLIC cxx_std_20)

target_link_libraries(BibbleASM-main PRIVATE BibbleASM-framework-shared)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_custom_command(TARGET BibbleASM-main PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:BibbleASM-framework-shared>
        $<TARGET_FILE_DIR:BibbleASM-main>
    )

    add_custom_command(TARGET BibbleASM-main PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:BibbleBytecode-shared>
        $<TARGET_FILE_DIR:BibbleASM-main>
    )

    if (MSVC)
        add_custom_command(TARGET BibbleASM-main PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_PDB_FILE:BibbleASM-framework-shared>
            $<TARGET_FILE_DIR:BibbleASM-main>
        )

        add_custom_command(TARGET BibbleASM-main PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_PDB_FILE:BibbleBytecode-shared>
            $<TARGET_FILE_DIR:BibbleASM-main>
        )
    endif()
endif()