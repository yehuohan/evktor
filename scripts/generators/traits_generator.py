#!/usr/bin/env python3

from base_generator import BaseGenerator
from generators.generator_utils import PlatformGuardHelper

LBracket = "{"
RBracket = "}"
BaseTraits = """
struct HasInstance {
protected:
    VkInstance __parent;

public:
    HasInstance(VkInstance p = VK_NULL_HANDLE) : __parent(p) {}
    VkInstance parent() const {
        return __parent;
    }
};

struct HasPhysicalDevice {
protected:
    VkPhysicalDevice __parent;

public:
    HasPhysicalDevice(VkPhysicalDevice p = VK_NULL_HANDLE) : __parent(p) {}
    VkPhysicalDevice parent() const {
        return __parent;
    }
};

struct HasDevice {
protected:
    VkDevice __parent;

public:
    HasDevice(VkDevice p = VK_NULL_HANDLE) : __parent(p) {}
    VkDevice parent() const {
        return __parent;
    }
};

template <typename H> struct vk_child_of_instance : public std::false_type {};
template <typename H> struct vk_child_of_physical_device : public std::false_type {};
template <typename H> struct vk_child_of_device : public std::false_type {};

template <typename H> constexpr bool vk_child_of_instance_v = vk_child_of_instance<H>::value;
template <typename H> constexpr bool vk_child_of_physical_device_v = vk_child_of_physical_device<H>::value;
template <typename H> constexpr bool vk_child_of_device_v = vk_child_of_device<H>::value;
template <typename H> constexpr bool vk_has_parent_v = vk_child_of_instance_v<H> || vk_child_of_physical_device_v<H> || vk_child_of_device_v<H>;

template <typename H> using vk_parent_instance_t = typename std::conditional<vk_child_of_instance_v<H>, VkInstance, std::monostate>::type;
template <typename H> using vk_parent_physical_device_t = typename std::conditional<vk_child_of_physical_device_v<H>, VkPhysicalDevice, std::monostate>::type;
template <typename H> using vk_parent_device_t = typename std::conditional<vk_child_of_device_v<H>, VkDevice, std::monostate>::type;
template <typename H> using vk_parent_t = typename std::conditional<vk_child_of_device_v<H>, VkDevice,
    typename std::conditional<vk_child_of_physical_device_v<H>, VkPhysicalDevice,
        typename std::conditional<vk_child_of_instance_v<H>, VkInstance, std::monostate>::type
    >::type
>::type;

template <typename H> using vk_parent_instance_s = typename std::conditional<vk_child_of_instance_v<H>, HasInstance, std::monostate>::type;
template <typename H> using vk_parent_physical_device_s = typename std::conditional<vk_child_of_physical_device_v<H>, HasPhysicalDevice, std::monostate>::type;
template <typename H> using vk_parent_device_s = typename std::conditional<vk_child_of_device_v<H>, HasDevice, std::monostate>::type;
template <typename H> using vk_parent_s = typename std::conditional<vk_child_of_device_v<H>, HasDevice,
    typename std::conditional<vk_child_of_physical_device_v<H>, HasPhysicalDevice,
        typename std::conditional<vk_child_of_instance_v<H>, HasInstance, std::monostate>::type
    >::type
>::type;
"""


class TraitsGenerator(BaseGenerator):
    def __init__(self, namespaces):
        BaseGenerator.__init__(self)
        self.namespaces = namespaces

    def generate(self):
        out = []
        out.append("#pragma once\n\n")
        out.append("#include <type_traits>\n")
        out.append("#include <variant>\n")
        out.append("#include <vulkan/vulkan.h>\n\n")
        out.append("\n".join(map(lambda ns: f"namespace {ns} {LBracket}", self.namespaces)))
        out.append("\n\n")

        out.append("// clang-format off")
        out.append(BaseTraits)
        out.append("\n")

        c2p = {}
        for h in [x for x in self.vk.handles.values() if x.parent]:
            c2p[h.name] = h.parent

        def append(guarder, h, p):
            if p.name == "VkInstance":
                out.extend(guarder.add_guard(h.protect))
                out.append(f"template <> struct vk_child_of_instance<{h.name}> : public std::true_type {{}};\n")
            elif p.name == "VkPhysicalDevice":
                out.extend(guarder.add_guard(h.protect))
                out.append(f"template <> struct vk_child_of_physical_device<{h.name}> : public std::true_type {{}};\n")
            elif p.name == "VkDevice":
                out.extend(guarder.add_guard(h.protect))
                out.append(f"template <> struct vk_child_of_device<{h.name}> : public std::true_type {{}};\n")
            elif p.name in c2p:
                append(guarder, h, c2p[h.parent.name])

        guarder = PlatformGuardHelper()
        for h in [x for x in self.vk.handles.values() if x.parent]:
            append(guarder, h, h.parent)
        out.extend(guarder.add_guard(None))
        out.append("// clang-format on\n")
        out.append("\n")

        out.append("\n".join([RBracket] * len(self.namespaces)))
        self.write("".join(out))
