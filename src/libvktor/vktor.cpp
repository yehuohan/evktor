#include "vktor.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

core::CoreApi& Vktor::createApi(const Vector<const char*>& inst_exts,
                                const Vector<const char*>& dev_exts,
                                std::function<VkSurfaceKHR(const core::Instance& instance)> create_surface) {
    api = newBox<CoreApi>();
    DebugState dso{};
    dso.setMessageSeverity(false, false);

    // Create instance
    api->init(InstanceState()
                  .setNext(dso)
                  .setAppName("evktor")
                  .setAppVerion(VK_MAKE_VERSION(1, 0, 0))
                  .setEngineName("vktor")
                  .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
                  .addValidationLayer()
                  .addDebugUtilsExtension()
                  .addExtensions(inst_exts)
                  .setVerbose(false))
        .unwrap();

    // Enable extensions
    api->add(dso).unwrap();
    Vector<const char*> exts{};
    if (create_surface) {
        api->add(create_surface(*api), true);
        exts.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

    // Select physical device
    api->init(PhysicalDeviceState()
                  .preferDiscreteGPU()
                  .requirePresentQueue(*api, create_surface ? true : false)
                  .requireGraphicsQueue()
                  .requireComputeQueue()
                  .requireTransferQueue()
                  .setVerbose(true))
        .unwrap();

    // Create device
    api->init(DeviceState()
                  .setMaxQueueCount(1)
                  .addExtensionsForVMA()
                  .addExtensions(exts)
                  .addExtensions(dev_exts)
                  .enableDynamicRenderingFeature()
                  .setVerbose(false))
        .unwrap();

    return *api;
}

NAMESPACE_END(vkt)
