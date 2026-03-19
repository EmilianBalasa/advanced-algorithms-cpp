#ifndef CONTAINER_UTILS_H
#define CONTAINER_UTILS_H

#include <stdexcept>

template<class ElementType>
class CircularBuffer {
private:
    ElementType* storage;
    int capacity;
    int frontIndex;
    int backIndex;
    int elementCount;

public:
    CircularBuffer(int maxSize = 200) : capacity(maxSize), frontIndex(0), backIndex(0), elementCount(0) {
        storage = new ElementType[capacity];
    }

    ~CircularBuffer() {
        delete[] storage;
    }

    void insert(const ElementType& item) {
        if (elementCount >= capacity) {
            throw std::overflow_error("Buffer overflow detected");
        }

        storage[backIndex] = item;
        backIndex = (backIndex + 1) % capacity;
        elementCount++;
    }

    ElementType extract() {
        if (elementCount <= 0) {
            throw std::underflow_error("Buffer underflow detected");
        }

        ElementType result = storage[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        elementCount--;
        return result;
    }

    ElementType& front() {
        if (elementCount <= 0) {
            throw std::underflow_error("Buffer is empty");
        }
        return storage[frontIndex];
    }

    bool hasElements() const {
        return elementCount > 0;
    }

    int size() const {
        return elementCount;
    }
};

#endif