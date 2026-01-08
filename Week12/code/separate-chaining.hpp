#pragma once
#include <vector>
#include <list>
#include <functional>
#include <utility>
#include <stdexcept>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class SeparateChainingHashTable {
private:
    using KeyValuePair = std::pair<Key, Value>;
    std::vector<std::list<KeyValuePair>> buckets;
    size_t elementCount;
    Hash hasher;
    double maxLoadFactor_ = 1.0;

    size_t getIndex(const Key& key) const {
        return hasher(key) % buckets.size();
    }

    void rehash() {
        auto oldBuckets = buckets;
        buckets.assign(buckets.size() * 2, {});
        elementCount = 0;
        for (const auto& bucket : oldBuckets) {
            for (const auto& pair : bucket) {
                insert(pair.first, pair.second);
            }
        }
    }

public:
    SeparateChainingHashTable(size_t capacity = 8) : buckets(capacity), elementCount(0) {}

    void insert(const Key& key, const Value& value) {
        if ((double)elementCount / buckets.size() >= maxLoadFactor_) {
            rehash();
        }
        
        size_t index = getIndex(key);
        for (auto& pair : buckets[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        
        buckets[index].push_back({key, value});
        elementCount++;
    }

    bool find(const Key& key, Value& result) const {
        size_t index = getIndex(key);
        for (const auto& pair : buckets[index]) {
            if (pair.first == key) {
                result = pair.second;
                return true;
            }
        }
        return false;
    }

    bool contains(const Key& key) const {
        size_t index = getIndex(key);
        for (const auto& pair : buckets[index]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    void remove(const Key& key) {
        size_t index = getIndex(key);
        auto& bucket = buckets[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                elementCount--;
                return;
            }
        }
    }

    size_t size() const {
        return elementCount;
    }

    bool empty() const {
        return elementCount == 0;
    }
};
