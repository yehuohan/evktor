#include "__helpers.hpp"
#include <vktor.hpp>

using namespace vkt;
using namespace vkt::core;

extern Box<CoreApi> setupCoreApi(const Vector<const char*> instance_exts = {}, const Vector<const char*> device_exts = {});

void case_core_memory() {
    auto api = setupCoreApi({},
                            {
                                VK_KHR_EXTERNAL_MEMORY_EXTENSION_NAME,
#ifdef VK_USE_PLATFORM_WIN32_KHR
                                VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME,
#else
                                VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME,
#endif
                            });

#ifdef VK_USE_PLATFORM_WIN32_KHR
    auto hdl_type = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;
#else
    auto hdl_type = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;
#endif
    {
        BufferState bso{};
        bso.setSize(0x1000); // 随便填个buffer size
        DeviceMemoryPoolState mpso{};
        mpso.setExternalHandleType(hdl_type);
        auto mem_pool = mpso.into(*api, bso).unwrap();
        bso.setMemoryPool(&mem_pool);
        auto buf = bso.into(*api).unwrap();

#ifdef VK_USE_PLATFORM_WIN32_KHR
        HANDLE hdl = nullptr;
        buf.getWin32Handle(hdl);
        assert(hdl);
        tstOut("Buffer handle: {}", hdl);
#else
        int fd;
        buf.getFd(fd);
        assert(fd > -1);
        tstOut("Buffer fd: {}", fd);
#endif
    }

    {
        ImageState iso{};
        iso.setFormat(VK_FORMAT_R32G32B32A32_SFLOAT);
        iso.setExtent(1920, 1080); // 随便填个image extent
        DeviceMemoryPoolState mpso{};
        mpso.setExternalHandleType(hdl_type);
        auto mem_pool = mpso.into(*api, iso).unwrap();
        iso.setMemoryPool(&mem_pool);
        auto img = iso.into(*api).unwrap();

#ifdef VK_USE_PLATFORM_WIN32_KHR
        HANDLE hdl;
        img.getWin32Handle(hdl);
        assert(hdl);
        tstOut("Image handle: {}", hdl);
#else
        int fd = -1;
        img.getFd(fd);
        assert(fd > -1);
        tstOut("Image fd: {}", fd);
#endif
    }
}
