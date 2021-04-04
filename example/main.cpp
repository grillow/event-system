#include <iostream>
#include <GES/EventBus.hpp>
#include <GES/Handler.hpp>

#include <list>


std::shared_ptr<EventBus> bus = EventBus::Create(); // global :3

namespace Event {
    struct Example : IEventTemplate<Example> {
        Example(const uint64_t number) : number(number) {}

        const uint64_t number;
    };
    template<>
    const IEvent::Type_t IEventTemplate<Example>::ID = "Example"_t;
}

struct ExampleEventListener : EventListener<Event::Example> {
    ExampleEventListener(std::string name) : m_name(std::move(name)) {}

    virtual void OnEvent(Event::Example & event) override {
        std::cout << m_name << " received: " << event.number << std::endl;
    }

private:
    const std::string m_name;
};


struct ExampleStruct {
    ExampleStruct() {
        std::cout << "ExampleStruct()" << std::endl;
        handler.Subscribe(bus, std::make_unique<ExampleEventListener>("ListenerA"));
        bus->Raise<Event::Example>(808);
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

        bus->Raise<Event::Example>(1337);
        bus->Raise<Event::Example>(1488);
    }

    bus->Raise<Event::Example>(404);
    

    return 0;
}

