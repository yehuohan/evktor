#!/usr/bin/env python3

from generators.base_generator import BaseGenerator
from generators.generator_utils import PlatformGuardHelper

LBracket = "{"
RBracket = "}"


class InitializerGenerator(BaseGenerator):
    def __init__(self, namespaces):
        BaseGenerator.__init__(self)
        self.namespaces = namespaces

    def generate(self):
        out = []
        out.append("#pragma once\n\n")
        out.append("#include <vulkan/vulkan.h>\n\n")
        out.append("\n".join(map(lambda ns: f"namespace {ns} {LBracket}", self.namespaces)))
        out.append("\n\n")

        guarder = PlatformGuardHelper()
        for s in self.vk.structs.values():
            num = len(s.members)
            if num >= 1 and s.members[0].name == "sType" and s.sType != None:
                name = s.name
                args = ""
                exts = []
                if num >= 2 and s.members[1].name == "pNext":
                    args = "const void* next = nullptr" if s.members[1].const else "void* next = nullptr"
                    exts = "    info.pNext = next;\n"
                out.extend(guarder.add_guard(s.protect, True))
                out.append(f"inline {name} {name[2:]}({args}) {LBracket}\n")
                out.append(f"    {name} info{{}};\n")
                out.append(f"    info.sType = {s.sType};\n")
                out.extend(exts)
                out.append(f"    return info;\n")
                out.append(f"{RBracket}\n")
        out.extend(guarder.add_guard(None))
        out.append("\n")

        out.append("\n".join([RBracket] * len(self.namespaces)))
        self.write("".join(out))
