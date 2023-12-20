#define VOLK_IMPLEMENTATION
#include "vktor.hpp"

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

NAMESPACE_BEGIN(vkt)

using namespace core;

void Vktor::addRenderContext() {
    render_context = newBox<RenderContext>(api);
}

NAMESPACE_END(vkt)
