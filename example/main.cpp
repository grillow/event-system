#include <iostream>
#include <GES/EventBus.hpp>
#include <GES/Subscriber.hpp>

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


struct ExampleEventListener : public IEventListener<ExampleEvent> {
    ExampleEventListener(std::string name) : m_name(std::move(name)) {}

    virtual void OnEvent(ExampleEvent & event) override {
        std::cout << m_name << " received: " << event.number << std::endl;
    }

private:
    const std::string m_name;
};

struct ExampleStruct : public Subscriber {
public:
    ExampleStruct() {
        std::cout << "ExampleStruct()" << std::endl;
        Subscribe(bus, std::make_unique<ExampleEventListener>("ListenerA"));
        bus->Raise(std::make_unique<ExampleEvent>(808));
       	Subscribe(bus, std::make_unique<ExampleEventListener>("ListenerB"));
    }

    ~ExampleStruct() {
        std::cout << "~ExampleStruct()" << std::endl;
    }

};

int main() {
    std::cout << "Hello, World!\n";

    {
        ExampleStruct sample;

        bus->Raise(std::make_unique<ExampleEvent>(1337));
        bus->Raise(std::make_unique<ExampleEvent>(1488));
    }

    bus->Raise(std::make_unique<ExampleEvent>(404));
    

    return 0;
}

