#include "__helpers.hpp"
#include <vktor.hpp>

using namespace vkt;
using namespace vkt::core;

void check(const CoreApi& api,
           const Instance& instance,
           const PhysicalDevice& phy_dev,
           const Device& device,
           const Debug& debug)

{
    Vector<VkInstance> vec_instance{(VkInstance)api,
                                    ((const Instance&)api).handle,
                                    ((const PhysicalDevice&)api).instance.get().handle,
                                    ((const Device&)api).physical_device.get().instance.get().handle,
                                    instance.handle,
                                    debug.instance.get().handle,
                                    phy_dev.instance.get().handle,
                                    device.physical_device.get().instance.get().handle};
    Vector<VkPhysicalDevice> vec_phy_dev{
        (VkPhysicalDevice)api,
        ((const PhysicalDevice&)api).handle,
        ((const Device&)api).physical_device.get().handle,
        phy_dev.handle,
        device.physical_device.get().handle,
    };
    Vector<VkDevice> vec_dev{
        (VkDevice)api,
        ((const Device&)api).handle,
        device.handle,
    };
    for (size_t k = 1; k < vec_instance.size(); k++) {
        assert(vec_instance[0] == vec_instance[k]);
    }
    for (size_t k = 1; k < vec_phy_dev.size(); k++) {
        assert(vec_phy_dev[0] == vec_phy_dev[k]);
    }
    for (size_t k = 1; k < vec_dev.size(); k++) {
        assert(vec_dev[0] == vec_dev[k]);
    }

    tstOut("\tInstance: {}", fmt::ptr(vec_instance[0]));
    tstOut("\tPhysical Device: {}", fmt::ptr(vec_phy_dev[0]));
    tstOut("\tDevice: {}", fmt::ptr(vec_dev[0]));
    tstOut("\tDebug: {}", fmt::ptr(debug.handle));
}

void case_core_api() {
    CoreApi api;
    {
        DebugState dso{};
        dso.setMessageSeverity(false, false);
        auto& instance = api.init(InstanceState().setNext(dso).enableExtensionDebugUtils()).unwrap().get();
        auto& idebug = api.add(dso).unwrap().get();
        auto& debug = *dynamic_cast<const Debug*>(&idebug);
        auto& phy_dev = api.init(PhysicalDeviceState().preferDiscreteGPU().requireGraphicsQueue()).unwrap().get();
        auto& device = api.init(DeviceState().setMaxQueueCount(1)).unwrap().get();
        tstOut("Check inited:");
        check(api, instance, phy_dev, device, debug);
    }

    CoreApi api_;
    {
        DebugState dso{};
        dso.setMessageSeverity(false, false);
        auto& instance = api_.borrow((VkInstance)api, vkGetInstanceProcAddr).unwrap().get();
        auto& idebug = api_.add(dso).unwrap().get();
        auto& debug = *dynamic_cast<const Debug*>(&idebug);
        auto& phy_dev = api_.borrow((VkPhysicalDevice)api).unwrap().get();
        auto& device = api_.borrow((VkDevice)api, vkGetDeviceProcAddr).unwrap().get();
        tstOut("Check borrowed:");
        check(api_, instance, phy_dev, device, debug);
    }
}
