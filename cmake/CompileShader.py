#!/usr/bin/env python3

"""
Compile glsl/slang/spirv shader code into static c/cpp array.
"""

import os
import argparse


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


def load_binary(spv_file):
    with open(spv_file, mode="rb") as fp:
        spv_bytes = fp.read()
        assert len(spv_bytes) % 4 == 0
        return ",".join([
            f"0x{int.from_bytes(spv_bytes[k : k + 4], 'little', signed=False):08x}" for k in range(0, len(spv_bytes), 4)
        ])


def load_array(spv_file):
    with open(spv_file, mode="r", encoding="utf-8") as fp:
        return fp.read().replace("{", "").replace("}", "").strip()


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", "-i", dest="input_file", required=True, help="Input shader file")
    parser.add_argument("--output", "-o", dest="output_path", required=True, help="Output path")
    parser.add_argument(
        "--binary-spirv",
        "-b",
        dest="spirv",
        action="store_true",
        default=False,
        help="Take the input shader as a binary spirv file",
    )
    parser.add_argument("--define-macro", "-D", dest="defs", default=[], nargs="*", help="Add shader macros")
    parser.add_argument("--include-dirs", "-I", dest="incs", default=[], nargs="*", help="Add shader includes")
    parser.add_argument("extra_args", default="", nargs=argparse.REMAINDER, help="Extra args for compilers after '--'")
    args = parser.parse_args()
    args.input_file = os.path.abspath(args.input_file)
    args.shader_file = os.path.split(args.input_file)[-1]
    args.shader_name = args.shader_file.replace(".", "_").replace("-", "_")
    args.output_path = os.path.abspath(args.output_path)
    args.defs = ("-D" if args.defs else "") + " -D".join(args.defs)
    args.incs = ("-I" if args.incs else "") + " -I".join(args.incs)
    args.extra_args = " ".join(args.extra_args[1:])
    if args.spirv:
        args.compiler = None
        args.load_spv = load_binary
    elif os.path.splitext(args.shader_file)[-1] == ".slang":
        default_args = "-target spirv"
        args.compiler = f"slangc {args.defs} {args.incs} {default_args} {args.extra_args} {args.input_file}"
        args.load_spv = load_binary
    else:
        default_args = "-mfmt=c --target-env=vulkan1.3"
        args.compiler = f"glslc {args.defs} {args.incs} {default_args} {args.extra_args} {args.input_file}"
        args.load_spv = load_array

    # print(args)
    return args


def dump_spv(args, spv_file):
    spv_uints = args.load_spv(spv_file)
    header_file = f"{args.output_path}/{args.shader_file}.h"
    source_file = f"{args.output_path}/{args.shader_file}.c"
    header = CodeHeader.format(name=args.shader_name)
    source = CodeSource.format(header=f"{args.shader_file}.h", name=args.shader_name, ustr=spv_uints)
    with open(header_file, mode="w", encoding="utf-8", newline="\n") as fp:
        fp.write(header)
    with open(source_file, mode="w", encoding="utf-8", newline="\n") as fp:
        fp.write(source)


def compile_shader(args: argparse.Namespace):
    if args.compiler:
        spv_file = f"{args.output_path}/{args.shader_file}.spv"
        if os.system(f"{args.compiler}  -o {spv_file}"):
            exit(-1)
    else:
        spv_file = args.input_file
    dump_spv(args, spv_file)


if __name__ == "__main__":
    args = get_args()
    compile_shader(args)
