#!/usr/bin/env python3

from generators.base_generator import BaseGenerator
from generators.generator_utils import PlatformGuardHelper

LBracket = "{"
RBracket = "}"


class LDTGenerator(BaseGenerator):
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
        out.append(
            "typedef PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, const char* pName);\n\n"
        )
        out.append(f"// Instance dispatch table\n")
        out.append(f"typedef struct VkLayerInstanceDispatchTable {LBracket}\n")
        out.append(f"PFN_GetPhysicalDeviceProcAddr GetPhysicalDeviceProcAddr;\n")
        for c in [x for x in self.vk.commands.values() if x.instance]:
            out.extend(guarder.add_guard(c.protect))
            out.append(f"    PFN_{c.name} {c.name[2:]};\n")
        out.extend(guarder.add_guard(None))
        out.append(f"{RBracket} VkLayerInstanceDispatchTable;\n\n")

        guarder = PlatformGuardHelper()
        out.append(f"// Device dispatch table\n")
        out.append(f"typedef struct VkLayerDispatchTable {LBracket}\n")
        for c in [x for x in self.vk.commands.values() if x.device]:
            out.extend(guarder.add_guard(c.protect))
            out.append(f"    PFN_{c.name} {c.name[2:]};\n")
        out.extend(guarder.add_guard(None))
        out.append(f"{RBracket} VkLayerDispatchTable;\n\n")

        out.append("\n".join([RBracket] * len(self.namespaces)))
        self.write("".join(out))
