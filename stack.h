#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 

public:
    StackArray():CircularArray<T>(){
    }

    StackArray(int _capacity):CircularArray<T>(_capacity){
    }

    void push(T data){
        this->push_back(data);
        return;
    }

    T pop(){
        T element = this->pop_back();
        return element;
    }
};