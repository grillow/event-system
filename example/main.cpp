#include <iostream>
#include <GES/EventBus.hpp>
#include <GES/Handler.hpp>

#include <list>


std::shared_ptr<EventBus> bus = EventBus::Create(); // global :3


struct ExampleEvent : IEventTemplate<ExampleEvent> {
    ExampleEvent(const uint64_t number) : number(number) {}

    const uint64_t number;
};
template<>
const IEvent::Type_t IEventTemplate<ExampleEvent>::ID = 1;


struct ExampleEventListener : public IEventListener<ExampleEvent> {
    ExampleEventListener(std::string name) : m_name(std::move(name)) {}

    virtual void OnEvent(ExampleEvent & event) override {
        std::cout << m_name << " received: " << event.number << std::endl;
    }

private:
    const std::string m_name;
};


struct ExampleStruct {
    ExampleStruct() {
        std::cout << "ExampleStruct()" << std::endl;
        handler.Subscribe(bus, std::make_unique<ExampleEventListener>("ListenerA"));
        bus->Raise<ExampleEvent>(808);
       	handler.Subscribe(bus, std::make_unique<ExampleEventListener>("ListenerB"));
    }

    ~ExampleStruct() {
        std::cout << "~ExampleStruct()" << std::endl;
    }
private:
	Handler handler;
};

int main() {
    std::cout << "Hello, World!\n";

    {
        ExampleStruct sample;

        bus->Raise<ExampleEvent>(1337);
        bus->Raise<ExampleEvent>(1488);
    }

    bus->Raise<ExampleEvent>(404);
    

    return 0;
}

