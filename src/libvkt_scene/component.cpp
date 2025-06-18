#include "component.hpp"

NAMESPACE_BEGIN(vktscn)

Component::Component(const std::string& name) : name{name} {}

const std::string& Component::getName() const {
    return name;
}

NAMESPACE_END(vktscn)
