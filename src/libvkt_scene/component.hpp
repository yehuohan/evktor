#pragma once
#include <memory>
#include <share/share.hpp>
#include <typeindex>

NAMESPACE_BEGIN(vktscn)

class Component {
public:
    Component() = default;
    Component(const vkt::Name& name);
    Component(Component&& other) = default;
    virtual ~Component() = default;

    const vkt::String& getName() const;
    virtual std::type_index getType() = 0;

private:
    vkt::Name name;
};

NAMESPACE_END(vktscn)
