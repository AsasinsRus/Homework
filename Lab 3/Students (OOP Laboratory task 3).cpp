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

        void setName(string name)
        {
            this->name = name;
        }

        void setSurname(string surname)
        {
            this->surname = surname;
        }

        void setNoteMath(int noteMath)
        {
            this->noteMath = noteMath;
        }

        void setNotePhysics(int notePhysics)
        {
            this->notePhysics = notePhysics;
        }

        void setNoteInformatica(int noteInformatica)
        {
            this->noteInformatica = noteInformatica;
        }

        void set(string name,string surname, int noteMath, int notePhysics, int noteInformatica)
        {
            this->name = name;
            this->surname = surname;
            this->noteMath = noteMath;
            this->notePhysics = notePhysics;
            this->noteInformatica = noteInformatica;
        }

        string getName()
        {
            return name;
        }

        string getSurname()
        {
            return surname;
        }

        int getNoteMath()
        {
            return noteMath;
        }

        int getNotePhysics()
        {
            return notePhysics;
        }

        int getNoteInformatica()
        {
            return noteInformatica;
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
    int size = 0;
    string str;
    ifstream file("data.txt"); // �������� �����

    if(file) // �������� �� ��, �� �������� ����
    {
        while(!file.eof()) // �������� �� ����� ������� �� ����
        {
            getline(file, str, '\n'); // ������� ��������� �����
            size++;
        }

        Student students[size]; // ��������� ������ ��'����
        file.clear(); // ��������� ����� ���� �����
        file.seekg(0); // ����������� ������ �� �������

        for(int i=0;i<size;i++)
        {
            string name, surname;
            int noteMath, notePh, noteInf;

            file >> name >> surname >> noteMath >> notePh >> noteInf; // ����� ����� � ����� � ����

            students[i].set(name, surname, noteMath, notePh, noteInf); // ����� ������ � ��'���
        }

        for(int i=0;i<size;i++)
        {
            if(students[i].getNoteMath() == 5 && students[i].getNotePhysics() == 5 && students[i].getNoteInformatica() == 5) // �������� �� 5
            {
                cout << "Student " << i+1 << endl << students[i] << endl; // ���� ��������� �������� �� ����� ����� ������������ ���������
            }
        }

        file.close(); // �������� �����
    }
    else cout << "Unable to open file";

    return 0;
}
