#include "vktor.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

core::CoreApi& Vktor::createApi(std::function<void(core::InstanceState&)> update_inst,
                                std::function<VkSurfaceKHR(const core::Instance& instance)> create_surface,
                                std::function<void(const core::Instance&, core::PhysicalDeviceState&)> update_phydev,
                                std::function<void(const core::PhysicalDevice&, core::DeviceState&)> update_dev) {
    api = newBox<CoreApi>();
    DebugState dso{};
    dso.setMessageSeverity(false, false);

    // Create instance
    InstanceState inst_stt{};
    inst_stt.setNext(dso)
        .setAppName("evktor")
        .setAppVerion(VK_MAKE_VERSION(1, 0, 0))
        .setEngineName("vktor")
        .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
        .tryAddValidationLayer()
        .tryAddDebugUtilsExtension()
        .setVerbose(false);
    if (update_inst) {
        update_inst(inst_stt);
    }
    api->init(inst_stt).unwrap();

    // Enable extensions
    api->add(dso).unwrap();
    Vector<const char*> exts{};
    if (create_surface) {
        api->add(create_surface(*api), true);
        exts.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

    // Select physical device
    PhysicalDeviceState phydev_stt{};
    phydev_stt.preferDiscreteGPU()
        .requirePresentQueue(*api, create_surface ? true : false)
        .requireGraphicsQueue()
        .requireComputeQueue()
        .requireTransferQueue()
        .setVerbose(true);
    if (update_phydev) {
        update_phydev(*api, phydev_stt);
    }
    api->init(phydev_stt).unwrap();

    // Create device
    DeviceState dev_stt{};
    dev_stt.setMaxQueueCount(1).addExtensions(exts).enableDynamicRenderingFeature().setVerbose(false);
    if (update_dev) {
        update_dev(*api, dev_stt);
    }
    api->init(dev_stt).unwrap();

    return *api;
}

NAMESPACE_END(vkt)
