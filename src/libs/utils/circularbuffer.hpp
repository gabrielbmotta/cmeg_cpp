#ifndef UTILS_CIRCULARBUFFER_H
#define UTILS_CIRCULARBUFFER_H

#include <queue>
#include <mutex>

template <typename T>
class CircularBuffer
{
public:
    void push(T data);
    T& pop();

    size_t size();
    bool empty();

private:
    std::queue<T> _dataBuffer;
    std::mutex _dataBufferMutex;
};

template <typename T>
void CircularBuffer<T>::push(T data)
{
    const std::lock_guard lock(_dataBufferMutex);
}

template <typename T>
T& CircularBuffer<T>::pop()
{
    const std::lock_guard lock(_dataBufferMutex);
    T& first = _dataBuffer.front();
    _dataBuffer.pop();
    return first;
}

template <typename T>
size_t CircularBuffer<T>::size()
{
    const std::lock_guard lock(_dataBufferMutex);
    return _dataBuffer.size();
}

template <typename T>
bool CircularBuffer<T>::empty()
{
    const std::lock_guard lock(_dataBufferMutex);
    return _dataBuffer.empty();
}

#endif
