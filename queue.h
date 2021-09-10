#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> { 
public:
    QueueArray():CircularArray<T>(){
    }

    QueueArray(int _capacity):CircularArray<T>(_capacity){
    }

    void push(T data){
        this->push_back(data);
        return;
    }

    T pop(){
        T element = this->pop_front();
        return element;
    }
    
};