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
    if (!__borrowed && handle) {
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
    active_count = rhs.active_count;
    rhs.active_count = 0;
}

EventPool::~EventPool() {
    events.clear();
}

Res<CRef<Event>> EventPool::request() {
    if (active_count < events.size()) {
        return Ok(newCRef(events[active_count++]));
    }

    auto res = EventState().into(device);
    OnErr(res);
    events.push_back(res.unwrap());
    active_count++;
    return Ok(newCRef(events.back()));
}

Res<Event> EventPool::acquire() {
    if (active_count < events.size()) {
        auto evt = std::move(events.back());
        events.pop_back();
        return Ok(std::move(evt));
    }
    return EventState().into(device);
}

void EventPool::reback(Event&& event) {
    events_cache.push_back(std::move(event));
}

void EventPool::resetPool() {
    active_count = 0;
    for (auto& evt : events_cache) {
        events.push_back(std::move(evt));
    }
    events_cache.clear();
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
