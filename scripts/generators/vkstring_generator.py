#!/usr/bin/env python3

import re
from generators.base_generator import BaseGenerator

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


class VkStringGenerator(BaseGenerator):
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
        out.extend("\n".join(map(lambda ns: f"namespace {ns} {LBracket}", self.namespaces)))

        out.append("\n// Enums\n")
        for e in self.vk.enums.values():
            if e.protect:
                out.append(f"#ifdef {e.protect}\n")
            out.append(f"std::string On_Str_{e.name}({e.name} e);\n")
            if e.protect:
                out.append(f"#endif // {e.protect}\n")

        out.append("\n// Flags\n")
        for f in self.vk.bitmasks.values():
            if f.protect:
                out.append(f"#ifdef {f.protect}\n")
            out.append(f"std::string On_Str_{f.flagName}({f.flagName} f);\n")
            if f.protect:
                out.append(f"#endif // {f.protect}\n")

        out.extend("\n".join([RBracket] * len(self.namespaces)))
        self.write("".join(out))

    def generate_source(self):
        out = []
        out.append(f'#include "{self.include}"\n\n')
        out.extend("\n".join(map(lambda ns: f"namespace {ns} {LBracket}", self.namespaces)))

        out.append("\n\n// Enums\n")
        for e in self.vk.enums.values():
            if e.protect:
                out.append(f"#ifdef {e.protect}\n")
            out.append(f"std::string On_Str_{e.name}({e.name} e) {LBracket}\n")
            out.append(f'    std::string str = "Unknown " + std::to_string(e);\n')
            out.append(f"    switch(e) {LBracket}\n")
            for v in e.fields:
                if v.protect:
                    out.append(f"#ifdef {v.protect}\n")
                out.append(f'    case {v.name}: str = "{trim(e.name, v.name)}"; break;\n')
                if v.protect:
                    out.append(f"#endif // {v.protect}\n")
            out.append(f"    default: break;\n")
            out.append(f"    {RBracket}\n")
            out.append(f"    return std::move(str);\n")
            out.append(f"{RBracket}\n")
            if e.protect:
                out.append(f"#endif // {e.protect}\n")
            out.append("\n")

        out.append("\n// Flags\n")
        for f in self.vk.bitmasks.values():
            if f.protect:
                out.append(f"#ifdef {f.protect}\n")
            out.append(f"std::string On_Str_{f.flagName}({f.flagName} f) {LBracket}\n")
            out.append(f'    std::string str = "";\n')
            for v in f.flags:
                if v.protect:
                    out.append(f"#ifdef {v.protect}\n")
                out.append(f"    if (f & {v.name}) {LBracket}\n")
                out.append(f'        str += "|{trim(f.flagName, v.name)}";\n')
                out.append(f"    {RBracket}\n")
                if v.protect:
                    out.append(f"#endif // {v.protect}\n")
            out.append(f'    str += "|";\n')
            out.append(f"    return std::move(str);\n")
            out.append(f"{RBracket}\n")
            if f.protect:
                out.append(f"#endif // {f.protect}\n")
            out.append("\n")

        out.extend("\n".join([RBracket] * len(self.namespaces)))
        self.write("".join(out))
