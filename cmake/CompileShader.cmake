
set(CompileShaderPy ${CMAKE_CURRENT_LIST_DIR}/CompileShader.py)

# Create shader target
# add_shader_target(<TargetName>
#   [GLSL_COMPILER <executable program>]
#   <shader source files list>
# )
function(add_shader_target TargetName)
    # Parse required shader args
    set(options "")
    set(oneValueArgs GLSL_COMPILER)
    set(multiValueArgs "")
    cmake_parse_arguments(SARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(SARGS_SHADER_SRC ${SARGS_UNPARSED_ARGUMENTS})

    # Check shader args
    if(NOT SARGS_SHADER_SRC)
        cmsg(ERROR "[${TargetName}] No shader source files were provided")
    endif()
    if (NOT SARGS_GLSL_COMPILER)
        # if (Vulkan_FOUND)
        #     # set(SARGS_GLSL_COMPILER ${Vulkan_GLSLC_EXECUTABLE})
        #     set(SARGS_GLSL_COMPILER ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE})
        # else()
        #     cmsg(ERROR "[${TargetName}] Please find vulkan package or provide GLSL_COMPILER")
        # endif()
        set(SARGS_GLSL_COMPILER ${glslang_glslangValidator})
    endif()

    set(TargetPath  ${LIBRARY_OUTPUT_PATH}/${TargetName})
    file(MAKE_DIRECTORY "${TargetPath}")

    # Create targets
    set(CompiledSources "")
    set(CompiledTargets "")
    foreach(Shader ${SARGS_SHADER_SRC})
        get_filename_component(ShaderName ${Shader} NAME)
        set(ShaderSpv ${TargetPath}/${ShaderName}.spv)
        set(ShaderHeader ${TargetPath}/${ShaderName}.h)
        set(ShaderSource ${TargetPath}/${ShaderName}.c)
        list(APPEND CompiledTargets ${ShaderHeader} ${ShaderSource})
        list(APPEND CompiledSources ${ShaderSource})
        add_custom_command(
            OUTPUT ${ShaderHeader} ${ShaderSource}
            COMMAND python ${CompileShaderPy} ${SARGS_GLSL_COMPILER} ${Shader} ${TargetPath}
            DEPENDS ${Shader}
            COMMENT "${CMsgInfo}[${TargetName}] Compiling ${Shader}${CMsgReset}")
    endforeach()

    add_custom_target(${TargetName}.dep DEPENDS ${CompiledTargets})

    project(${TargetName})
    add_library(${TargetName} STATIC ${CompiledSources})
    target_include_directories(${TargetName} PUBLIC ${TargetPath})
    add_dependencies(${TargetName} ${TargetName}.dep)
endfunction()
