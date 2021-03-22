#include <iostream>
#include <GES/EventBus.hpp>

#include <list>


EventBus bus; // global :3


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
        std::cout << m_name << " received: " << event.number << std::endl;
    }

private:
    const std::string m_name;
};

struct ExampleStruct {
public:
    ExampleStruct() {
        std::cout << "ExampleStruct()" << std::endl;
        m_handles.emplace_back(bus.Add(std::make_unique<ExampleEventListener>("ListenerA")));
        m_handles.emplace_back(bus.Add(std::make_unique<ExampleEventListener>("ListenerB")));
    }

    ~ExampleStruct() {
        std::cout << "~ExampleStruct()" << std::endl;
    }

private:
    std::list<EventListenerHandle> m_handles;

};

int main() {
    std::cout << "Hello, World!\n";

    {
        ExampleStruct sample;

        bus.Raise(std::make_unique<ExampleEvent>(1337));
        bus.Raise(std::make_unique<ExampleEvent>(1488));
    }
    

    return 0;
}

