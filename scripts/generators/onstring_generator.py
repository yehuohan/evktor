#!/usr/bin/env python3

import re
from generators.base_generator import BaseGenerator
from generators.generator_utils import PlatformGuardHelper

LBracket = "{"
RBracket = "}"


def trim(tyname: str, name: str):
    prefix = tyname
    for s in ["Flags", "Flags2", "FlagsEXT", "FlagsKHR", "FlagsAMD", "FlagsNV", "FlagsFUCHSIA"]:
        if tyname.endswith(s):
            prefix = tyname.removesuffix(s)
            break
    prefix = "_".join(map(lambda x: x.upper(), re.findall("[A-Z][^A-Z]*", prefix))) + "_"
    res = name.removeprefix(prefix)
    for p in [
        "_BIT",
        "_BIT_EXT",
        "_BIT_KHR",
        "_BIT_AMD",
        "_BIT_AMDX",
        "_BIT_NV",
        "_BIT_QNX",
        "_BIT_FUCHSIA",
        "_BIT_HUAWEI",
        "_BIT_QCOM",
    ]:
        if res.endswith(p):
            res = res.removesuffix(p)
            break
    return res


class OnStringGenerator(BaseGenerator):
    def __init__(self, namespaces, include=None):
        BaseGenerator.__init__(self)
        if include:
            self.generate = self.generate_source
        else:
            self.generate = self.generate_header
        self.include = include
        self.namespaces = namespaces

    def generate_header(self):
        out = []
        out.append("#pragma once\n\n")
        out.append("#include <vulkan/vulkan.h>\n")
        out.append("#include <string>\n\n")
        out.append(f"#define VkStr(Type, Var) {'::'.join(self.namespaces)}::On_Str_##Type(Var)\n\n")
        out.append("\n".join(map(lambda ns: f"namespace {ns} {LBracket}", self.namespaces)))

        guarder = PlatformGuardHelper()
        out.append("\n\n// Enums\n")
        for e in self.vk.enums.values():
            out.extend(guarder.add_guard(e.protect))
            out.append(f"std::string On_Str_{e.name}({e.name} e);\n")
        out.extend(guarder.add_guard(None))

        guarder = PlatformGuardHelper()
        out.append("\n// Flags\n")
        for f in self.vk.bitmasks.values():
            out.extend(guarder.add_guard(f.protect))
            out.append(f"std::string On_Str_{f.flagName}({f.flagName} f);\n")
        out.extend(guarder.add_guard(None))
        out.append("\n")

        out.append("\n".join([RBracket] * len(self.namespaces)))
        self.write("".join(out))

    def generate_source(self):
        out = []
        out.append(f'#include "{self.include}"\n\n')
        out.append("\n".join(map(lambda ns: f"namespace {ns} {LBracket}", self.namespaces)))

        guarder = PlatformGuardHelper()
        out.append("\n\n// Enums\n")
        for e in self.vk.enums.values():
            out.extend(guarder.add_guard(e.protect, True))
            out.append(f"std::string On_Str_{e.name}({e.name} e) {LBracket}\n")
            out.append(f'    std::string str = "Unknown " + std::to_string(e);\n')
            out.append(f"    switch(e) {LBracket}\n")
            subguarder = PlatformGuardHelper()
            for v in e.fields:
                out.extend(subguarder.add_guard(v.protect))
                out.append(f'    case {v.name}: str = "{trim(e.name, v.name)}"; break;\n')
            out.extend(subguarder.add_guard(None))
            out.append(f"    default: break;\n")
            out.append(f"    {RBracket}\n")
            out.append(f"    return std::move(str);\n")
            out.append(f"{RBracket}\n")
        out.extend(guarder.add_guard(None))

        guarder = PlatformGuardHelper()
        out.append("\n// Flags\n")
        for f in self.vk.bitmasks.values():
            out.extend(guarder.add_guard(f.protect, True))
            out.append(f"std::string On_Str_{f.flagName}({f.flagName} f) {LBracket}\n")
            out.append(f'    std::string str = "";\n')
            subguarder = PlatformGuardHelper()
            for v in f.flags:
                out.extend(subguarder.add_guard(v.protect))
                out.append(f"    if (f & {v.name}) {LBracket}\n")
                out.append(f'        str += "|{trim(f.flagName, v.name)}";\n')
                out.append(f"    {RBracket}\n")
            out.extend(subguarder.add_guard(None))
            out.append(f'    str += "|";\n')
            out.append(f"    return std::move(str);\n")
            out.append(f"{RBracket}\n")
        out.extend(guarder.add_guard(None))

        out.append("\n".join([RBracket] * len(self.namespaces)))
        self.write("".join(out))
