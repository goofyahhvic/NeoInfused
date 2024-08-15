cmake_minimum_required(VERSION 3.29.0)
set(CMAKE_CXX_STANDARD 20)

add_library(NeoInfused
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/neo_core.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/core/neo_app.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/core/neo_input.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/core/neo_window.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/data_structures/neo_layer-storage.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/data_structures/neo_scene-storage.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/data_structures/neo_window-storage.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/graphics/neo_mesh.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/graphics/neo_shader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/graphics/gl/neo-gl_context.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/graphics/gl/neo-gl_mesh.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NeoInfused/graphics/gl/neo-gl_shader.cpp
           )

if(WIN32)
    target_compile_definitions(NeoInfused PUBLIC NEO_PLATFORM_WINDOWS)
else()
    target_compile_definitions(NeoInfused PUBLIC NEO_PLATFORM_LINUX)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(NeoInfused PUBLIC NEO_CONFIG_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(NeoInfused PUBLIC NEO_CONFIG_RELEASE)
    set(CMAKE_CXX_FLAGS "-O3")
elseif(CMAKE_BUILD_TYPE STREQUAL "Distribution")
    target_compile_definitions(NeoInfused PUBLIC NEO_CONFIG_DIST)
    set(CMAKE_CXX_FLAGS "-O3")
else()

endif()


target_include_directories(NeoInfused
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/include
                          )

target_link_libraries(NeoInfused glad glfw)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
