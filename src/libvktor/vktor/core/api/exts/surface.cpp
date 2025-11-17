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
    Surface surface(instance);
    surface.handle = _surface;
    _surface = VK_NULL_HANDLE;
    if (!surface.handle) {
        return Er("Get an invalid VkSurfaceKHR");
    }
    return Ok(std::move(surface));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
