#include <GES/EventBus.hpp>

#include <list>


uint64_t global_number = 0;


struct ExampleEvent : public IEvent {
    static const std::string Name;
    virtual std::string Type() const override {
        return Name;
    }

    ExampleEvent(const uint64_t number) : number(number) {}

    const uint64_t number;
};
const std::string ExampleEvent::Name = "ExampleEvent";


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
    void Register(std::shared_ptr<EventBus> bus) {
        m_handles.emplace_back(bus->Add(std::make_unique<ExampleEventListener>("ListenerA")));
        m_handles.emplace_back(bus->Add(std::make_unique<ExampleEventListener>("ListenerB")));
    }

private:
    std::list<EventListenerHandle> m_handles;

};

