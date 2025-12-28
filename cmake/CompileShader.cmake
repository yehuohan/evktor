set(CompileShaderPy ${CMAKE_CURRENT_LIST_DIR}/CompileShader.py)

string(ASCII 27 __Esc)
set(MsgError "${__Esc}[1;31m")
set(MsgInfo  "${__Esc}[32m")
set(MsgReset "${__Esc}[m")

# Create shader target
#
# Requires:
#   * LIBRARY_OUTPUT_PATH
#   * Python
#   * glslc or slangc
#
# add_shader_target(<TargetName>
#   <glsl/slang files list>
#   [INCLUDE_DIRECTORIES <include directories list>]
#   [COMPILE_DEFINITIONS <macros list, e.g. HAS_VEC USE_MAT=1>]
#   [COMPILE_OPTIONS <extra compiler args>]
# )
function(add_shader_target TargetName)
    # Parse required shader args
    set(options "")
    set(oneValueArgs "")
    set(multiValueArgs INCLUDE_DIRECTORIES COMPILE_DEFINITIONS COMPILE_OPTIONS)
    cmake_parse_arguments(SHADER "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(SHADER_SRC ${SHADER_UNPARSED_ARGUMENTS})

    # Check shader args
    if(NOT SHADER_SRC)
        message(FATAL_ERROR "${MsgError}[${TargetName}] Shader target requires shader source files${MsgReset}")
    endif()

    set(TargetPath  ${LIBRARY_OUTPUT_PATH}/${TargetName})
    file(MAKE_DIRECTORY "${TargetPath}")

    # Create targets
    set(CompiledSources "")
    set(CompiledTargets "")
    foreach(Shader ${SHADER_SRC})
        get_filename_component(ShaderName ${Shader} NAME)
        set(ShaderSpv ${TargetPath}/${ShaderName}.spv)
        set(ShaderHeader ${TargetPath}/${ShaderName}.h)
        set(ShaderSource ${TargetPath}/${ShaderName}.c)
        list(APPEND CompiledTargets ${ShaderHeader} ${ShaderSource})
        list(APPEND CompiledSources ${ShaderSource})
        add_custom_command(
            OUTPUT ${ShaderHeader} ${ShaderSource}
            COMMAND python ${CompileShaderPy} -i ${Shader} -o ${TargetPath}
                -D ${SHADER_COMPILE_DEFINITIONS}
                -I ${SHADER_INCLUDE_DIRECTORIES}
                -- ${SHADER_COMPILE_OPTIONS}
            DEPENDS ${Shader}
            COMMENT "${MsgInfo}[${TargetName}] Compiling ${Shader}${MsgReset}")
    endforeach()

    add_custom_target(${TargetName}.dep DEPENDS ${CompiledTargets})

    project(${TargetName})
    add_library(${TargetName} STATIC ${CompiledSources})
    target_include_directories(${TargetName} PUBLIC ${TargetPath})
    add_dependencies(${TargetName} ${TargetName}.dep)
endfunction()
