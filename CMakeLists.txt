cmake_minimum_required(VERSION 3.26)
project(BibbleASM VERSION 1.0.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)

add_subdirectory(framework)
add_subdirectory(main)

configure_package_config_file(
    cmake/BibbleASMConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/BibbleASMConfig.cmake
    INSTALL_DESTINATION lib/cmake/BibbleASM
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/BibbleASMConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/BibbleASMConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/BibbleASMConfigVersion.cmake
    DESTINATION lib/cmake/BibbleASM
)
