#include <iostream>
#include <stdlib.h>

using namespace std;

template<typename T>
class List
{
public:
    List();
    List(const List<T>& other);
    ~List();

    void pushBack(T data);
    void pushFront(T data);
    void insert(T data, int index);

    void popBack();
    void popFront();
    void removeAt(int index);
    void clear();

    int getSize();

    T& operator[](const int index);

    bool operator==(const List<T>& list);
    bool operator!=(const List<T>& list);

    void operator=(const List<T>& list);

    void operator+=(List<T> list);
    List<T>& operator+(List<T> list);
    void operator+=(T data);
    List<T>& operator+(T data);

    List<T>& operator--();
    List<T>& operator--(int none);

private:

    template<typename T1>
    class Node
    {
    public:
        Node* pNext;
        T1 data;

        Node(T1 data = T1(), Node* pNext = nullptr);
    };

    int Size;
    Node<T>* head;

    Node<T>* findPrevious(int index);
};

template<typename T>
template<typename T1>
inline List<T>::Node<T1>::Node(T1 data, Node* pNext)
{
    this->data = data;
    this->pNext = pNext;
}

template<typename T>
List<T>::List()
{
    Size = 0;
    head = nullptr;
}

template<typename T>
List<T>::List(const List<T>& other)
{
    this->Size = 0;
    this->head = nullptr;

    Node<T>* current = other.head;

    while (current != nullptr)
    {
        pushBack(current->data);
        current = current->pNext;
    }
}

template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
void List<T>::pushBack(T data)
{
    if (head == nullptr)
    {
        head = new Node<T>(data);
    }
    else
    {
        Node<T>* current = this->head;

        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }

        current->pNext = new Node<T>(data);
    }

    Size++;
}

template<typename T>
void List<T>::pushFront(T data)
{
    head = new Node<T>(data, head);
    Size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
    if (index == 0)
    {
        pushFront(data);
    }
    else if (index >= Size)
    {
        pushBack(data);
    }
    else
    {
        Node<T>* previous = findPrevious(index);
        previous->pNext = new Node<T>(data, previous->pNext);

        Size++;
    }
}

template<typename T>
void List<T>::popBack()
{
    removeAt(Size - 1);
}

template<typename T>
void List<T>::popFront()
{
    if (Size > 0)
    {
        Node<T>* temp = head;

        if (head != nullptr)
            head = head->pNext;
        delete temp;

        Size--;
    }
}

template<typename T>
void List<T>::removeAt(int index)
{
    if (index == 0)
    {
        popFront();
    }
    else
    {
        Node<T>* previous = findPrevious(index);

        Node<T>* toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;

        delete toDelete;
        Size--;
    }
}

template<typename T>
void List<T>::clear()
{
    while (Size)
    {
        popFront();
    }
}

template<typename T>
int List<T>::getSize()
{
    return Size;
}

template<typename T>
T& List<T>::operator[](const int index)
{
    Node<T>* current = this->head;
    int counter = 0;

    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }

        current = current->pNext;
        counter++;
    }
}

template<typename T>
void List<T>::operator=(const List<T>& list)
{
    if (head != list.head)
    {
        clear();

        Node<T>* current = list.head;

        while (current != nullptr)
        {
            pushBack(current->data);
            current = current->pNext;
        }
    }
}

template<typename T>
bool List<T>::operator==(const List<T>& list)
{
    if (Size == list.Size)
    {
        Node<T>* list1 = head;
        Node<T>* list2 = list.head;

        for (int i = 0; i < Size; i++)
        {
            if (list1->data != list2->data)
                return false;

            list1 = list1->pNext;
            list2 = list2->pNext;
        }

        return true;
    }

    return false;
}

template<typename T>
bool List<T>::operator!=(const List<T>& list)
{
    if (Size == list.Size)
    {
        Node<T>* list1 = head;
        Node<T>* list2 = list.head;

        for (int i = 0; i < Size; i++)
        {
            if (list1->data != list2->data)
                return true;

            list1 = list1->pNext;
            list2 = list2->pNext;
        }

        return false;
    }

    return true;
}

template<typename T>
void List<T>::operator+=(List<T> list)
{
    for (int i = 0; i < list.Size; i++)
    {
        pushBack(list[i]);
    }
}

template<typename T>
List<T>& List<T>::operator+(List<T> list)
{
    for (int i = 0; i < list.Size; i++)
    {
        pushBack(list[i]);
    }

    return *this;
}

template<typename T>
void List<T>::operator+=(T data)
{
    pushBack(data);
}

template<typename T>
List<T>& List<T>::operator+(T data)
{
    pushBack(data);

    return *this;
}

template<typename T>
List<T>& List<T>::operator--()
{
    popFront();

    return *this;
}

template<typename T>
List<T>& List<T>::operator--(int none)
{
    popBack();

    return *this;
}

template<typename T>
List<T>::Node<T>* List<T>::findPrevious(int index)
{
    Node<T>* previous = this->head;

    for (int i = 0; i < index - 1; i++)
    {
        previous = previous->pNext;
    }

    return previous;
}

int main()
{

    List<int> lst;
    List<int> lst2(lst);

    lst.pushBack(2);
    lst.pushBack(32);
    lst.pushBack(25);
    lst.pushFront(23);
    lst.pushFront(22);
    lst.pushFront(23);

    lst2 = lst;

    cout << "List 1:\t\tList 2:\n";

    for (int i = 0; i < lst.getSize(); i++)
    {
        cout << lst[i] << "\t\t" << lst2[i] << endl;
    }

    cout << endl << "List 1 == List 2: " << (lst == lst2);
    cout << endl << "List 1 != List 2: " << (lst != lst2);

    --lst;
    lst2--;
    cout << endl << "\n--List 1:\t\tList 2--\n";
    for (int i = 0; i < lst.getSize(); i++)
    {
        cout << lst[i] << "\t\t\t" << lst2[i] << endl;
    }

    lst = lst + lst2;

    cout << endl << "List 1 + List 2:\n";
    for (int i = 0; i < lst.getSize(); i++)
    {
        cout << lst[i] << endl;
    }

    return 0;
}
