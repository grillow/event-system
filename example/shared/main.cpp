#include <iostream>
#include <GES/EventBus.hpp>

// global :3
EventBus bus;


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

    virtual void OnEvent(ExampleEvent & event) override {
        std::cout << event.number << std::endl;
    }
};

struct ExampleStruct {
public:
    ExampleStruct() : m_handle(bus.Add(std::make_unique<ExampleEventListener>())) {
        std::cout << "ExampleStruct()" << std::endl;
    }

    ~ExampleStruct() {
        std::cout << "~ExampleStruct()" << std::endl;
    }

private:
    EventListenerHandle m_handle;

};

int main() {
    std::cout << "Hello, World!\n";

    {
        ExampleStruct sample;

        ExampleEvent event(1337);
        bus.Dispatch(event);
    }
    


    return 0;
}

