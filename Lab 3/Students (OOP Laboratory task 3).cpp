#include <iostream> // Варіант 12
#include <fstream>

using namespace std;

class Student // опис класу
{
    string name, surname;
    int noteMath, notePhysics, noteInformatica;

    public:
        Student(string name = "",string surname = "", int noteMath = 0, int notePhysics = 0, int noteInformatica = 0)
        {
            this->name = name;
            this->surname = surname;
            this->noteMath = noteMath;
            this->notePhysics = notePhysics;
            this->noteInformatica = noteInformatica;
        }

        friend ostream& operator<< (ostream &os, Student &student); // дружня функція перегрузки оператора
};

ostream& operator<< (ostream &os, Student &student) // перегрузка оператора
{
    os << "Name: " << student.name << "\nSurname: " << student.surname <<
    "\nNote Math: " << student.noteMath << "\nNote Physics: " << student.notePhysics <<
    "\nNote Informatica: " << student.noteInformatica << endl;

    return os;
}


int main()
{


    return 0;
}
