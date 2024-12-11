#pragma once
#include "__api.hpp"
#include "instance.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Surface : public CoreHandle<VkSurfaceKHR> {
    const VkAllocationCallbacks* allocator = nullptr;
    const VkInstance instance;

protected:
    explicit Surface(const Instance& instance) : allocator(instance.allocator), instance(instance) {}

public:
    Surface(Surface&&);
    Surface& operator=(Surface&&);
    ~Surface();

    /**
     * @brief A simple way to create core::Surface from VkSurfaceKHR
     *
     * Be attention that the VkSurfaceKHR's ownership will transfer to the created core::Surface
     */
    static Res<Surface> from(const Instance& instance, VkSurfaceKHR& surface);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
