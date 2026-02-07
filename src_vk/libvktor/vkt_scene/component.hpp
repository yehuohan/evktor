#pragma once
#include "share/share.hpp"
#include "share/traits.hpp"
#include <typeindex>

NAMESPACE_BEGIN(vktscn)

class Component : private NonCopyable {
public:
    Component() = default;
    Component(const String& name) : name(name) {}
    virtual ~Component() = default;

    const String& getName() const {
        return name;
    }
    virtual std::type_index getType() const = 0;

private:
    String name{""};
};

NAMESPACE_END(vktscn)
