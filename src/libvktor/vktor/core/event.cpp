#include "event.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = EventState::Self;

Self EventState::setFlags(VkEventCreateFlags flags) {
    event_ci.flags = flags;
    return *this;
}

Res<Event> EventState::into(const CoreApi& api) const {
    return Event::from(api, *this);
}

Event::Event(Event&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

Event::~Event() {
    if (!__borrowed && handle) {
        vkDestroyEvent(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
}

Res<Event> Event::from(const CoreApi& api, const EventState& info) {
    Event event(api);

    OnRet(vkCreateEvent(api, &info.event_ci, api, event), "Failed to create event");
    OnName(event, info.__name);

    return Ok(std::move(event));
}

EventPool::EventPool(EventPool&& rhs) : api(rhs.api) {
    active_count = rhs.active_count;
    rhs.active_count = 0;
    events = std::move(rhs.events);
    events_cache = std::move(rhs.events_cache);
}

EventPool::~EventPool() {
    events.clear();
    events_cache.clear();
}

Res<CRef<Event>> EventPool::request() {
    if (active_count < events.size()) {
        return Ok(newCRef(events[active_count++]));
    }

    auto res = EventState().into(api);
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
    return EventState().into(api);
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
