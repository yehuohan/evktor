#include "surface.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

Surface::Surface(Surface&& rhs) : instance(rhs.instance) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

Surface::~Surface() {
    if (!__borrowed && handle) {
        vkDestroySurfaceKHR(instance.get(), handle, instance.get());
    }
    handle = VK_NULL_HANDLE;
}

Surface& Surface::operator=(Surface&& rhs) {
    if (this != &rhs) {
        if (!__borrowed && handle) {
            vkDestroySurfaceKHR(instance.get(), handle, instance.get());
        }

        handle = rhs.handle;
        rhs.handle = VK_NULL_HANDLE;
        __borrowed = rhs.__borrowed;
    }
    return *this;
}

Res<Surface> Surface::from(CRef<Instance> instance, VkSurfaceKHR& _surface) {
    if (!_surface) {
        return Er("From an invalid VkSurfaceKHR");
    }

    Surface surface(instance);
    surface.__borrowed = false;
    surface.handle = _surface;
    _surface = VK_NULL_HANDLE;
    return Ok(std::move(surface));
}

Res<Surface> Surface::borrow(CRef<Instance> instance, const VkSurfaceKHR& _surface) {
    Surface surface(instance);
    surface.__borrowed = true;
    surface.handle = _surface;
    return Ok(std::move(surface));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
