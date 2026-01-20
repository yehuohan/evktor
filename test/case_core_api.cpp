#include "__helpers.hpp"

void testCoreApi() {
    auto check = [](const CoreApi& api,
                    const Instance& instance,
                    const PhysicalDevice& phy_dev,
                    const Device& device,
                    const Debug& debug)

    {
        Vector<VkInstance> vec_instance{(VkInstance)api,
                                        ((const Instance&)api).getHandle(),
                                        ((const PhysicalDevice&)api).instance.get().getHandle(),
                                        ((const Device&)api).physical_device.get().instance.get().getHandle(),
                                        instance.getHandle(),
                                        debug.instance.get().getHandle(),
                                        phy_dev.instance.get().getHandle(),
                                        device.physical_device.get().instance.get().getHandle()};
        Vector<VkPhysicalDevice> vec_phy_dev{
            (VkPhysicalDevice)api,
            ((const PhysicalDevice&)api).getHandle(),
            ((const Device&)api).physical_device.get().getHandle(),
            phy_dev.getHandle(),
            device.physical_device.get().getHandle(),
        };
        Vector<VkDevice> vec_dev{
            (VkDevice)api,
            ((const Device&)api).getHandle(),
            device.getHandle(),
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
        tstOut("\tDebug: {}", fmt::ptr(debug.getHandle()));
    };

    CoreApi api;
    {
        DebugState dso{};
        dso.setMessageSeverity(false, false);
        auto& instance = api.init(InstanceState().setNext(dso).tryAddDebugUtilsExtension()).unwrap().get();
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

void testNextState() {
    NextState nso{Itor::InstanceCreateInfo(),
                  Itor::PhysicalDeviceFeatures2(),
                  Itor::DeviceCreateInfo(),
                  Itor::DeviceQueueInfo2()};
    auto cmdbuf_ai = Itor::CommandBufferAllocateInfo();

    nso.get<0>().enabledLayerCount = 123;
    nso.get<VkDeviceCreateInfo>().enabledLayerCount = 321;

    const VkBaseInStructure* ptr = (VkBaseInStructure*)nso.into(&cmdbuf_ai);
    assert(ptr->sType == VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO);
    assert(ptr == (const VkBaseInStructure*)&nso.get<0>());
    assert(((VkInstanceCreateInfo*)ptr)->enabledLayerCount == 123);

    ptr = ptr->pNext;
    assert(ptr->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2);
    assert(ptr == (const VkBaseInStructure*)&nso.get<1>());

    ptr = ptr->pNext;
    assert(ptr->sType == VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO);
    assert(ptr == (const VkBaseInStructure*)&nso.get<VkDeviceCreateInfo>());
    assert(((VkDeviceCreateInfo*)ptr)->enabledLayerCount == 321);

    ptr = ptr->pNext;
    assert(ptr->sType == VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2);
    assert(ptr == (const VkBaseInStructure*)&nso.get<VkDeviceQueueInfo2>());

    ptr = ptr->pNext;
    assert(ptr->sType == VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO);
}

void case_core_api() {
    testCoreApi();
    testNextState();
}
