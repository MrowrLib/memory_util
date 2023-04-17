cmake_minimum_required(VERSION 3.21)
project(_Log_ VERSION 0.1.0 LANGUAGES CXX)
set(namespace MrowrLib)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${namespace}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake.in "@PACKAGE_INIT@\n\ninclude(CMakeFindDependencyMacro)\ninclude(\"${CMAKE_INSTALL_PREFIX}/@PROJECT_NAME@Targets.cmake\")")

configure_package_config_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    PATH_VARS CMAKE_INSTALL_PREFIX
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

find_package(spdlog CONFIG REQUIRED)
find_path(MROWR_LOG_INCLUDE_DIRS "_Log_")
find_path(MROWR_STRING_FORMAT_INCLUDE_DIRS "string_format")
add_executable(Example Example.cpp)
target_link_libraries(Example PRIVATE ${PROJECT_NAME} spdlog::spdlog)
target_include_directories(Example INTERFACE ${MROWR_LOG_INCLUDE_DIRS})
target_include_directories(Example INTERFACE ${MROWR_STRING_FORMAT_INCLUDE_DIRS})
target_compile_features(Example PRIVATE cxx_std_20)
