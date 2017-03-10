#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions


namespace structures {

template<typename T>
class ArrayList {
public:
    //! Construtor
    /*!
        Cria um array com o tamanho de DEFAULT_SIZE e inicializa size_ com 0
    */
    ArrayList();
    
    //! Construtor que cria array com tamanho do parametro
    /*!
        \param max tipo size_t demarca o tamanho do array criado
        Cria um array com o tamanho do parametro e inicializa top_ com 0
    */
    ArrayList(std::size_t max_size);
    
    //! Destrutor
    ~ArrayList();

    //! Método void clear()
    /*!
        Limpa a lista colocando size_ = 0
        \return void
    */
    void clear();
    
    //! Método void push_back(T data)
    /*!
        \param data Elemento que será inserido na lista
        \return void
        insere elemento no final da lista
    */
    void push_back(T data);
    
    //! Método void push_front(T data)
    /*!
        \param data Elemento que será inserido na lista
        \return void
        insere elemento no começo da lista
    */
    void push_front(T data);
    
    //! Método void insert(T data, std::size_t index);
    /*!
        \param data Elemento que será inserido na lista
        \param index tipo size_t Indica posição que será inserido o elemento
        \return void
        insere elemento em qualquer lugar válido da lista
    */
    void insert(T data, std::size_t index);
    
    //! Método void insert_sorted(T data)
    /*!
        \param data Elemento que será inserido na lista
        \return void
        Funcao que insere elemento em order (crescente)
    */
    void insert_sorted(T data);
    
    //! Método T pop(std::size_t index)
    /*!
        \param index tipo size_t Posicao do elemento que será retirado
        \return T
        Retira elemento da posição escolhida da lista
    */
    T pop(std::size_t index);
    
    //! Método T pop_back()
    /*!
        \return T
        Retira elemento do comeco da lista
    */
    T pop_back();
    
    //! Método T pop_front()
    /*!
        \return T
        Retira elemento do final da lista
    */
    T pop_front();
    
    //! Método void remove(T data)
    /*!
        \return void
        Retira elemento do final da lista sem retorná-lo
    */
    void remove(T data);
    
    //! Um método constante
    /*!
        \return bool
        indica se a lista está cheia
    */
    bool full() const;
    
    //! Um método constante
    /*!
        \return bool
        indica se a lista está vazia
    */
    bool empty() const;
    
    //! Um método contante
    /*!
        \param data
        \return bool
        indica se a lista contém o parâmetro data
    */
    bool contains(const T& data) const;
    
    //! Um método contante
    /*!
        \param data
        \return size_t
        indica se a posição da lista do parâmetro
    */
    std::size_t find(const T& data) const;
    
    //! Um método contante
    /*!
        \return size_t
        indica tamanho da lista
    */
    std::size_t size() const;
    
    //! Um método contante
    /*!
        \return size_t
        indica tamanho máximo da lista
    */
    std::size_t max_size() const;
    
    //! Um método
    /*!
        \param index
        \return T&
        Retorna elemento da posição index, fazendo a checkagem se a posição
        está dentro dos limites do array da lista
    */
    T& at(std::size_t index);
    
    //! Um método
    /*!
        \param index
        \return T&
        Sobrescreve o operador [].
        Na prática ele retorna elemento da posição index, sem fazer a checkagem 
        se a posição está dentro dos limites do array da lista
    */
    T& operator[](std::size_t index);
    
    //! Um método constante
    /*!
        \param index
        \return T&
        Retorna elemento da posição index, fazendo a checkagem se a posição
        está dentro dos limites do array da lista
    */
    const T& at(std::size_t index) const;
    
    //! Um método constante
    /*!
        \param index
        \return T&
        Sobrescreve o operador [].
        Na prática ele retorna elemento da posição index, sem fazer a checkagem 
        se a posição está dentro dos limites do array da lista
    */
    const T& operator[](std::size_t index) const;

private:
    //! Uma variável
    /*!
        Ponteiro que vai apontar para o inicio do array da lista
    */
    T* contents;
    
    //! Uma variável
    /*!
        Indica tamanho da lista
    */
    std::size_t size_;
    
    //! Uma variável
    /*!
        Indica tamanho máximo da lista
    */
    std::size_t max_size_;

    //! Uma variável constante e estática
    /*!
        Indica tamanho máximo da lista default
    */
    const static auto DEFAULT_MAX = 10u;
};

template <class T>
ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = 0;
}

template <class T>
ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0;
}

template <class T>
ArrayList<T>::~ArrayList() {
    delete contents;
}

template <class T>
void ArrayList<T>::clear() {
    size_ = 0;
}

template <class T>
bool ArrayList<T>::full() const {
    return size_ == max_size_;
}

template <class T>
bool ArrayList<T>::empty() const {
    return size_ == 0;
}

template <class T>
void ArrayList<T>::insert(T data, std::size_t index) {
    int current;
    if (full()){
        throw std::out_of_range ("Full List");
    }
    else {
        if (index > size_ || index < 0) {
            throw std::out_of_range ("Not permitted position");
        }
        else {
            current = size_;
            size_ += 1;
            while (current > index) {
                contents[current] = contents[current - 1];
                --current;
            }
            contents[index] = data;
        }
    }
}

template <class T>
void ArrayList <T>::push_back(T data) {
    insert (data, size_);
}

template <class T>
void ArrayList <T>::push_front(T data) {
    insert (data, 0);
}

template <class T>
T ArrayList <T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range ("Empty list");
    }
    else {
        if (index > size_ - 1 || index < 0){
            throw std::out_of_range ("Not permitted position"); 
        }
        else {
            int current = index;
            T data = contents[index];
            size_ -= 1;
            while (current < size_) {
                contents[current] = contents[current + 1];
                ++current;
            }
            return data;
        }
    }
}

template <class T>
T ArrayList<T>::pop_back() {
    return pop(size_ - 1);
}

template <class T>
T ArrayList<T>::pop_front() {
    return pop(0);
}

template <class T>
std::size_t ArrayList<T>::size() const {
    return size_;
}

template <class T>
std::size_t ArrayList<T>::max_size() const {
    return max_size_;
}

template <class T>
std::size_t ArrayList<T>::find(const T& data) const {
    std::size_t current = 0;
    while (current < size_ && data != contents[current]) {
        ++current;
    }
    return current;
}

template <class T>
bool ArrayList<T>::contains(const T& data) const {
    std::size_t current = 0;
    while (current < size_ && data != contents[current]) {
        ++current;
    }
    return current < size_;
}

template <class T>
void ArrayList<T>::remove(T data) {
    if (empty()) {
        throw std::out_of_range ("Empty list");
    }
    else {
        std::size_t current = find(data);
        if (current > size_) {
            throw std::out_of_range ("Element not finded");
        }
        else {
            size_ -= 1;
            while (current < size_) {
            contents[current] = contents[current + 1];
            ++current;
            }
        }
    }
    
}

template <class T>
void ArrayList<T>::insert_sorted(T data) {
    size_t index = 0;
    while (data > contents[index] && index < size_) {
        ++index;
    }
    insert(data, index);
}

template <class T>
T& ArrayList<T>::at(std::size_t index) {
    if (index < 0 || index > max_size_){
        throw std::out_of_range ("Out of boundaries");
    }
    else {
        return contents[index];    
    }
}

template <class T>
T& ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template <class T>
const T& ArrayList<T>::at(std::size_t index) const {
    if (index < 0 || index > max_size_){
        throw std::out_of_range ("Out of boundaries");
    }
    else {
        return contents[index];    
    }
}

template <class T>
const T& ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}

}


#endif
