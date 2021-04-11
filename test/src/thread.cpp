#include <gtest/gtest.h>

#include <GES/GES.hpp>

#include <numeric>
#include <thread>
#include <chrono>
#include <array>
#include <list>

using namespace std::chrono_literals;

namespace Event {
    struct Number : EventTemplate<Number> {
        Number(int64_t number) : number(number) {}
        const int64_t number;
    };
}

#include <iostream>
TEST(thread, simple_safety) {
    const auto spammer = [](std::shared_ptr<Event::Bus> bus,
            std::chrono::milliseconds deltaTime,
            const size_t amount) {
        for (size_t i = 1; i <= amount; ++i) {
            bus->Raise<Event::Number>(i);
            
            //std::cout << deltaTime.count() << " " << i << '\n';

            std::this_thread::sleep_for(deltaTime);
        }
    };

    std::array<size_t, 2>                       amount = { 200, 100 };
    std::array<std::chrono::milliseconds, 2> deltaTime = { 1ms, 2ms };
    std::array<int64_t, 2>                         sum = { 0, 20100 + 5050 };

    std::list<int64_t> list;

    auto bus = Event::Bus::Create();
    auto handle = bus->Add<Event::Listener<Event::Number>>(
        [&](Event::Number & event) {
            list.push_back(event.number);
            
            std::cout << event.number << '\n';

            //std::this_thread::sleep_for(10ms);
        }
    );

    std::thread spammer_first  (spammer, bus, deltaTime[0], amount[0]);
    std::thread spammer_second (spammer, bus, deltaTime[1], amount[1]);

    spammer_first.join();
    spammer_second.join();

    sum[0] = std::accumulate(list.begin(), list.end(), 0);

    EXPECT_EQ(sum[0], sum[1]);

}

/*
 *  This whole test is useless at the moment
 *  The test passes, but bus is not thread-safe
 */

