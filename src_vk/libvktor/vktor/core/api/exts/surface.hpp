#pragma once
#include "../__api.hpp"
#include "../instance.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Surface : public CoreHandle<VkSurfaceKHR> {
    CRef<Instance> instance;

protected:
    explicit Surface(CRef<Instance> instance) : instance(instance) {}
    explicit Surface(CRef<Instance> instance, VkHandle<VkSurfaceKHR> h) : CoreHandle(h), instance(instance) {}

public:
    Surface(Surface&& rhs) : CoreHandle(std::move(rhs)), instance(rhs.instance) {}
    ~Surface();
    Surface& operator=(Surface&&);

    /**
     * @brief A simple way to create core::Surface from a created VkSurfaceKHR
     *
     * Be attention that the VkSurfaceKHR's ownership will transfer to the created core::Surface
     */
    static Res<Surface> from(CRef<Instance> instance, VkHandle<VkSurfaceKHR> surface);
    /**
     * @brief Borrow VkSurfaceKHR as core::Surface
     */
    static Res<Surface> borrow(CRef<Instance> instance, VkHandle<VkSurfaceKHR> handle);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
