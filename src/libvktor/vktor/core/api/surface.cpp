#include "surface.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

Surface::Surface(Surface&& rhs) : instance(rhs.instance) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

Surface& Surface::operator=(Surface&& rhs) {
    if (this != &rhs) {
        handle = rhs.handle;
        rhs.handle = VK_NULL_HANDLE;
        __borrowed = rhs.__borrowed;
    }
    return *this;
}

Surface::~Surface() {
    if (!__borrowed && handle) {
        vkDestroySurfaceKHR(instance, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<Surface> Surface::from(const Instance& instance, VkSurfaceKHR _surface) {
    Surface surface(instance);
    surface.handle = _surface;
    return Ok(std::move(surface));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
