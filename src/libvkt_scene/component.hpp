#pragma once
#include <memory>
#include <share/share.hpp>
#include <typeindex>

NAMESPACE_BEGIN(vktscn)

class Component {
public:
    Component() = default;
    Component(const String& name) : name(name) {}
    Component(Component&& other) = default;
    virtual ~Component() = default;

    operator const String&() const {
        return name;
    }
    virtual operator std::type_index() = 0;

private:
    String name{""};
};

NAMESPACE_END(vktscn)
