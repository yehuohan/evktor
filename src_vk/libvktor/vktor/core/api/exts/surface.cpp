#include "surface.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

Surface::~Surface() {
    if (!borrowed() && __handle) {
        vkDestroySurfaceKHR(instance.get(), __handle, instance.get());
    }
    __handle = VK_NULL_HANDLE;
}

Surface& Surface::operator=(Surface&& rhs) {
    if (this != &rhs) {
        if (!borrowed() && __handle) {
            vkDestroySurfaceKHR(instance.get(), __handle, instance.get());
        }
        moveFrom(std::move(rhs));
    }
    return *this;
}

Res<Surface> Surface::from(CRef<Instance> instance, VkHandle<VkSurfaceKHR> _surface) {
    if (!_surface.valid()) {
        return Er("From constructor requires a valid VkHandle for VkSurfaceKHR");
    }

    Surface surface(instance);
    surface.__handle = _surface;
    return Ok(std::move(surface));
}

Res<Surface> Surface::borrow(CRef<Instance> instance, VkHandle<VkSurfaceKHR> handle) {
    if (!handle.valid()) {
        return Er("Borrow requires a valid VkHandle for VkSurfaceKHR");
    }
    return Ok(Surface(instance, handle));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
