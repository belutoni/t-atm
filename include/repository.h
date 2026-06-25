//
// Created by Antonie Gabriel Belu on 02.06.2026.
//

#ifndef OOP_REPOSITORY_H
#define OOP_REPOSITORY_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>

template <typename T>
class repository_t {
    std::vector<T> items;

public:
    repository_t() = default;

    void add(const T& item) {
        items.push_back(item);
    }

    void remove(size_t index) {
        if (index >= items.size()) {
            throw std::out_of_range("Index out of range in repository_t");
        }
        items.erase(items.begin() + index);
    }

    T& get(size_t index) {
        if (index >= items.size()) {
            throw std::out_of_range("Index out of range in repository_t");
        }
        return items[index];
    }

    const T& get(size_t index) const {
        if (index >= items.size()) {
            throw std::out_of_range("Index out of range in repository_t");
        }
        return items[index];
    }

    [[nodiscard]] size_t size() const {
        return items.size();
    }

    [[nodiscard]] bool empty() const {
        return items.empty();
    }

    auto begin() { return items.begin(); }
    auto end() { return items.end(); }
    auto begin() const { return items.begin(); }
    auto end() const { return items.end(); }
};

template <typename T>
void print_collection(const repository_t<T>& repo, std::ostream& os = std::cout) {
    if (repo.empty()) {
        os << "Repository is empty.\n";
        return;
    }

    size_t index = 0;
    for (const auto& item : repo) {
        os << "[" << index++ << "] " << item << "\n";
    }
}

template <typename T>
void print_collection(const std::vector<T>& collection, std::ostream& os = std::cout) {
    if (collection.empty()) {
        os << "Collection is empty.\n";
        return;
    }

    size_t index = 0;
    for (const auto& item : collection) {
        os << "[" << index++ << "] " << item << "\n";
    }
}

template <typename T>
void print_collection(const std::vector<std::shared_ptr<T>>& collection, std::ostream& os = std::cout) {
    if (collection.empty()) {
        os << "Collection is empty.\n";
        return;
    }
    size_t index = 0;
    for (const auto& item : collection) {
        if (item) {
            os << "[" << index++ << "] " << *item << "\n";
        }
    }
}

#endif //OOP_REPOSITORY_H
