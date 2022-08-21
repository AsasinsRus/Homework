#include <iostream>

using namespace std;

class star // опис класу
{
int a,b;

public:
    star();
    star(int a, int b);
    ~star();

    int getA();
    int getB();
    void set(int a, int b);

    float starArea();

    void print_sqrt();
};

star::star() // конструктор без параметрів
{
    a = 0;
    b = 0;

    cout << "Star was created" << endl;
}

star::star(int a, int b) // конструктор з параметрами
{
    this->a = a;
    this->b = b;

    cout << "Star was created" << endl << endl;
}

star::~star() // деструктор
{
    cout << "Star was destroyed" << endl;
}

void star::set(int a, int b) // сеттер
{
    this->a = a;
    this->b = b;
}

int star::getA() // геттер для довжини а
{
    return a;
}

int star::getB() // геттер для довжини б
{
    return b;
}

float star::starArea() // площа зірки
{
    float triangles, square;

    if(a > 0 && b > 0 && a > b)
    {

        triangles = (a-b)*b; // площа трикутників зірки
        square = b*b; // площа квадрату зірки

        return triangles + square;
    }

    return -1;

}

void star::print_sqrt() // виводить на екран значення a, b і площі цієї фігури цієї фігури
{
    cout << "A > " << a
        << "\nB > " << b
        << "\nStar's area > " << starArea() << endl << endl;
}

int main()
{
    star starWithoutParam; // виклик конструктора без параметрів
    star newStar(5,2); // виклик конструктора з параметрами


    newStar.print_sqrt();
    starWithoutParam.print_sqrt();

    star *starPt = &newStar, *starWithoutParamPT = &starWithoutParam; // покажчик на об'єкт

    starPt->print_sqrt(); // використання покажчика на об'єкт
    starWithoutParamPT->print_sqrt();

    cout << newStar.getA() << endl << newStar.getB() << endl << endl; // використання геттерів

    void (star::*print)(); // покажчик на функцію
    print = &star::print_sqrt;

    newStar.set(10, 5); // використання сеттера
    (newStar.*print)(); // викоористання покажчика на функцію

    //руйнування об'єктів після закінчення роботи програми

    return 0;
}
