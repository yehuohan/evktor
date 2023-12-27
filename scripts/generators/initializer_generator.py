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
            if s.members[0].name == "sType" and s.sType != None:
                name = s.name
                out.extend(guarder.add_guard(s.protect, True))
                out.append(f"inline {name} {name[2:]}() {LBracket}\n")
                out.append(f"    {name} info{{}};\n")
                out.append(f"    info.sType = {s.sType};\n")
                out.append(f"    return info;\n")
                out.append(f"{RBracket}\n")
        out.extend(guarder.add_guard(None))
        out.append("\n")

        out.append("\n".join([RBracket] * len(self.namespaces)))
        self.write("".join(out))
