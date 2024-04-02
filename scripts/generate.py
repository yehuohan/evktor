#!/usr/bin/env python3

import os
import sys

__VCPKG_TRIPLET = os.environ["VCPKG_TRIPLET"]

__DIR_THIS = os.path.dirname(os.path.abspath(__file__))
__DIR_ROOT = os.path.dirname(__DIR_THIS)
__DIR_VkValidationLayers = f"{__DIR_ROOT}/deps/repos/Vulkan-ValidationLayers/scripts"
__DIR_VkHeaders = f"{__DIR_ROOT}/deps/{__VCPKG_TRIPLET}/share/vulkan/registry"
sys.path.insert(0, __DIR_VkHeaders)
sys.path.insert(0, __DIR_VkValidationLayers)

import shutil
import subprocess
from xml.etree import ElementTree
from reg import Registry
from generators.base_generator import SetOutputDirectory, SetTargetApiName, SetMergedApiNames
from generators.base_generator import BaseGeneratorOptions
from generators.ldt_generator import LDTGenerator
from generators.initializer_generator import InitializerGenerator
from generators.onstring_generator import OnStringGenerator

__VK_Out = f"{__DIR_ROOT}/src"
__VK_Sty = f"{__DIR_ROOT}/.clang-format"
__VK_Xml = f"{__DIR_VkHeaders}/vk.xml"
__VK_Api = "vulkan"
__VK_Generators = {
    "libvkt_layer/generated/vk_ldt.hpp": lambda: LDTGenerator(["vkt"]),
    "libvktor/generated/vk_initializer.hpp": lambda: InitializerGenerator(["vkt", "Itor"]),
    "libvktor/generated/vk_string.hpp": lambda: OnStringGenerator(["vkt"]),
    "libvktor/generated/vk_string.cpp": lambda: OnStringGenerator(["vkt"], "vk_string.hpp"),
}


def generate(filename, generator):
    opts = BaseGeneratorOptions(customFileName=filename)
    reg = Registry(generator(), opts)
    tree = ElementTree.parse(__VK_Xml)
    [
        exts.remove(e)
        for exts in tree.findall("extensions")
        for e in exts.findall("extension")
        if (sup := e.get("supported")) is not None and all(api not in sup.split(",") for api in [__VK_Api])
    ]
    reg.loadElementTree(tree)
    reg.apiGen()
    print(f"Generated {filename}")
    # Format
    if shutil.which("clang-format") is not None:
        sys.stdout.flush()
        cmd = f"clang-format -i --style=file:{__VK_Sty} {__VK_Out}/{filename}"
        subprocess.check_call(cmd.split(" "))


def main():
    SetOutputDirectory(__VK_Out)
    SetTargetApiName(__VK_Api)
    SetMergedApiNames(None)
    for fn, gr in __VK_Generators.items():
        generate(fn, gr)


if __name__ == "__main__":
    main()
