#include <iostream>
#include <GES/EventBus.hpp>

#include <list>


std::shared_ptr<EventBus> bus = EventBus::Create(); // global :3


struct ExampleEvent : public IEvent {
    static const std::string Name;
    
    virtual std::string Type() const override {
        return Name;
    }

    ExampleEvent(const uint64_t number) : number(number) {}

    const uint64_t number;
};
const std::string ExampleEvent::Name = "ExampleEvent";


struct ExampleEventListener : public virtual IEventListener<ExampleEvent> {
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
        m_handles.emplace_back(bus->Add(std::make_unique<ExampleEventListener>("ListenerA")));
        bus->Raise(std::make_unique<ExampleEvent>(808));
        m_handles.emplace_back(bus->Add(std::make_unique<ExampleEventListener>("ListenerB")));
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

        bus->Raise(std::make_unique<ExampleEvent>(1337));
        bus->Raise(std::make_unique<ExampleEvent>(1488));
    }
    

    return 0;
}

