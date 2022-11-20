#include <iostream> // Варіант 13

using namespace std;

class dynArrActions
{
    int lenght; // довжина масиву
    int *arr; // ініціалізація масиву

public:
    dynArrActions(int lenght = 0)
    {
        this->lenght = lenght;
        arr = new int[lenght]; // виділення пам'яті для масиву

        for(int i=0;i<lenght;i++) // заповнення масиву відповідно умови задвдання
        {
            if(i%2 == 0)
                arr[i] = i;
            else arr[i] = i-6;
        }
    }

    dynArrActions(const dynArrActions &copy) // конструктор копії
    {
        lenght = copy.lenght;
        arr = new int[lenght];
        arr = copy.arr;
    }

    ~dynArrActions() // деструктор
    {
        delete[] arr;
        arr = 0;
    }

    int getLenght()
    {
        return lenght;
    }

    void setLenght(int lenghtNew)
    {
        int *bufferArr = new int[lenghtNew];

        for(int i = 0;i < lenght; i++)
        {
            if(i < lenght)
                bufferArr[i] = arr[i];
        }

        delete[] arr;
        arr = bufferArr;
        delete[] bufferArr;
        lenght = lenghtNew;
    }

    int getElement(int i)
    {
        return arr[i];
    }

    void setElement(int i, int value)
    {
        if(i < lenght)
            arr[i] = value;
    }

    void add()
    {
        setLenght(lenght+1);
    }

    friend ostream& operator<< (ostream &os, dynArrActions &arr);
};

ostream& operator<< (ostream &os, dynArrActions &arr) // перегрузка оператора
{
    for(int i=0;i<arr.lenght;i++)
    {
        os << "[" << i << "] " << arr.getElement(i) << "\n";
    }

    return os;
}

int negativeProduct(dynArrActions arr) // функція відповідно умови завдання
{
    int res = 1;

    for(int i=0;i<arr.getLenght();i++)
    {
        int el = arr.getElement(i);

        if(el < 0)
        {
            res *= el;
        }
    }

    return res;
}

int main()
{
    dynArrActions arr(15); //ініціалізація об'єкту
    arr.setLenght(19); //ініціалізація об'єкту

    cout << arr << endl << "Product negative: " << negativeProduct(arr) << endl;

    return 0;
}

