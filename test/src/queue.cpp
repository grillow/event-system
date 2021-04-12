#include <gtest/gtest.h>

#include <GES/GES.hpp>

#include <numeric>
#include <thread>
#include <array>
#include <list>


namespace Event {
    struct Number : EventTemplate<Number> {
        Number(int64_t number) : number(number) {}
        const int64_t number;
    };
}

TEST(queue, from_two_threads) {
    const auto spammer = [](std::shared_ptr<Event::Bus> bus,
            const size_t amount) {
        for (size_t i = 1; i <= amount; ++i) {
            bus->Push<Event::Number>(i);
        }
    };

    std::array<size_t, 2> amount = { 200, 200 };
    std::array<int64_t, 2>   sum = { 0, 20100 + 20100 };

    std::list<int64_t> list;

    auto bus = Event::Bus::Create();
    auto handle = bus->Add<Event::Listener<Event::Number>>(
        [&](Event::Number & event) {
            list.push_back(event.number);
        }
    );

    std::thread spammer_first  (spammer, bus, amount[0]);
    std::thread spammer_second (spammer, bus, amount[1]);

    spammer_first.join();
    spammer_second.join();

	bus->RaiseAll();

    sum[0] = std::accumulate(list.begin(), list.end(), 0);

    EXPECT_EQ(sum[0], sum[1]);

}

