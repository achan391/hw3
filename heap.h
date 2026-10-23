#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <cstddef>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
    Heap(int m = 2, PComparator c = PComparator())
        : m_(m), comp_(c)
    {
        if (m_ < 2) {
            throw std::invalid_argument("Heap arity must be at least 2");
        }
    }

    ~Heap() {}

    void push(const T& item)
    {
        data_.push_back(item);
        std::size_t child = data_.size() - 1;
        while (child > 0) {
            std::size_t parent = (child - 1) / static_cast<std::size_t>(m_);
            if (!comp_(data_[child], data_[parent])) {
                break;
            }
            std::swap(data_[child], data_[parent]);
            child = parent;
        }
    }

    T const& top() const
    {
        if (data_.empty()) {
            throw std::underflow_error("Heap is empty");
        }
        return data_[0];
    }

    void pop()
    {
        if (data_.empty()) {
            throw std::underflow_error("Heap is empty");
        }
        if (data_.size() == 1) {
            data_.pop_back();
            return;
        }

        data_[0] = data_.back();
        data_.pop_back();

        std::size_t current = 0;
        while (true) {
            std::size_t firstChild = current * static_cast<std::size_t>(m_) + 1;
            if (firstChild >= data_.size()) {
                break;
            }

            std::size_t bestChild = firstChild;
            std::size_t end = std::min(data_.size(), firstChild + static_cast<std::size_t>(m_));
            for (std::size_t child = firstChild + 1; child < end; ++child) {
                if (comp_(data_[child], data_[bestChild])) {
                    bestChild = child;
                }
            }

            if (!comp_(data_[bestChild], data_[current])) {
                break;
            }
            std::swap(data_[current], data_[bestChild]);
            current = bestChild;
        }
    }

    bool empty() const { return data_.empty(); }
    size_t size() const { return data_.size(); }

private:
    std::vector<T> data_;
    int m_;
    PComparator comp_;
};

#endif
