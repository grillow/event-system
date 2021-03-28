#pragma once
#include <algorithm>

struct UniqueGenerator final {
   
    UniqueGenerator() : m_next(0) {}

    uint64_t Get() {
        for (uint64_t index = m_next; index < m_values.size(); ++index) {
            if (!m_values[index]) {
                m_values[index] = true;
                return index;
            }
        }

        m_values.emplace_back(true);
        return m_values.size() - 1;
    }

    void Release(uint64_t value) {
        m_values[value] = false;
        m_next = std::min(m_next, value);
    }

private:
    std::vector<bool> m_values;
    uint64_t m_next;
};

