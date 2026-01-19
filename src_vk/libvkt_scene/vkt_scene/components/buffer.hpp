#pragma once
#include "../component.hpp"
#include <vktor/core/buffer.hpp>

NAMESPACE_BEGIN(vktscn)

class Buffer : public Component {
private:
    vkt::core::Buffer buffer;

public:
    Buffer(vkt::core::Buffer&& buffer, const String& name = "") : Component(name), buffer(std::move(buffer)) {}
    virtual ~Buffer() = default;

    OnConstType(VkBuffer, buffer.handle);

    virtual std::type_index getType() const override {
        return typeid(Buffer);
    }
};

struct SubBuffer {
    SubBuffer() = default;
    SubBuffer(const Buffer& buffer, VkDeviceSize offset) : buffer(&buffer), offset(offset) {}

    operator VkBuffer() const {
        assert(buffer);
        return (VkBuffer)*buffer;
    }

    const Buffer* buffer = nullptr;
    VkDeviceSize offset = 0;
};

NAMESPACE_END(vktscn)
