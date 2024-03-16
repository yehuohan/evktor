#include "event.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = EventState::Self;

Self EventState::setFlags(VkEventCreateFlags flags) {
    event_ci.flags = flags;
    return *this;
}

Res<Event> EventState::into(const Device& device) const {
    return Event::from(device, *this);
}

Event::Event(Event&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

Event::~Event() {
    if (handle) {
        vkDestroyEvent(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<Event> Event::from(const Device& device, const EventState& info) {
    Event event(device);

    OnRet(vkCreateEvent(device, &info.event_ci, nullptr, event), "Failed to create event");
    OnName(event, info.__name);

    return Ok(std::move(event));
}

EventPool::EventPool(EventPool&& rhs) : device(rhs.device) {
    events = std::move(rhs.events);
}

EventPool::~EventPool() {
    events.clear();
}

Res<Ref<Event>> EventPool::request() {
    if (active_count < events.size()) {
        return Ok(newRef(events[active_count++]));
    }

    auto res = EventState().into(device);
    OnErr(res);
    events.push_back(res.unwrap());
    active_count++;
    return Ok(newRef(events.back()));
}

void EventPool::resetPool() {
    active_count = 0;
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
