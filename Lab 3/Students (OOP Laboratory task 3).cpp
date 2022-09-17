#include <iostream> // ������ 12
#include <fstream>

using namespace std;

class Student // ���� �����
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

        friend ostream& operator<< (ostream &os, Student &student); // ������ ������� ���������� ���������
};

ostream& operator<< (ostream &os, Student &student) // ���������� ���������
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
