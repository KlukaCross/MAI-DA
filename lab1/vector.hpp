#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class TVector {
public:
    TVector();
    TVector(unsigned int size, const T& value);
    TVector(TVector<T>& other);
    ~TVector();
    unsigned int Size();
    bool Empty();
    void PushBack(const T& value);
    void PopBack();
    void Set(unsigned int pos, const T& value);
    T& Back();
    T& Front();
    T& Get(unsigned int pos);
    T& operator[](unsigned int pos);
    T* Begin();
    T* End();
    void Reserve(unsigned int newPoolSize);
private:
    T* buffer;
    unsigned int poolSize;
    unsigned int size;
    void GrowBuffer();
    const unsigned int BUFFER_GROW_COEFFICIENT = 2;
};

template<typename T>
void TVector<T>::Reserve(unsigned int newPoolSize) {
    T* newBuf = new T[newPoolSize];

    for (unsigned int i = 0; i < poolSize; ++i) {
        newBuf[i] = buffer[i];
    }

    delete[] buffer;
    poolSize = newPoolSize;
    buffer = newBuf;
}

template<typename T>
T* TVector<T>::Begin() {
    return &buffer[0];
}

template<typename T>
T* TVector<T>::End() {
    return &buffer[size];
}

template<typename T>
TVector<T>::TVector() {
    buffer = new T[1];
    poolSize = 1;
    size = 0;
}

template<typename T>
TVector<T>::TVector(unsigned int size, const T& value) {
    buffer = new T[size];
    poolSize = size;
    this->size = size;
    for (unsigned int i = 0; i < size; ++i) {
        buffer[i] = value;
    }
}

template<typename T>
TVector<T>::TVector(TVector<T> &other) {
    poolSize = other.poolSize;
    size = other.size;
    buffer = new T[size];
    for (unsigned int i = 0; i < other.size; ++i) {
        buffer[i] = other.buffer[i];
    }
}

template<typename T>
TVector<T>::~TVector() {
    delete[] buffer;
    poolSize = 0;
    size = 0;
}

template<typename T>
void TVector<T>::PushBack(const T& value) {
    if (size >= poolSize) {
        GrowBuffer();
    }
    buffer[size] = value;
    ++size;
}

template<typename T>
void TVector<T>::PopBack() {
    --size;
}

template<typename T>
unsigned int TVector<T>::Size() {
    return size;
}

template<typename T>
bool TVector<T>::Empty() {
    return size == 0;
}

template<typename T>
T& TVector<T>::Get(unsigned int pos) {
    return buffer[pos];
}

template<typename T>
T &TVector<T>::Front() {
    return Get(0);
}

template<typename T>
T &TVector<T>::Back() {
    return Get(size - 1);
}

template<typename T>
T& TVector<T>::operator[](unsigned int pos) {
    return Get(pos);
}

template<typename T>
void TVector<T>::Set(unsigned int pos, const T &value) {
    buffer[pos] = value;
}

template<typename T>
void TVector<T>::GrowBuffer() {
    T* new_buf = new T[BUFFER_GROW_COEFFICIENT * poolSize];

    for (unsigned int i = 0; i < poolSize; ++i) {
        new_buf[i] = buffer[i];
    }

    delete[] buffer;
    poolSize = poolSize * BUFFER_GROW_COEFFICIENT;
    buffer = new_buf;
}


#endif //VECTOR_H
