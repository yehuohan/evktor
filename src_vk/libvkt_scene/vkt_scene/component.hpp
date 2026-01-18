#pragma once
#include <share/share.hpp>
#include <share/traits.hpp>
#include <typeindex>

NAMESPACE_BEGIN(vktscn)

class Component : public NonCopyable {
public:
    Component() = default;
    Component(const String& name) : name(name) {}
    Component(Component&& rhs) : name(std::move(rhs.name)) {}
    virtual ~Component() = default;

    const std::string& getName() const {
        return name;
    }
    virtual std::type_index getType() const = 0;

private:
    String name{""};
};

NAMESPACE_END(vktscn)
