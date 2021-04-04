#include <gtest/gtest.h>

#include <GES/GES.hpp>


struct NumberEvent : IEventTemplate<NumberEvent> {
	NumberEvent(int64_t number) : number(number) {}
	int64_t number;
};
template<> const IEvent::Type_t IEventTemplate<NumberEvent>::ID = 1;

TEST(Priority, example) {
    auto bus = EventBus::Create();
	
	int64_t number = 0;

	auto receivehandle = bus->Add<IEventListenerLambda<NumberEvent>>(
		[&](NumberEvent & event) -> void {
			number = event.number;
		}
	);

	EXPECT_EQ(number, 0);
	
	bus->Raise<NumberEvent>(1337);
	EXPECT_EQ(number, 1337);

	auto hookhandle = bus->Add(
		std::make_unique<IEventListenerLambda<NumberEvent>>(
			[](NumberEvent & event) {
				event.number = -event.number;
			}),
        Priority::HOOK
	);

	bus->Raise<NumberEvent>(1337);
	EXPECT_EQ(number, -1337);
}

