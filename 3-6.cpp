// 3-6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>

// lista dwukierunkowa cykliczna

template <typename T> 
struct Element {
    T data;

    Element<T>* forward; // down the list toward last elem
    Element<T>* backward; // up the list toward first elem

    Element(T _data) : backward(nullptr), forward(nullptr), data(_data) {}
};

template <typename T> 
class List {
    Element<T>* current;

    Element<T>* first;
    Element<T>* last;

    size_t size;
public:

    List() : current(nullptr), first(nullptr), last(nullptr), size(0) {}
    ~List() {
        Element<T>* temporary = current;

        do {

            Element<T>* t2 = temporary->backward;
            pop_pointer(temporary);
            temporary = t2;

            temporary = temporary->forward;
        } while (temporary != current->backward);

    }

    void insert_front(T data) {
        Element<T>* new_element = new Element<T>(data);

        if (current == nullptr) { // first add
            current = new_element;
            first = new_element;
            last = new_element;

            // it's the only element for now, so:
            current->forward = current;
            current->backward = current;
        }
        else if (current == last) { // add at the back
            new_element->backward = last;
            new_element->forward = first;

            last->forward = new_element;
            first->backward = new_element;

            last = new_element;
        }
        else {
            new_element->backward = current;
            new_element->forward = current->forward;

            current->forward->backward = new_element;
            current->forward = new_element;

        }

        size++;
    }
    void insert_back(T data) {
        Element<T>* new_element = new Element<T>(data);

        if (current == nullptr) { // first add
            current = new_element;
            first = new_element;
            last = new_element;

            // it's the only element for now, so:
            current->forward = current;
            current->backward = current;
        }
        else if (current == first) { // add at the back
            new_element->backward = last;
            new_element->forward = first;

            last->forward = new_element;
            first->backward = new_element;

            first = new_element;
        }
        else {
            new_element->forward = current;
            new_element->backward = current->backward;

            current->backward->forward = new_element;
            current->backward = new_element;

        }

        size++;
    }

    void pop_current() {
        if (current == nullptr) throw std::out_of_range("The list is empty.");

        if (size == 1) {
            delete current, first, last;
            current = first = last = nullptr;
        }
        else {
            current->forward->backward = current->backward;
            current->backward->forward = current->forward;

            if (current == first) first = current->forward;
            else if (current == last) last = current->backward;

            Element<T>* temp = current;
            current = current->forward;

            delete temp;
        }

        size--;
    }
    void pop_pointer(Element<T>* element) {
        if (element == nullptr) throw std::out_of_range("The list is empty.");

        if (size == 1) {
            delete current, first, last;
            current = first = last = nullptr;
        }
        else {
            element->forward->backward = element->backward;
            element->backward->forward = element->forward;

            if (element == current) current = element->forward;

            if (element == first) first = element->forward;
            else if (element == last) last = element->backward;

            delete element;
        }

        size--;
    }
    void pop_value(T value) {
        Element<T>* temporary = current;

        do {

            if (temporary->data == value) {
                Element<T>* t2 = temporary->backward;
                pop_pointer(temporary);
                temporary = t2;
            }

            temporary = temporary->forward;
        } while (temporary != current->backward);

    }

    T get_current() {
        if (current == nullptr) throw std::out_of_range("The list is empty.");
        return current->data;
    }
    size_t get_size() {
        return size;
    }

    void move_forward() {
        current = current->forward;
    }
    void move_backward() {
        current = current->backward;
    }

    // not compatible with every type; only for tests!
    void show_toward_front() {
        Element<T>* temporary = current;

        std::cout << "Two-way List Elements (forward): \n";

        unsigned int c = 0;
        for (; temporary != current->backward; temporary = temporary->forward) {
            std::cout << "\t[" << c++ << "] Element value: " << temporary->data << "\n";
        }
        std::cout << "\t[" << c++/*hehe*/ << "] Element value: " << temporary->data << "\n";
    }
    void show_toward_back() {
        Element<T>* temporary = current;

        std::cout << "Two-way List Elements (backward): \n";

        unsigned int c = size - 1;
        for (; temporary != current->forward; temporary = temporary->backward) {
            std::cout << "\t[" << c-- << "] Element value: " << temporary->data << "\n";
        }
        std::cout << "\t[" << c--/* :( */ << "] Element value: " << temporary->data << "\n";
    }

};

int main()
{

    // FUN
    {
        List<int> list;

        list.insert_front(10);
        list.insert_front(101010);
        list.insert_front(11);
        list.insert_front(404);
        list.insert_front(101010);
        list.insert_front(501);

        list.move_forward();
        std::cout << list.get_current() << "\n";

        list.insert_front(101010);

        list.insert_back(4110041);

        list.show_toward_front();
        list.move_forward();
        list.show_toward_front();

        std::cout << "\n";
        list.pop_value(101010);
        list.show_toward_front();
    }
    
    return 0;
}
