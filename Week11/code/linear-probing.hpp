template<typename K, typename V>
class LinearProbingHashTable {
private:
    std::vector<HashEntry<K, V>> table;
    size_t size;
    size_t capacity;
    static constexpr double MAX_LOAD_FACTOR = 0.7;
    
    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }
    
    double getLoadFactor() const {
        return static_cast<double>(size) / capacity;
    }
    
public:
    LinearProbingHashTable(size_t cap = 16) 
        : capacity(cap), size(0) {
        table.resize(capacity);
    }
    
    bool insert(const K& key, const V& value) {
        if (getLoadFactor() >= MAX_LOAD_FACTOR) {
            rehash();
        }
        
        size_t index = hash(key);
        size_t i = 0;
        
        while (i < capacity) {
            size_t probeIndex = (index + i) % capacity;
            
            if (table[probeIndex].state == EMPTY || 
                table[probeIndex].state == DELETED) {
                table[probeIndex].key = key;
                table[probeIndex].value = value;
                table[probeIndex].state = OCCUPIED;
                size++;
                return true;
            }
            
            if (table[probeIndex].state == OCCUPIED && 
                table[probeIndex].key == key) {
                // Update existing
                table[probeIndex].value = value;
                return true;
            }
            
            i++;
        }
        
        return false;  // Table full
    }
    
    bool search(const K& key, V& value) const {
        size_t index = hash(key);
        size_t i = 0;
        
        while (i < capacity) {
            size_t probeIndex = (index + i) % capacity;
            
            if (table[probeIndex].state == EMPTY) {
                return false;  // Not found
            }
            
            if (table[probeIndex].state == OCCUPIED && 
                table[probeIndex].key == key) {
                value = table[probeIndex].value;
                return true;
            }
            
            i++;
        }
        
        return false;
    }
    
    bool remove(const K& key) {
        size_t index = hash(key);
        size_t i = 0;
        
        while (i < capacity) {
            size_t probeIndex = (index + i) % capacity;
            
            if (table[probeIndex].state == EMPTY) {
                return false;
            }
            
            if (table[probeIndex].state == OCCUPIED && 
                table[probeIndex].key == key) {
                table[probeIndex].state = DELETED;
                size--;
                return true;
            }
            
            i++;
        }
        
        return false;
    }
    
private:
    void rehash() {
        size_t oldCapacity = capacity;
        capacity *= 2;
        
        std::vector<HashEntry<K, V>> oldTable = std::move(table);
        table.clear();
        table.resize(capacity);
        size = 0;
        
        for (size_t i = 0; i < oldCapacity; ++i) {
            if (oldTable[i].state == OCCUPIED) {
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
    }
};