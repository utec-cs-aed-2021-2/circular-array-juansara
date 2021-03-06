#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray(); //Completo
    CircularArray(int _capacity); //Completo
    virtual ~CircularArray(); //Completo
    void push_front(T data); //Completo
    void push_back(T data); //Completo
    void insert(T data, int pos); //Completo
    T pop_front(); //Completo
    T pop_back(); //Completo
    bool is_full(); //Completo
    bool is_empty(); //Completo
    int size(); //Completo
    void clear(); //Completo
    T &operator[](int); //Completo
    void sort(); //Completo
    bool is_sorted(); //Completo
    void reverse(); //Completo
    string to_string(string sep=" "); //Completo
    void resize();
    void heapify(T* arr, int tamanio, int nivel);

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}

template<class T>
bool CircularArray<T>::is_full() {
    return ((front == 0 && back == capacity - 1) || front == next(back));
}

template<class T>
bool CircularArray<T>::is_empty() {
    return (front == -1);
}

template<class T>
int CircularArray<T>::size() {
    if(back > front){
        return back - front + 1;
    }
    else{
        return back - front + 1 + capacity;
    }
}

template<class T>
T& CircularArray<T>::operator[](int index) {
    return array[(front + index) % capacity];
}

template<class T>
void CircularArray<T>::push_back(T data) {
    if (is_full()) {
        resize();
    }
    else{
        //Si no hay nada en el arreglo
        if (front == -1) {
            front = 0;
        }  
    }
    back = next(back);
    array[back] = data; 
}

template<class T>
void CircularArray<T>::push_front(T data) {
    if (is_full()) {
        resize();
    }
    else{
    //Si no hay nada en el array
        if (front == -1) {
            front = 0;
            back = 0;
        }
    }
    //Si el front se encuentra en otra posicion, vamos al previo
    front = prev(front);
    //Le ponemos el valor
    array[front] = data;
}

template<class T>
void CircularArray<T>::insert(T data, int pos) {
    if (((front + pos) % capacity) == front) { //si lo quiere poner en la posicion del front
        push_front(data);
        return;
    }
    else if (((front + pos) % capacity) == back) { //si lo quiere poner en la posicion del back
        push_back(data);
        return;
    }
    else {
        capacity++;
        //Shifteo los elementos una posicion hasta la posicion
        for (int i = capacity; i >= ((front + pos) % capacity); i--) {
            array[i] = array[i - 1];
        }
        array[((front + pos) % capacity)] = data;
        return;
    }
}

template<class T>
T CircularArray<T>::pop_front() {
    T element = 0;
    if (is_empty()) {
        cout << "Array vacio" << endl;
        return -1;
    }
    else{
        element = array[front];
        if(front == back){ //Solo tiene un elemento
            front = -1;
            back = -1;
        }
        else{
            front = next(front);
        }
    }
    return element;
}
template<class T>
T CircularArray<T>::pop_back() {
    T element = 0;
    if (is_empty()) {
        cout << "Array vacio" << endl;
        return 0;
    }
    else{
        element = array[back];
        //Si solo hay un elemento
        if (front == back) {
            front = -1;
            back = -1;
    } 
        else {
            back = prev(back);
        }
    }
    return element;
}

template<class T>
bool CircularArray<T>::is_sorted() {
    if (is_empty()) {
        cout << "Array vacio" << endl;
        return false;
    }
    if(back > front){
        for (int i = front; i != back ; i = next(i)) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
    }
    else if (front > back) {
        for (int i = front; i != back ; i = next(i)) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
    }
    return true;
}

template<class T> //Extraido del replit del trabajo de Ordenamiento
void CircularArray<T>::heapify(T* arr, int tamanio, int nivel){
    
  // EMPIEZA CON 1 EL LEFT PARA QUE TENGA SENTIDO SU RECORRIDO
    int root = nivel;
    int left = 2 * nivel + 1;
    int right = 2* nivel + 2; 

    /*Si el hijo de la izquierda es mayor que la raiz
    entonces su raiz pasa a ser el de la izquierda (no hay intercambio entre nodos)
   */

    if(left < tamanio && arr[left] >= arr[root]){
        root = left;
    }

    /*Si el hijo de la derecha es mayor que la raiz entonce la raiz pasa a ser el de la derecha (no hay intercambio entre nodos)

  */
    if(right < tamanio && arr[right] >= arr[root]){
        root = right;
    }

  //Si el nodo en donde estamos, no es una raiz, entonces intercambiamos la raiz con el nodo en dicho nivel

    if(root != nivel){

    swap(arr[nivel],arr[root]);

    //Se aplica recursion para seguir evaluando los demas nodos de los siguientes niveles

    heapify(arr, tamanio, root);
    }
}

template<class T>
void CircularArray<T>::sort() { //Se inicia con back en la ultima posicion y front en 0
    back = size() - 1;
    front = 0;

    for(int i = (size() - 1)/ 2 ; i >= 0; i--){
        heapify(array, size(), i);
    }

  //Elimina los elementos uno por uno
    for(int i= size() - 1; i > 0; i--){
    //Mueve la raiz hasta el final
        swap(array[0],array[i]);
    //Reorganizamos todo el heap pero con menos elementos
        heapify(array, i, 0);
    }
}

template<class T>
void CircularArray<T>::reverse() {
    T temp;
    auto ini = front;
    auto final = back;
    if (is_empty()) {
        cout << "Array vacio" << endl;
        return;
    }
    while(ini != final){
        temp = array[ini];
        array[ini] = array[final];
        array[final] = temp;
        ini = next(ini);
        final = prev(final);
    }
    return;
}

template<class T>
void CircularArray<T>::clear() {
    delete[] array;
}

template<class T>
void CircularArray<T>::resize(){
    T* new_array = new T[capacity*2];
    int temp = capacity;
    int j =  0;
    for(int i = 0; i < size(); i++){
        new_array[j] = array[i];
        j++;
    }
    delete[] array;
    array = new_array;
    capacity *= 2;
    back = j - 1;
    front = 0;
}