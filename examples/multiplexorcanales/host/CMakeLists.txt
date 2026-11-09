# CMakeLists.txt — HOST example: MultiplexorCanales
# Generado por fmu_codegen_host.py.
# Herramienta: OpenModelica Compiler OpenModelica v1.25.7 (64-bit)
#
# Targets:
#   multiplexorcanales_host_me  — instancia como ModelExchange
#   multiplexorcanales_host_cs  — instancia como CoSimulation

cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED FMU2HOST_ROOT)
    get_filename_component(FMU2HOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../.." ABSOLUTE)
endif()

set(FMU_SRC "${FMU2HOST_ROOT}/models/MultiplexorCanales/MultiplexorCanales/sources")
file(GLOB_RECURSE FMU_SOURCES "${FMU_SRC}/*.c")

# Parche MSVC: 'const int x[0] = {}' (C2466) generado por OpenModelica
if(MSVC)
    foreach(_SRC ${FMU_SOURCES})
        file(READ "${_SRC}" _CONTENT)
        string(FIND "${_CONTENT}" "[0] = {}" _ZERO_ARR)
        if(NOT _ZERO_ARR EQUAL -1)
            get_filename_component(_NAME "${_SRC}" NAME_WE)
            set(_FIXED "${CMAKE_CURRENT_BINARY_DIR}/${_NAME}_msvc.c")
            string(REPLACE "const int columns[0] = {};"
                           "const int columns[1] = {0};" _CONTENT "${_CONTENT}")
            string(REPLACE "const int rows[0] = {};"
                           "const int rows[1] = {0};" _CONTENT "${_CONTENT}")
            file(WRITE "${_FIXED}" "${_CONTENT}")
            list(REMOVE_ITEM FMU_SOURCES "${_SRC}")
            list(APPEND FMU_SOURCES "${_FIXED}")
        endif()
    endforeach()
endif()

# -- Target multiplexorcanales_host_me (Model Exchange) --
add_executable(multiplexorcanales_host_me
    main_me.c
    scenario.c
    multiplexorcanales_adapter_me.c
    ${FMU_SOURCES}
)
target_include_directories(multiplexorcanales_host_me PRIVATE
    "${FMU_SRC}"
    "${FMU_SRC}/fmi"
    "${FMU_SRC}/fmi-export"
    "${FMU_SRC}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(multiplexorcanales_host_me PRIVATE fmi)
target_compile_definitions(multiplexorcanales_host_me PRIVATE
    FMI2_FUNCTION_PREFIX=MultiplexorCanales_
)
if(WIN32)
    target_link_libraries(multiplexorcanales_host_me PRIVATE ws2_32)
endif()

configure_file("${FMU2HOST_ROOT}/models/MultiplexorCanales/MultiplexorCanales/resources/MultiplexorCanales_info.json"
    "${CMAKE_CURRENT_BINARY_DIR}/MultiplexorCanales_info.json" COPYONLY)
add_custom_command(TARGET multiplexorcanales_host_me POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FMU2HOST_ROOT}/models/MultiplexorCanales/MultiplexorCanales/resources/MultiplexorCanales_info.json"
        "$<TARGET_FILE_DIR:multiplexorcanales_host_me>/MultiplexorCanales_info.json"
    COMMENT "Copiando MultiplexorCanales_info.json"
)
set_target_properties(multiplexorcanales_host_me PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:multiplexorcanales_host_me>"
)

add_test(NAME multiplexorcanales_host_me COMMAND multiplexorcanales_host_me
    WORKING_DIRECTORY "$<TARGET_FILE_DIR:multiplexorcanales_host_me>")

# -- Target multiplexorcanales_host_cs (Co-Simulation) --
add_executable(multiplexorcanales_host_cs
    main_cs.c
    scenario.c
    multiplexorcanales_adapter_cs.c
    ${FMU_SOURCES}
)
target_include_directories(multiplexorcanales_host_cs PRIVATE
    "${FMU_SRC}"
    "${FMU_SRC}/fmi"
    "${FMU_SRC}/fmi-export"
    "${FMU_SRC}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(multiplexorcanales_host_cs PRIVATE fmi)
target_compile_definitions(multiplexorcanales_host_cs PRIVATE
    FMI2_FUNCTION_PREFIX=MultiplexorCanales_
)
if(WIN32)
    target_link_libraries(multiplexorcanales_host_cs PRIVATE ws2_32)
endif()

configure_file("${FMU2HOST_ROOT}/models/MultiplexorCanales/MultiplexorCanales/resources/MultiplexorCanales_info.json"
    "${CMAKE_CURRENT_BINARY_DIR}/MultiplexorCanales_info.json" COPYONLY)
add_custom_command(TARGET multiplexorcanales_host_cs POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FMU2HOST_ROOT}/models/MultiplexorCanales/MultiplexorCanales/resources/MultiplexorCanales_info.json"
        "$<TARGET_FILE_DIR:multiplexorcanales_host_cs>/MultiplexorCanales_info.json"
    COMMENT "Copiando MultiplexorCanales_info.json"
)
set_target_properties(multiplexorcanales_host_cs PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:multiplexorcanales_host_cs>"
)

add_test(NAME multiplexorcanales_host_cs COMMAND multiplexorcanales_host_cs
    WORKING_DIRECTORY "$<TARGET_FILE_DIR:multiplexorcanales_host_cs>")
