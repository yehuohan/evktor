#!/usr/bin/env python3

from generators.base_generator import BaseGenerator

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
        out.extend("\n".join(map(lambda ns: f"namespace {ns} {LBracket}", self.namespaces)))
        out.append("\n\n")

        for s in self.vk.structs.values():
            if s.members[0].name == "sType" and s.sType != None:
                name = s.name
                if s.protect:
                    out.append(f"#ifdef {s.protect}\n")
                out.append(f"inline {name} {name[2:]}() {LBracket}\n")
                out.append(f"    {name} info{{}};\n")
                out.append(f"    info.sType = {s.sType};\n")
                out.append(f"    return info;\n")
                out.append(f"{RBracket}\n")
                if s.protect:
                    out.append(f"#endif // {s.protect}\n")
                out.append("\n")

        out.extend("\n".join([RBracket] * len(self.namespaces)))
        self.write("".join(out))
