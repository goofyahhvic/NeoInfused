cmake_minimum_required(VERSION 3.29.0)
set(CMAKE_CXX_STANDARD 20)

macro(add_precompiled_header PrecompiledHeader PrecompiledSource SourcesVar Target HeaderDir)
    if(MSVC)
        get_filename_component(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
        set(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
        set(Sources ${${SourcesVar}})

        set_source_files_properties(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
                                           set_source_files_properties(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  

    list(APPEND ${SourcesVar} ${PrecompiledSource})
    else()
        target_precompile_headers(${Target} PUBLIC ${HeaderDir}/${PrecompiledHeader})
    endif(MSVC)
endmacro(add_precompiled_header)

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
endif()

add_precompiled_header("neo_pch.hpp" "neo_pch.cpp" ${CMAKE_CURRENT_SOURCE_DIR}/src NeoInfused ${CMAKE_CURRENT_SOURCE_DIR}/include/)

target_include_directories(NeoInfused
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/include
                          )

target_link_libraries(NeoInfused glad glfw)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
