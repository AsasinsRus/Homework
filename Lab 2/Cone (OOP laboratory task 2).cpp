#define _USE_MATH_DEFINES
 // Варіант 7
#include <iostream>
#include <math.h>

using namespace std;

class Cone // опис класу
{
int radius, height;

public:
    Cone(int radius = 0, int height = 0)
    {
        this->radius = radius;
        this->height = height;
    }

    void setRadius(int radius)
    {
        this->radius = radius;
    }

    void setHeight(int height)
    {
        this->height = height;
    }

    void set(int radius = 0, int height = 0) // скорочене написання для конструкторів
    {
        this->radius = radius;
        this->height = height;
    }

    int getRadius()
    {
        return radius;
    }

    int getHeight()
    {
        return height;
    }

    double volume()
    {
        return M_PI*pow(radius,2)*height/3;
    }

    void print_val()
    {
        cout << "Height: " << height << endl <<
        "Radius: " << radius << endl <<
        "Volume: " << volume() << endl;
    }

    friend ostream& operator<< (ostream &os, Cone &cone); // дружня функція перегрузки оператора
    friend Cone frd(Cone cone1, Cone cone2); // дружня функція з умови
};

ostream& operator<< (ostream &os, Cone &cone) // перегрузка оператора
{
    os << "Height: " << cone.height << "\nRadius: " << cone.radius << endl;
    return os;
}

Cone frd(Cone cone1, Cone cone2)
{
    Cone res(fmax(cone1.radius, cone2.radius), cone1.height + cone2.height);

    return res;
}


int main()
{
    Cone cone1(2,4); // ініціалізація конструктора з параметрами
    Cone cone2; // ініціалізація конструктора без параметрів

    cout << "Cone 1:\n" << cone1; // використання перегрузки оператора
    cout << "\nCone 2:\n" << cone2;

    cone2.set(4,5); // використання сеттера для задання нових даних

    cout << "\nCone 1:\n" << cone2 << endl;

    cout << "Cone 1: \n";
    cone1.print_val();

    cout << "\nCone 2: \n";
    cone2.print_val();

    Cone buffer = frd(cone1, cone2); // виклик дружньої функції

    cout << "\nfrd result: \n" << buffer;

    return 0;
}
