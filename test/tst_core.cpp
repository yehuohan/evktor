#include "__helpers.hpp"
#include <iostream>
#include <vktor.hpp>

using namespace vkt;
using namespace vkt::core;

static const std::string filename = "./glsl/test/quad.comp";

Box<CoreApi> setupCoreApi() {
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
    Box<CoreApi> api = newBox<CoreApi>(aso.into().unwrap());

    vktOut("Instance: {}, Physical Device: {}, Device: {}",
           fmt::ptr((VkInstance)*api),
           fmt::ptr((VkPhysicalDevice)*api),
           fmt::ptr((VkDevice)*api));

    return std::move(api);
}

void setupComputePass(const CoreApi& api) {
    ShaderSource shader_source = ShaderSource::from(ShaderSource::Comp, read_shader(filename)).unwrap();
    Shader shader = Shader::from(shader_source).unwrap();

    DescriptorSetLayoutState dslso{};
    dslso.addCompBinding(0, VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);
    dslso.addCompBinding(1, VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);
    auto dsl = dslso.into(api).unwrap();

    PipelineLayoutState plso{};
    plso.addDescriptorSetLayout(dsl);
    auto pl = plso.into(api).unwrap();

    ComputePipelineState pso{};
    pso.setShader(shader.into(api).unwrap()).setPipelineLayout(pl);
    auto p = pso.into(api).unwrap();

    vktOut("Pipeline: {}", fmt::ptr((VkPipeline)p));
}

int main(int argc, char* argv[]) {
    vktOut(">>> tst_core");

    auto api = setupCoreApi();
    setupComputePass(*api);
}
