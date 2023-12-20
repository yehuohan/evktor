#!/usr/bin/env python3

import os
import sys

# CompilerArgs = "-mfmt=c --target-env=vulkan1.0"  # For glslc
CompilerArgs = "-V -x --target-env vulkan1.0"  # For glslangValidator

CodeHeader = """
#pragma once
#include <stdint.h>
extern const uint32_t {name}[];
extern const size_t {name}_size;
"""

CodeSource = """
#include "{header}"
const uint32_t {name}[] = {{
    {ustr}
}};
const size_t {name}_size = sizeof({name});
"""


def load_spv(spv_file):
    """Load spv data as bytes string"""
    with open(spv_file, mode="r", encoding="utf-8") as fp:
        return fp.read().replace("{", "").replace("}", "")


def dump_spv(shader_name, path):
    ustr = load_spv(f"{path}/{shader_name}.spv")
    header_file = f"{path}/{shader_name}.h"
    source_file = f"{path}/{shader_name}.c"
    name = shader_name.replace(".", "_").replace("-", "_")
    header = CodeHeader.format(name=name)
    source = CodeSource.format(header=f"{shader_name}.h", name=name, ustr=ustr)
    with open(header_file, mode="w", encoding="utf-8", newline="\n") as fp:
        fp.write(header)
    with open(source_file, mode="w", encoding="utf-8", newline="\n") as fp:
        fp.write(source)


def compile_shader(compiler, shader_file, output_path):
    shader_name = os.path.split(shader_file)[1]
    if os.system(f"{compiler} {CompilerArgs} -o {output_path}/{shader_name}.spv {shader_file}"):
        exit(-1)
    dump_spv(shader_name, output_path)


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: \n\t python CompileShader.py <glsl-compiler> <shader-file> <output-path>")
    else:
        compiler = sys.argv[1]
        shader_file = sys.argv[2]
        output_path = sys.argv[3]
        compile_shader(compiler, shader_file, output_path)
