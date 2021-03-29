#pragma once
#include <algorithm>
#include <concepts>


template <std::unsigned_integral T>
struct UniqueGenerator final {
   
    UniqueGenerator() : m_next(0) {}

    T Get() {
        for (T index = m_next; index < m_values.size(); ++index) {
            if (!m_values[index]) {
                m_values[index] = true;
                return index;
            }
        }

        m_values.emplace_back(true);
        return m_values.size() - 1;
    }

    void Release(T value) {
        m_values[value] = false;
        m_next = std::min(m_next, value);
    }

private:
    std::vector<bool> m_values;
    T m_next;
};

