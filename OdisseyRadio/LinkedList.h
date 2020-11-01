#pragma once
#include <iostream>


/**
 * @class Nodo Linked List
 * @brief Description: Nodo class implementation, holds the data and the pointer to the next nodo
 */
template<class T>
class Nodo{
public:

    T data;
    Nodo* next;

    Nodo(T data){
        this->data = data;
        this->next = nullptr;
    }
};




/**
 * @class Linked List implementation
 * @briefDescription: This class contains all the necessary methods for linked List's implementation
 */
template<class T>
class LinkedList{
public:

    /**
     * @brief Constructor, initialize  the head pointer and the size
     */
    LinkedList(){
        this->head = nullptr;
        this->size = 0;
    }


    /**
     *@brief Destructor
     */
    ~LinkedList() = default;


    /**
     * @brief Verify if the linked list is empty
     * @return true if it's empty, otherwise it's false
     */

    bool isEmpty(){
        return head == nullptr;
    }


    /**
     *@brief Add a new nodo to the tail of the linked list
     * @param data
     */


    void addNodo(T data){
        //std::cout << data << "\n";
        //std::cout << "Head Linked List " << &head << "\n";
        if(head== nullptr){
            head =  new Nodo<T>(data);
            size++;
        }else{
            Nodo<T> *current = head;
            //std::cout<< "current "  << current << " head " << head << "\n";
            while(current->next != nullptr){
                current = current->next;
            }
            current->next = new Nodo<T>(data);
            size++;
        }
    }

    /**
     *@brief Remove a nodo from a especific position
     * @param index
     */
    void remove(int index){
        if(size == 1){
            std::cout << head << " data : " << head->next;
            head = nullptr;
            size = 0;
        }else if(index == 0){
            head = head->next;
            size--;
        }else{
            int i = 0;
            Nodo<T> *current = head;
            while(i < index -1){
                current = current->next;
                i++;
            }
            current->next = current->next->next;
            size--;
        }
    }
    void printElements(){
        Nodo<T> *current = head;
        while(current != nullptr){
            std::cout << "Direccion en memoria " << current << "\n";
            std::cout << "El valor de la lista es " << current->data << "\n";
            std::cout << "Next :" << current->next << "\n";
            current = current->next;
        }

    }

    /**
     * @brief Returns the value of the size
     * @return
     */
    int getSize(){
        return this->size;
    }

    /**
     * @brief Returns the nodo from the especified position
     * @param index
     * @return nodo encoutered in the index position
     */

    Nodo<T>* get(int index){
        if(index>=size){
            return nullptr;
        }else{
            int current{0};
            Nodo<T>* temp = head;
            for(current; current < index;current++){
                temp = temp->next;
            }
            return temp;
        }
    }

    T getLast(){
        Nodo<T> *current = head;
        while(current->next != nullptr){
            current = current->next;

        }
        return current;
    }

    /**
     * @brief Remove all the nodes of the linked list
     */

    void removeAll(){
        head = nullptr;
        size = 0;
    }
private:
    Nodo<T>* head;
    int size{};

};
