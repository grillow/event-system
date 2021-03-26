#pragma once
#include "IEvent.hpp"

#include <type_traits>
#include <vector>
#include <functional>


struct IEventListenerBase {
    virtual ~IEventListenerBase() = default;
    virtual void Receive(IEvent & event) = 0;
    virtual std::vector<std::string> Types() const = 0;
};


struct IEventListenerBaseTypes : public IEventListenerBase {
public:
    std::vector<std::string> Types() const override final {
        return m_types;
    }

protected:
    std::vector<std::string> m_types;
};


template <typename T>
struct IEventListener : public IEventListenerBaseTypes {
public:
    constexpr IEventListener() {
        static_assert(std::is_base_of<IEvent, T>::value,
                "IEventListener<T>: T must inherit from IEvent");
        m_types.emplace_back(T::Name);
    }

    void Receive(IEvent & event) override final {
        OnEvent(dynamic_cast<T &>(event));
    }

    virtual void OnEvent(T & event) = 0;

};


template <typename T>
struct IEventListenerLambda : public IEventListener<T> {
public:
    constexpr IEventListenerLambda(std::function<void(T &)> callback) : m_callback(callback) {}

    void OnEvent(T & event) override final {
        m_callback(event);
    }

private:
    const std::function<void(T &)> m_callback;
};

