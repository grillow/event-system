#include <gtest/gtest.h>

#include <GES/EventBus.hpp>

#include <list>


uint64_t global_number = 0;


struct ExampleEvent : public IEvent {
    virtual std::string Type() const override {
        return "ExampleEvent";
    }

    ExampleEvent(const uint64_t number) : number(number) {}

    const uint64_t number;
};

struct ExampleEventListener : public IEventListener<ExampleEvent> {
    virtual std::string Type() const {
        return "ExampleEvent";
    }

    ExampleEventListener(std::string name) : m_name(std::move(name)) {}

    virtual void OnEvent(ExampleEvent & event) override {
        global_number += event.number;
    }

private:
    const std::string m_name;
};

struct ExampleStruct {
public:
    void Register(EventBus & bus) {
        m_handles.emplace_back(bus.Add(std::make_unique<ExampleEventListener>("ListenerA")));
        m_handles.emplace_back(bus.Add(std::make_unique<ExampleEventListener>("ListenerB")));
    }

private:
    std::list<EventListenerHandle> m_handles;

};


TEST(Example, example) {
    EventBus bus;
    ExampleStruct sample;
    sample.Register(bus);
    bus.Raise(std::make_unique<ExampleEvent>(1337));
    bus.Raise(std::make_unique<ExampleEvent>(1488));

    EXPECT_EQ(global_number, 1337 + 1337 + 1488 + 1488);
}

