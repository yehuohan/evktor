#pragma once
#include "__core.hpp"
#include "instance.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Surface : public CoreHandle<VkSurfaceKHR> {
    const Instance& instance;

protected:
    explicit Surface(const Instance& instance) : instance(instance) {}

public:
    Surface(Surface&&);
    Surface& operator=(Surface&&);
    ~Surface();

    /**
     * @brief A simple way to create core::Surface from VkSurfaceKHR
     *
     * Be attention that the VkSurfaceKHR's ownership will transfer to the created core::Surface
     */
    static Res<Surface> from(const Instance& instance, VkSurfaceKHR surface);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
