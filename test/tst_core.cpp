#include <iostream>
#include <vktor.hpp>

using namespace vkt;
using namespace vkt::core;

int main(int argc, char* argv[]) {
    vktOut("tst_core");

    CoreApiState aso{};

    // Create instance
    DebugState dso{};
    aso.init(InstanceState()
                 .setAppName("tst_core")
                 .setAppVerion(VK_MAKE_VERSION(1, 0, 0))
                 .setEngineName("vktor")
                 .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
                 .setApiVerion(VK_API_VERSION_1_2)
                 .enableLayerValidation()
                 .enableExtensionDebugUtils(&dso)
                 .setVerbose(true))
        .unwrap();

    // Select physical device
    aso.init(PhysicalDeviceState()
                 .preferDiscreteGPU()
                 // .preferIntegratedGPU()
                 .requireGraphicsQueue()
                 .requireComputeQueue()
                 .setVerbose(true))
        .unwrap();

    // Create device
    aso.init(DeviceState().setMaxQueueCount(1).setVerbose(true)).unwrap();

    // Create core api
    vkt::Box<vkt::core::CoreApi> api = newBox<vkt::core::CoreApi>(aso.into().unwrap());

    vktOut("Instance: {}, Physical Device: {}, Device: {}",
           fmt::ptr((VkInstance)*api),
           fmt::ptr((VkPhysicalDevice)*api),
           fmt::ptr((VkDevice)*api));
}
