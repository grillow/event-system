#include <iostream>
#include <GES/GES.hpp>

#include <list>


std::shared_ptr<Event::Bus> bus = Event::Bus::Create(); // global :3

namespace Event {
    struct Example : EventTemplate<Example> {
        Example(const uint64_t number) : number(number) {}

        const uint64_t number;
    };
    template<>
    const IEvent::Type_t EventTemplate<Example>::ID = "Example"_t;
}

struct ExampleListener : Event::ListenerTemplate<Event::Example> {
    ExampleListener(std::string name) : m_name(std::move(name)) {}

    virtual void OnEvent(Event::Example & event) override {
        std::cout << m_name << " received: " << event.number << std::endl;
    }

private:
    const std::string m_name;
};


struct ExampleStruct {
    ExampleStruct() {
        std::cout << "ExampleStruct()" << std::endl;
        handler.Subscribe(bus, std::make_unique<ExampleListener>("ListenerA"));
        bus->Raise<Event::Example>(808);
       	handler.Subscribe(bus, std::make_unique<ExampleListener>("ListenerB"));
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

