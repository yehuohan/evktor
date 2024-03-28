#pragma once
#include "__core.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Event;

class EventState : public CoreStater<EventState> {
    friend struct Event;

private:
    VkEventCreateInfo event_ci{};

public:
    explicit EventState(Name&& name = "Event") : CoreStater(std::move(name)) {
        event_ci = Itor::EventCreateInfo();
    }

    Self setFlags(VkEventCreateFlags flags);

    Res<Event> into(const Device& device) const;
};

struct Event : public CoreResource<VkEvent, VK_OBJECT_TYPE_EVENT, Device> {
protected:
    explicit Event(const Device& device) : CoreResource(device) {}

public:
    Event(Event&&);
    ~Event();

    static Res<Event> from(const Device& device, const EventState& info);
};

class EventPool : public NonCopyable {
private:
    Vector<Event> events{};
    uint32_t active_count = 0;

public:
    const Device& device;

    explicit EventPool(const Device& device) : device(device) {}
    EventPool(EventPool&&);
    ~EventPool();

    Res<Ref<Event>> request();
    void resetPool();
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
