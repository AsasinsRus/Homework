#include <iostream>
#include <stdlib.h>

using namespace std;

class Animal
{
protected:
    string name;
    string livingEnvironment;
    int maxAge;

public:
    Animal(string name = "", string livingEnvironment = "", int maxAge = 0)
    {
        this->name = name;
        this->livingEnvironment = livingEnvironment;
        this->maxAge = maxAge;
    }

    string getName()
    {
        return name;
    }

    string getLivingEnvironment()
    {
        return livingEnvironment;
    }

    int getMaxAge()
    {
        return maxAge;
    }

    void setName(string name = "")
    {
        this->name = name;
    }

    void setLivingEnvironment(string livingEnvironment = "")
    {
        this->livingEnvironment = livingEnvironment;
    }

    void setMaxAge(int maxAge = 0)
    {
        this->maxAge = maxAge;
    }

    void set(string name = "", string livingEnvironment = "", int maxAge = 0)
    {
        this->name = name;
        this->livingEnvironment = livingEnvironment;
        this->maxAge = maxAge;
    }

    friend ostream& operator<< (ostream &os, Animal &animal);
};

ostream& operator<< (ostream &os, Animal &animal)
{
    os << "Name: " << animal.name << "\nLiving Environment: " <<  animal.livingEnvironment << "\nMax Age: " << animal.maxAge << endl;

    return os;
}

class Mammal : public Animal
{
protected:
    float normalBodyTemperature;

public:
    Mammal(string name = "", string livingEnvironment = "", int maxAge = 0, float normalBodyTemperature = 0) : Animal(name, livingEnvironment, maxAge)
    {
        this->normalBodyTemperature = normalBodyTemperature;
    }

    float getBodyTemperature()
    {
        return normalBodyTemperature;
    }

    void setBodyTemperature(float normalBodyTemperature = 0)
    {
        this->normalBodyTemperature = normalBodyTemperature;
    }

    void set(string name = "", string livingEnvironment = "", int maxAge = 0, float normalBodyTemperature = 0)
    {
        this->normalBodyTemperature = normalBodyTemperature;
        this->name = name;
        this->livingEnvironment = livingEnvironment;
        this->maxAge = maxAge;
    }

    friend ostream& operator<< (ostream &os, Mammal &mammal);
};

ostream& operator<< (ostream &os, Mammal &mammal)
{
    os << "Name: " << mammal.name << "\nLiving Environment: " <<  mammal.livingEnvironment
    << "\nMax Age: " << mammal.maxAge << "\nNormal body temperature: " << mammal.normalBodyTemperature << endl;

    return os;
}

class Even_toed : public Mammal
{
    bool hasHorns;

public:
    Even_toed(string name = "", string livingEnvironment = "", int maxAge = 0, bool hasHorns = false, float normalBodyTemperature = 0) :
        Mammal(name, livingEnvironment, maxAge, normalBodyTemperature)
        {
            this->hasHorns = hasHorns;
        }

    bool getHorns()
    {
        return hasHorns;
    }

    void setHorns(bool hasHorns = false)
    {
        this->hasHorns = hasHorns;
    }

    void set(string name = "", string livingEnvironment = "", int maxAge = 0, bool hasHorns = false, float normalBodyTemperature = 0)
    {
        this->hasHorns = hasHorns;
        this->normalBodyTemperature = normalBodyTemperature;
        this->name = name;
        this->livingEnvironment = livingEnvironment;
        this->maxAge = maxAge;
    }

    friend ostream& operator<< (ostream &os, Even_toed &even_toed);
};

ostream& operator<< (ostream &os, Even_toed &even_toed)
{
    os << "Name: " << even_toed.name << "\nLiving Environment: " <<  even_toed.livingEnvironment
    << "\nMax Age: " << even_toed.maxAge << "\nNormal body temperature: " << even_toed.normalBodyTemperature
    << "\nHas horns: ";
    even_toed.hasHorns ? os << "yes" << endl : os << "no" << endl;

    return os;
}

class Bird : public Animal
{
    bool canFly;

public:
    Bird(string name = "", string livingEnvironment = "", int maxAge = 0, bool canFly = false) : Animal(name, livingEnvironment, maxAge)
    {
        this->canFly = canFly;
    }

    bool getFly()
    {
        return canFly;
    }

    void setFly(bool canFly = false)
    {
        this->canFly = canFly;
    }

    void set(string name = "", string livingEnvironment = "", int maxAge = 0, bool canFly = false)
    {
        this->canFly = canFly;
        this->name = name;
        this->livingEnvironment = livingEnvironment;
        this->maxAge = maxAge;
    }

    friend ostream& operator<< (ostream &os, Bird &bird);
};

ostream& operator<< (ostream &os, Bird &bird)
{
    os << "Name: " << bird.name << "\nLiving Environment: " <<  bird.livingEnvironment
    << "\nMax Age: " << bird.maxAge << "\nCan fly: ";
    bird.canFly ? os << "yes" << endl : os << "no" << endl;

    return os;
}

int main()
{
    Bird bird("Steppe eagle", "steppe", 30, true);
    Mammal mammal("Cat", "anywhere", 20, 38.3);
    Even_toed even_toed("Red deer", "Europe", 20, true, 38.5);

    cout << bird << endl << mammal << endl << even_toed << endl << endl;

    Animal animals[3] = {bird, mammal, even_toed};

    cout << "Array of animals:\n\n";

    for(int i=0;i<3;i++)
    {
        cout << animals[i] << endl;
    }

    return 0;
}
